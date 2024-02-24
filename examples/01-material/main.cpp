#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/math/extensions/projection.hpp>
#include <sway/pltf.hpp>
#include <sway/pltf/mac/dtpcanvas.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>
#include <sway/render/geometry.hpp>
#include <sway/render/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/procedurals/prims/plane.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>

#include <memory>  // std::shared_ptr, std::make_shared
#include <tuple>  // std::tuple

using namespace sway;

class RenderSubsystemContext : public core::foundation::Context {
public:
  RenderSubsystemContext() {
    std::array<char, PATH_MAX + 1> binPath;
    strncpy(binPath.data(), "/Users/apriori85/Documents/Projects/sway.module_render/bin", PATH_MAX);

    auto const plugname = core::misc::format("%s/libmodule_gapi_gl.dylib", binPath.data());

    subsystem_ =
        std::make_shared<render::RenderSubsystem>(new core::Plugin(core::generic::io::Path(plugname), RTLD_NOW), this);
    subsystem_->initialize();
    subqueue_ = std::make_shared<render::RenderSubqueue>();
    subqueue_->initialize();

    auto queue = subsystem_->createQueue(core::detail::toUnderlying(core::intrusive::Priority::HIGH));
    queue->addSubqueue(subqueue_);
  }

  virtual ~RenderSubsystemContext() = default;

  auto getRenderSubsystem() -> std::shared_ptr<render::RenderSubsystem> { return subsystem_; }

  void drawFrame() { subsystem_->render(); }

private:
  std::shared_ptr<render::RenderSubsystem> subsystem_;
  std::shared_ptr<render::RenderSubqueue> subqueue_;
};

enum { WindowSize_WD = 800, WindowSize_HT = 600 };

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  std::array<char, PATH_MAX + 1> binPath;
  strncpy(binPath.data(), "/Users/apriori85/Documents/Projects/sway.module_render/bin", PATH_MAX);

  pltf::WindowInitialInfo windowInitialInfo;
  windowInitialInfo.title = "material example";
  windowInitialInfo.size.normal = math::size2i_t(WindowSize_WD, WindowSize_HT);
  windowInitialInfo.fullscreen = false;
  windowInitialInfo.resizable = false;

  auto connection = std::make_shared<pltf::DTPScreenConnection>();
  auto canvas = std::make_shared<pltf::DTPCanvas>(connection, windowInitialInfo);

  canvas->show();
  canvas->getContext()->makeCurrent();

  auto renderSubsystemContext = std::make_shared<RenderSubsystemContext>();
  auto renderSubsystem = renderSubsystemContext->getRenderSubsystem();
  auto renderSubqueue = renderSubsystem->getQueueByIdx(0)->getSubqueues(render::RenderSubqueueGroup::OPAQUE)[0];

  auto imageResMngr = std::make_shared<rms::ImageResourceManager>();
  imageResMngr->registerImageProvider(core::misc::format("%s/libmodule_loader_png.dylib", binPath.data()));
  imageResMngr->fetchData("img_png", core::misc::format("%s/assets/img.png", binPath.data()));

  auto glslResMngr = std::make_shared<rms::GLSLResourceManager>();
  glslResMngr->fetchData("base_vs", core::misc::format("%s/assets/dtp/shader.vs", binPath.data()));
  glslResMngr->fetchData("base_fs", core::misc::format("%s/assets/dtp/shader.fs", binPath.data()));

  auto mtrl = std::make_shared<render::Material>("material", imageResMngr, glslResMngr);
  mtrl->addImage("img_png", "diffuse_sampler");
  printf("addImage\n");

  mtrl->addEffect({"base_vs", "base_fs"});
  printf("addEffect\n");

  std::array<sway::gapi::VertexSemantic, 3> quadSemantics = {
      sway::gapi::VertexSemantic::POS, sway::gapi::VertexSemantic::COL, sway::gapi::VertexSemantic::TEXCOORD_0};
  auto quad = std::make_shared<render::procedurals::prims::Plane<math::VertexTexCoord>>(
      math::size2f_t(1.0F), math::size2i_t(1));
  quad->useVertexSemanticSet(quadSemantics);

  auto geom = std::make_shared<render::Geometry>(renderSubsystem->getIdGenerator(), mtrl->getEffect(), true);
  geom->create(quad);

  pltf::Timer timer;

  f32_t test = 0.0F;
  while (canvas->eventLoop(true)) {
    auto dtime = timer.started();

    test += 1.0F * dtime;

    // clang-format off
    math::Projection projection = math::Projection((struct math::ProjectionDescription) {
      .rect = {{-1.0F /* L */, -1.0F /* T */, 1.0F /* R */, 1.0F /* B */}},
      .fov = 0,
      .aspect = f32_t(WindowSize_WD / WindowSize_HT),
      .znear = 0.0F,
      .zfar = 100.0F
    });  // clang-format on

    math::mat4f_t matProj;
    matProj.setData(projection.makeOrtho());

    render::pipeline::ForwardRenderCommand cmd;
    cmd.geometry = geom;
    cmd.material = mtrl;
    cmd.transform = math::mat4f_t();  // Identity
    cmd.proj = matProj;
    cmd.view = math::mat4f_t();
    renderSubqueue->post(cmd);

    canvas->getContext()->makeCurrent();

    mtrl->getEffect()->getShaderProgram()->setUniform1f("time", test);

    renderSubsystemContext->drawFrame();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();

    timer.ended();
  }

  return 0;
}
