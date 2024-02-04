#include "webapp.hpp"

enum { WindowSize_WD = 800, WindowSize_HT = 600 };

NAMESPACE_BEGIN(sway)

std::shared_ptr<pltf::EMSContext> emsContext_ = nullptr;
std::shared_ptr<pltf::EMSWindow> emsWindow_ = nullptr;
std::shared_ptr<pltf::EMSLooper> emsLooper_ = nullptr;
std::string canvasId_;
pthread_t worker_;

std::shared_ptr<render::RenderSubsystem> renderSubsystem_ = nullptr;
std::shared_ptr<render::RenderSubqueue> renderSubqueue_ = nullptr;

std::shared_ptr<rms::ImageResourceManager> imageResMngr_ = nullptr;
std::shared_ptr<rms::GLSLResourceManager> glslResMngr_ = nullptr;

std::shared_ptr<render::Material> crateMtrl_ = nullptr;
std::shared_ptr<render::Geometry> crateGeom_ = nullptr;
std::shared_ptr<render::SpriteBatch> batch_ = nullptr;

pltf::Timer timer_;
f32_t speed_ = 0.01F;

void createContext(const std::string &canvasId) {
  emsContext_ = std::make_shared<pltf::EMSContext>(canvasId);
  emsContext_->create(nullptr);
  emsContext_->makeCurrent();

  emsWindow_ = std::make_shared<pltf::EMSWindow>(emsContext_);
  emsWindow_->setSize(WindowSize_WD, WindowSize_HT);

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
  imageResMngr_ = std::make_shared<rms::ImageResourceManager>();
  imageResMngr_->registerImageProvider("./module_loader_png_wasm_async.wasm");
  imageResMngr_->fetchData("diffuse_sampler_png", "./wwwroot/dist/assets/img.png");
  imageResMngr_->fetchData("crate_png", "./wwwroot/dist/assets/kenney_tanks_crate_wood.png");
  imageResMngr_->fetchData("tank_png", "./wwwroot/dist/assets/kenney_tanks_tank_desert_1.png");

  glslResMngr_ = std::make_shared<rms::GLSLResourceManager>();
  glslResMngr_->fetchData("base_vs", "./wwwroot/dist/assets/web/crate.vs");
  glslResMngr_->fetchData("base_fs", "./wwwroot/dist/assets/web/crate.fs");

  crateMtrl_ = std::make_shared<render::Material>("crate_material", imageResMngr_, glslResMngr_);
  crateMtrl_->addImage("crate_png", "crate_sampler");
  crateMtrl_->addEffect({"base_vs", "base_fs"});

  batch_ = std::make_shared<render::SpriteBatch>();
  batch_->initialize(renderSubsystem_, renderSubqueue_, crateMtrl_, math::size2f_one);
}

void mainLoopCallback_(void *target) {
  auto dtime = timer_.started();

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

  batch_->onUpdate(math::mat4f_t(), matProj, math::mat4f_t(), dtime);

  renderSubsystem_->render();

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
  }, nullptr);  // clang-format on
}

NAMESPACE_END(sway)
