#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/glx11/canvas.hpp>
#include <sway/glx11/xscreenconnection.hpp>
#include <sway/graphics.hpp>
#include <sway/math.hpp>
#include <sway/math/extensions/projection.hpp>
#include <sway/render.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

class RenderSubsystemContext : public core::foundation::Context {
public:
  RenderSubsystemContext() {
    char path[PATH_MAX + 1];
    strncpy(path, "/Users/apriori85/Documents/Projects/sway.module_render/bin", PATH_MAX);
    std::string plugname = core::misc::format("%s/module_gapi_gl.dylib.0.16.34", path);

    subsystem_ = std::make_shared<render::RenderSubsystem>(plugname, this);

    subqueue_ = std::make_shared<render::RenderSubqueue>();
    subqueue_->initialize();

    material_ = std::make_shared<graphics::Material>();
    material_->loadEffect("");
    auto quad = std::make_shared<render::primitives::Quad>(math::size2f_t(0.5));
    auto quadData = quad->getGeometryData();

    render::GeometryCreateInfo info;
    info.topology = gapi::TopologyType::TRIANGLE_LIST;

    info.vb.desc.target = gapi::BufferTarget::ARRAY;
    info.vb.desc.usage = gapi::BufferUsage::STATIC;
    info.vb.desc.byteStride = sizeof(math::VertexColor);
    info.vb.desc.capacity = quadData->getVtxCount();
    info.vb.data = quadData->getVtxRawdata();

    info.ib.desc.target = gapi::BufferTarget::ELEMENT_ARRAY;
    info.ib.desc.usage = gapi::BufferUsage::STATIC;
    info.ib.desc.byteStride = sizeof(u32_t);
    info.ib.desc.capacity = quadData->getIdxCount();
    info.ib.data = quadData->getIndices().data();

    auto geometry = std::make_shared<render::Geometry>(subqueue_->getIdGenerator(), info, material_->getEffect(), true);
    geometry->create(quadData);
    subqueue_->addGeometry(geometry);

    auto queue = subsystem_->createQueue();
    queue->setPriority(core::intrusive::Priority_High);
    queue->addSubqueue(subqueue_);
  }

  virtual ~RenderSubsystemContext() = default;

  void drawFrame() { subsystem_->render(); }

  std::shared_ptr<graphics::Material> getMaterial() { return material_; }

private:
  std::shared_ptr<render::RenderSubsystem> subsystem_;
  std::shared_ptr<render::RenderSubqueue> subqueue_;
  std::shared_ptr<graphics::Material> material_;
};

enum { WindowSize_WD = 800, WindowSize_HT = 600 };

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  glx11::WindowInitialInfo windowInitialInfo;
  windowInitialInfo.title = "examples";
  windowInitialInfo.size.normal = math::size2i_t(WindowSize_WD, WindowSize_HT);
  windowInitialInfo.fullscreen = false;
  windowInitialInfo.resizable = false;

  auto connection = std::make_shared<glx11::XScreenConnection>();
  auto canvas = std::make_shared<glx11::Canvas>(connection, windowInitialInfo);

  canvas->show();
  canvas->getContext()->makeCurrent();

  auto rendersystemContext = std::make_shared<RenderSubsystemContext>();

  while (canvas->eventLoop(true)) {
    canvas->getContext()->makeCurrent();

    float const aspectRatio = 1.0;

    math::Projection projection;
    math::mat4f_t projmat = projection.ortho(1.0 * aspectRatio, -1.0, -1.0 * aspectRatio, 1.0, 0.0, 100.0);

    rendersystemContext->getMaterial()->getEffect()->getShaderProgram()->setUniformMat4f("proj_mat", projmat);

    rendersystemContext->drawFrame();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();
  }

  return 0;
}
