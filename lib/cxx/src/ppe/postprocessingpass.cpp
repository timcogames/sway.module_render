#include <sway/render/ppe/postprocessingpass.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

PostProcessingPass::PostProcessingPass(const std::string &name, typedefs::ScreenQuadSharedPtr_t quad)
    : target_(nullptr)
    , state_(nullptr)
    , quad_(quad)
    , enabled_(true) {}

void PostProcessingPass::apply(gapi::typedefs::FrameBufferPtr_t framebuf) {
  if (!enabled_) {
    return;
  }
}

void PostProcessingPass::execute() {
  if (!enabled_) {
    return;
  }

  auto sceneTex = target_->getColorBuffer()->getTexture();
  auto sceneTexUid = sceneTex->getUniqueId();

  sceneTex->setActive(sceneTexUid.value());
  sceneTex->bind();

  quad_->getShader()->setUniform1i("scene_sampler", sceneTexUid.value());
  // quad_->getShader()->setUniform1i("depth_sampler", depthTexUid.value());
  quad_->draw();

  sceneTex->unbind();
}

NS_END()  // namespace render
NS_END()  // namespace sway
