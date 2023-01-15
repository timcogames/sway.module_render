#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/glx11/canvas.hpp>
#include <sway/glx11/xscreenconnection.hpp>
#include <sway/graphics.hpp>
#include <sway/math.hpp>
#include <sway/math/extensions/projection.hpp>
#include <sway/render.hpp>

#include <chrono>  // std::chrono
#include <memory>  // std::shared_ptr, std::make_shared
#include <tuple>  // std::tuple

using namespace sway;
using namespace std::chrono;

#define TIME_STEP (1. / 60)
#define TIME_FRAME_BEG 0
#define TIME_FRAME_END 1

// using TimeFrame_t = std::tuple<time_point, time_point>;

// class Timer {
// public:
//   Timer() {}

//   ~Timer() = default;

//   void start() {
//     auto limit = duration_cast<system_clock::duration>(duration<f64_t>{TIME_STEP});
//     timeframe_.set<TIME_FRAME_BEG>(system_clock::now());
//     timeframe_.set<TIME_FRAME_END>(timeframe_.get<TIME_FRAME_BEG>() + limit);

//     auto prevTime = time_point_cast<seconds>(timeframe_.get<TIME_FRAME_BEG>());
//   }

//   void stop() {}

//   s64_t getInterval() {}

// private:
//   TimeFrame_t timeframe_;
// };

class RenderSubsystemContext : public core::foundation::Context {
public:
  RenderSubsystemContext() {
    char path[PATH_MAX + 1];
    strncpy(path, "/Users/apriori85/Documents/Projects/sway.module_graphics/bin", PATH_MAX);
    std::string plugname = core::misc::format("%s/module_gapi_gl.dylib.0.16.34", path);

    subsystem_ = std::make_shared<render::RenderSubsystem>(plugname, this);

    subqueue_ = std::make_shared<render::RenderSubqueue>();
    subqueue_->initialize();

    resourceManagerSystem_ = std::make_shared<rms::ResourceManagerSystem>();
    resourceManagerSystem_->registerImageProvider(
        "/Users/apriori85/Documents/Projects/sway.module_graphics/bin/module_loader_png.dylib.0.1.0");

    resourceManagerSystem_->loadImage("png", "/Users/apriori85/Documents/Projects/sway.module_graphics/bin/img.png");

    material_ = std::make_shared<graphics::Material>(resourceManagerSystem_);
    material_->loadImage("png");
    material_->loadEffect("");

    std::array<sway::gapi::VertexSemantic, 2> quadSemantics = {
        sway::gapi::VertexSemantic::POS, sway::gapi::VertexSemantic::TEXCOORD_0};
    auto quad = std::make_shared<render::primitives::Quad<math::VertexTexCoord>>(math::size2f_t(0.3f));
    quad->useVertexSemanticSet(quadSemantics);
    auto quadData = quad->getGeometryData();

    render::GeometryCreateInfo info;
    info.topology = gapi::TopologyType::TRIANGLE_LIST;

    info.vb.desc.usage = gapi::BufferUsage::STATIC;
    info.vb.desc.byteStride = sizeof(math::VertexTexCoord);
    info.vb.desc.capacity = quadData->getVtxCount();
    info.vb.data = quadData->getVtxRawdata();

    info.ib.desc.usage = gapi::BufferUsage::STATIC;
    info.ib.desc.byteStride = sizeof(u32_t);
    info.ib.desc.capacity = quadData->getIdxCount();
    info.ib.data = quadData->getIndices().data();

    auto geometry = std::make_shared<render::Geometry>(subqueue_->getIdGenerator(), info, material_->getEffect(), true);
    geometry->create(quad->getVertexAttribs());
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
  std::shared_ptr<rms::ResourceManagerSystem> resourceManagerSystem_;  // resmgr
  std::shared_ptr<graphics::Material> material_;
};

enum { WindowSize_WD = 800, WindowSize_HT = 600 };

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  glx11::WindowInitialInfo windowInitialInfo;
  windowInitialInfo.title = "material example";
  windowInitialInfo.size.normal = math::size2i_t(WindowSize_WD, WindowSize_HT);
  windowInitialInfo.fullscreen = false;
  windowInitialInfo.resizable = false;

  auto connection = std::make_shared<glx11::XScreenConnection>();
  auto canvas = std::make_shared<glx11::Canvas>(connection, windowInitialInfo);

  canvas->show();
  canvas->getContext()->makeCurrent();

  auto rendersystemContext = std::make_shared<RenderSubsystemContext>();

  auto prevTime = high_resolution_clock::now();
  float test = 0.0f;
  while (canvas->eventLoop(true)) {
    auto currTime = high_resolution_clock::now();
    f32_t dt = duration<f32_t, seconds::period>(currTime - prevTime).count();

    test += 1.f * dt;

    canvas->getContext()->makeCurrent();

    float const aspectRatio = 1.0;

    math::Projection projection;
    math::mat4f_t projmat = projection.ortho(-1.0 * aspectRatio, -1.0, 1.0 * aspectRatio, 1.0, 0.0, 100.0);

    rendersystemContext->getMaterial()->getEffect()->getShaderProgram()->setUniformMat4f("proj_mat", projmat);
    rendersystemContext->getMaterial()->getEffect()->getShaderProgram()->setUniform1f("time", test);
    rendersystemContext->getMaterial()->bind();
    rendersystemContext->drawFrame();
    rendersystemContext->getMaterial()->unbind();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();

    prevTime = currTime;
  }

  return 0;
}
