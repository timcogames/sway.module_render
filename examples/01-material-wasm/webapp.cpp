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

std::shared_ptr<render::Material> tankMtrl_ = nullptr;
std::shared_ptr<render::Geometry> tankGeom_ = nullptr;

std::shared_ptr<render::Material> tankSilhouetteMtrl_ = nullptr;
std::shared_ptr<render::Geometry> tankSilhouetteGeom_ = nullptr;

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
  glslResMngr_->fetchData("base_vs", "./wwwroot/dist/assets/web/shader.vs");
  glslResMngr_->fetchData("base_fs", "./wwwroot/dist/assets/web/shader.fs");
  glslResMngr_->fetchData("crate_vs", "./wwwroot/dist/assets/web/crate.vs");
  glslResMngr_->fetchData("crate_fs", "./wwwroot/dist/assets/web/crate.fs");
  glslResMngr_->fetchData("tank_vs", "./wwwroot/dist/assets/web/tank.vs");
  glslResMngr_->fetchData("tank_fs", "./wwwroot/dist/assets/web/tank.fs");
  glslResMngr_->fetchData("tank_silhouette_vs", "./wwwroot/dist/assets/web/tank_silhouette.vs");
  glslResMngr_->fetchData("tank_silhouette_fs", "./wwwroot/dist/assets/web/tank_silhouette.fs");

  crateMtrl_ = std::make_shared<render::Material>("crate_material", imageResMngr_, glslResMngr_);
  crateMtrl_->addImage("crate_png", "crate_sampler");
  crateMtrl_->addEffect({"crate_vs", "crate_fs"});

  tankMtrl_ = std::make_shared<render::Material>("tank_material", imageResMngr_, glslResMngr_);
  tankMtrl_->addImage("tank_png", "tank_sampler");
  tankMtrl_->addEffect({"tank_vs", "tank_fs"});

  tankSilhouetteMtrl_ = std::make_shared<render::Material>("tank_silhouette_material", imageResMngr_, glslResMngr_);
  tankSilhouetteMtrl_->addImage("tank_png", "tank_sampler");
  tankSilhouetteMtrl_->addEffect({"tank_silhouette_vs", "tank_silhouette_fs"});

  std::array<gapi::VertexSemantic, 3> quadSemantics = {
      gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0};

  auto crateGeomQuad = std::make_shared<render::procedurals::prims::Plane<math::VertexTexCoord>>(
      math::size2f_t(0.2F), math::size2i_t(1));
  crateGeomQuad->useVertexSemanticSet(quadSemantics);
  crateGeom_ = std::make_shared<render::Geometry>(renderSubsystem_->getIdGenerator(), crateMtrl_->getEffect(), true);
  crateGeom_->create(crateGeomQuad);

  auto tankGeomQuad = std::make_shared<render::procedurals::prims::Plane<math::VertexTexCoord>>(
      math::size2f_t(0.4F), math::size2i_t(1));
  tankGeomQuad->useVertexSemanticSet(quadSemantics);
  tankGeom_ = std::make_shared<render::Geometry>(renderSubsystem_->getIdGenerator(), tankMtrl_->getEffect(), true);
  tankGeom_->create(tankGeomQuad);

  auto tankSilhouetteQuad = std::make_shared<render::procedurals::prims::Plane<math::VertexTexCoord>>(
      math::size2f_t(0.4F), math::size2i_t(1), COL4F_RED);
  tankSilhouetteQuad->useVertexSemanticSet(quadSemantics);
  tankSilhouetteGeom_ =
      std::make_shared<render::Geometry>(renderSubsystem_->getIdGenerator(), tankSilhouetteMtrl_->getEffect(), true);
  tankSilhouetteGeom_->create(tankSilhouetteQuad);
}

void mainLoopCallback_(void *target) {
  auto dtime = timer_.started();
  speed_ += 1.0F * dtime;

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

  render::pipeline::ForwardRenderCommand crateCmd;
  crateCmd.stage = 0;
  crateCmd.blendDesc.enabled = true;
  crateCmd.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
  crateCmd.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
  crateCmd.blendDesc.mask = true;
  crateCmd.rasterizerDesc.mode = gapi::CullFace::BACK;
  crateCmd.rasterizerDesc.ccw = false;
  crateCmd.depthDesc.enabled = true;
  crateCmd.depthDesc.func = gapi::CompareFn::LESS;
  crateCmd.depthDesc.mask = true;
  crateCmd.depthDesc.near = 0;
  crateCmd.depthDesc.far = 0;
  crateCmd.stencilDesc.enabled = true;
  crateCmd.stencilDesc.front.func = gapi::CompareFn::ALWAYS;
  crateCmd.stencilDesc.front.fail = gapi::StencilOp::KEEP;
  crateCmd.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
  crateCmd.stencilDesc.front.depthPass = gapi::StencilOp::REPLACE;
  crateCmd.stencilDesc.front.rmask = 0xFFFFFF;
  crateCmd.stencilDesc.front.wmask = crateCmd.stencilDesc.front.rmask;
  crateCmd.stencilDesc.front.reference = 1;
  crateCmd.stencilDesc.back = crateCmd.stencilDesc.front;
  crateCmd.geometry = crateGeom_;
  crateCmd.material = crateMtrl_;
  crateCmd.tfrm = math::mat4f_t();  // Identity
  crateCmd.proj = matProj;
  crateCmd.view = math::mat4f_t();
  renderSubqueue_->post(crateCmd);

  render::pipeline::ForwardRenderCommand tankCmd_1;
  tankCmd_1.stage = 0;
  tankCmd_1.blendDesc.enabled = true;
  tankCmd_1.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
  tankCmd_1.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
  tankCmd_1.blendDesc.mask = false;
  tankCmd_1.rasterizerDesc.mode = gapi::CullFace::BACK;
  tankCmd_1.rasterizerDesc.ccw = false;
  tankCmd_1.depthDesc.enabled = true;
  tankCmd_1.depthDesc.func = gapi::CompareFn::LESS;
  tankCmd_1.depthDesc.mask = true;
  tankCmd_1.depthDesc.near = 0;
  tankCmd_1.depthDesc.far = 0;
  tankCmd_1.stencilDesc.enabled = true;
  tankCmd_1.stencilDesc.front.func = gapi::CompareFn::EQUAL;
  tankCmd_1.stencilDesc.front.fail = gapi::StencilOp::KEEP;
  tankCmd_1.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
  tankCmd_1.stencilDesc.front.depthPass = gapi::StencilOp::INCREMENT;
  tankCmd_1.stencilDesc.front.rmask = 0xFFFFFF;
  tankCmd_1.stencilDesc.front.wmask = tankCmd_1.stencilDesc.front.rmask;
  tankCmd_1.stencilDesc.front.reference = 1;
  tankCmd_1.stencilDesc.back = tankCmd_1.stencilDesc.front;
  tankCmd_1.geometry = tankGeom_;
  tankCmd_1.material = tankMtrl_;
  tankCmd_1.tfrm = math::mat4f_t();  // Identity
  tankCmd_1.proj = matProj;
  tankCmd_1.view = math::mat4f_t();
  renderSubqueue_->post(tankCmd_1);

  render::pipeline::ForwardRenderCommand tankCmd_2;
  tankCmd_2.stage = 0;
  tankCmd_2.blendDesc.enabled = true;
  tankCmd_2.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
  tankCmd_2.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
  tankCmd_2.blendDesc.mask = true;
  tankCmd_2.rasterizerDesc.mode = gapi::CullFace::BACK;
  tankCmd_2.rasterizerDesc.ccw = false;
  tankCmd_2.depthDesc.enabled = false;
  tankCmd_2.depthDesc.func = gapi::CompareFn::LESS;
  tankCmd_2.depthDesc.mask = true;
  tankCmd_2.depthDesc.near = 0;
  tankCmd_2.depthDesc.far = 0;
  tankCmd_2.stencilDesc.enabled = true;
  tankCmd_2.stencilDesc.front.func = gapi::CompareFn::EQUAL;
  tankCmd_2.stencilDesc.front.fail = gapi::StencilOp::KEEP;
  tankCmd_2.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
  tankCmd_2.stencilDesc.front.depthPass = gapi::StencilOp::INCREMENT;
  tankCmd_2.stencilDesc.front.rmask = 0xFFFFFF;
  tankCmd_2.stencilDesc.front.wmask = tankCmd_2.stencilDesc.front.rmask;
  tankCmd_2.stencilDesc.front.reference = 1;
  tankCmd_2.stencilDesc.back = tankCmd_2.stencilDesc.front;
  tankCmd_2.geometry = tankSilhouetteGeom_;
  tankCmd_2.material = tankSilhouetteMtrl_;
  tankCmd_2.tfrm = math::mat4f_t();  // Identity
  tankCmd_2.proj = matProj;
  tankCmd_2.view = math::mat4f_t();
  renderSubqueue_->post(tankCmd_2);

  render::pipeline::ForwardRenderCommand tankCmd_3;
  tankCmd_3.stage = 0;
  tankCmd_3.blendDesc.enabled = true;
  tankCmd_3.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
  tankCmd_3.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
  tankCmd_3.blendDesc.mask = true;
  tankCmd_3.rasterizerDesc.mode = gapi::CullFace::BACK;
  tankCmd_3.rasterizerDesc.ccw = false;
  tankCmd_3.depthDesc.enabled = true;
  tankCmd_3.depthDesc.func = gapi::CompareFn::LESS;
  tankCmd_3.depthDesc.mask = true;
  tankCmd_3.depthDesc.near = 0;
  tankCmd_3.depthDesc.far = 0;
  tankCmd_3.stencilDesc.enabled = false;
  tankCmd_3.stencilDesc.front.func = gapi::CompareFn::EQUAL;
  tankCmd_3.stencilDesc.front.fail = gapi::StencilOp::KEEP;
  tankCmd_3.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
  tankCmd_3.stencilDesc.front.depthPass = gapi::StencilOp::INCREMENT;
  tankCmd_3.stencilDesc.front.rmask = 0xFFFFFF;
  tankCmd_3.stencilDesc.front.wmask = tankCmd_3.stencilDesc.front.rmask;
  tankCmd_3.stencilDesc.front.reference = 1;
  tankCmd_3.stencilDesc.back = tankCmd_3.stencilDesc.front;
  tankCmd_3.geometry = tankGeom_;
  tankCmd_3.material = tankMtrl_;
  tankCmd_3.tfrm = math::mat4f_t();  // Identity
  tankCmd_3.proj = matProj;
  tankCmd_3.view = math::mat4f_t();
  renderSubqueue_->post(tankCmd_3);

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
