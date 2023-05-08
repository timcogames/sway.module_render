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
    char path[PATH_MAX + 1];
    strncpy(path, "/Users/apriori85/Documents/Projects/sway.module_render/bin", PATH_MAX);
    std::string const plugname = core::misc::format("%s/module_gapi_gl.dylib.0.16.34", path);

    subsystem_ =
        std::make_shared<render::RenderSubsystem>(new core::Plugin(core::generic::io::Path(plugname), RTLD_NOW), this);
    subsystem_->initialize();
    subqueue_ = std::make_shared<render::RenderSubqueue>();
    subqueue_->initialize();

    auto queue = subsystem_->createQueue();
    queue->setPriority(core::intrusive::Priority_High);
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

  auto resourceMngr = std::make_shared<rms::ResourceManagerSystem>();
  resourceMngr->registerImageProvider(
      "/Users/apriori85/Documents/Projects/sway.module_render/bin/module_loader_png.dylib.0.1.0");

  resourceMngr->loadImage("myimg", "/Users/apriori85/Documents/Projects/sway.module_render/bin/assets/img.png");

  auto mtrl = std::make_shared<render::Material>("material", resourceMngr);
  mtrl->addImage("myimg");
  mtrl->loadEffect({"/Users/apriori85/Documents/Projects/sway.module_render/bin/assets/dtp/shader.vs",
      "/Users/apriori85/Documents/Projects/sway.module_render/bin/assets/dtp/shader.fs"});

  std::array<sway::gapi::VertexSemantic, 2> quadSemantics = {
      sway::gapi::VertexSemantic::POS, sway::gapi::VertexSemantic::TEXCOORD_0};
  auto quad = std::make_shared<render::procedurals::prims::Plane<math::VertexTexCoord>>(
      math::size2f_t(1.0F), math::col4f_t(1.0F, 0.0F, 0.0F));
  quad->useVertexSemanticSet(quadSemantics);

  auto geom = std::make_shared<render::Geometry>(renderSubsystem->getIdGenerator(), mtrl->getEffect(), true);
  geom->create(quad);

  pltf::Timer timer;

  f32_t test = 0.0F;
  while (canvas->eventLoop(true)) {
    auto dtime = timer.started();

    test += 1.0F * dtime;

    // --

    f32_t const aspectRatio = 1.0F;
    math::Projection projection;
    math::mat4f_t projMtx = projection.ortho(-1.0F * aspectRatio, -1.0F, 1.0F * aspectRatio, 1.0F, 0.0F, 100.0F);

    render::pipeline::ForwardRenderCommand command;
    command.geometry = geom;
    command.effect = mtrl->getEffect();
    command.images = mtrl->getImages();
    command.transform = math::mat4f_t();  // Identity
    command.proj = projMtx;
    renderSubqueue->post(command);

    // --

    canvas->getContext()->makeCurrent();

    mtrl->getEffect()->getShaderProgram()->setUniform1f("time", test);
    mtrl->bind();
    renderSubsystemContext->drawFrame();
    mtrl->unbind();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();

    timer.ended();
  }

  return 0;
}
