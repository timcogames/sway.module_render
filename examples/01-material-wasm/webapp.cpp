#include "webapp.hpp"

enum { WindowSize_WD = 800, WindowSize_HT = 600 };

NAMESPACE_BEGIN(sway)

std::shared_ptr<pltf::EMSContext> emsContext_ = nullptr;
std::shared_ptr<pltf::EMSLooper> emsLooper_ = nullptr;
std::string canvasId_;
pthread_t worker_;

std::shared_ptr<render::RenderSubsystem> renderSubsystem_ = nullptr;
std::shared_ptr<render::RenderSubqueue> renderSubqueue_ = nullptr;

std::shared_ptr<rms::ImageResourceManager> resourceMngr_ = nullptr;

std::shared_ptr<render::Material> mtrl_ = nullptr;
std::shared_ptr<render::Geometry> geom_ = nullptr;

pltf::Timer timer_;
f32_t speed_ = 0.01F;

void createContext(const std::string &canvasId) {
  emsContext_ = std::make_shared<pltf::EMSContext>(canvasId);
  emsContext_->create(nullptr);
  emsContext_->makeCurrent();

  const auto *plugname = "./module_gapi_gl_wasm_async.wasm";
  auto *plug = new core::Plugin(core::generic::io::Path(plugname), RTLD_NOW);

  renderSubsystem_ = std::make_shared<render::RenderSubsystem>(plug, nullptr);
  renderSubsystem_->initialize();

  renderSubqueue_ = std::make_shared<render::RenderSubqueue>();
  renderSubqueue_->initialize();

  auto queue = renderSubsystem_->createQueue(core::detail::toUnderlying(core::intrusive::Priority::HIGH));
  queue->addSubqueue(renderSubqueue_);
}

void createResource() {
  resourceMngr_ = std::make_shared<rms::ImageResourceManager>();
  resourceMngr_->registerImageProvider("./module_loader_png_wasm_async.wasm");

  resourceMngr_->fetchData("myimg", "./wwwroot/dist/assets/img.png");

  mtrl_ = std::make_shared<render::Material>("material", resourceMngr_);
  mtrl_->addImage("myimg");

  // clang-format off
  mtrl_->loadEffect({
    "./wwwroot/dist/assets/web/shader.vs",
    "./wwwroot/dist/assets/web/shader.fs"
  });
  // clang-format on

  std::array<sway::gapi::VertexSemantic, 2> quadSemantics = {
      sway::gapi::VertexSemantic::POS, sway::gapi::VertexSemantic::TEXCOORD_0};
  auto quad = std::make_shared<render::procedurals::prims::Plane<math::VertexTexCoord>>(
      math::size2f_t(1.0F), math::size2i_t(1));
  quad->useVertexSemanticSet(quadSemantics);

  geom_ = std::make_shared<render::Geometry>(renderSubsystem_->getIdGenerator(), mtrl_->getEffect(), true);
  geom_->create(quad);
}

void mainLoopCallback_(void *target) {
  auto dtime = timer_.started();
  speed_ += 1.0F * dtime;

  // clang-format off
  math::Projection projection = math::Projection((struct math::ProjectionDescription) {
    .rect = {{-1.0F /* L */, -1.0F /* T */, 1.0F /* R */, 1.0F /* B */}},
    .fov = 0,
    .aspect = f32_t(WindowSize_WD / WindowSize_HT),
    .near = 0.0F,
    .far = 100.0F
  });
  // clang-format on

  math::mat4f_t matProj;
  matProj.setData(projection.makeOrtho());

  render::pipeline::ForwardRenderCommand cmd;
  cmd.geometry = geom_;
  cmd.effect = mtrl_->getEffect();
  cmd.images = mtrl_->getImages();
  cmd.transform = math::mat4f_t();  // Identity
  cmd.proj = matProj;
  cmd.view = math::mat4f_t();
  renderSubqueue_->post(cmd);

  mtrl_->getEffect()->getShaderProgram()->setUniform1f("time", speed_);
  mtrl_->bind();
  renderSubsystem_->render();
  mtrl_->unbind();

  timer_.ended();
}

void runWorker() {
  createContext("#canvas");
  createResource();

  emsLooper_ = std::make_shared<pltf::EMSLooper>();
  emsLooper_->loop(mainLoopCallback_, nullptr, false);
}

void createWorker() {
  assert(emscripten_is_main_browser_thread());

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  emscripten_pthread_attr_settransferredcanvases(&attr, "canvas");
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  // clang-format off
  pthread_create(&worker_, &attr, [](void *ctx) -> void * {
    runWorker();
    return nullptr;
  }, nullptr);
  // clang-format on
}

NAMESPACE_END(sway)
