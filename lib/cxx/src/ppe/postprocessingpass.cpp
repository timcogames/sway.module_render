#include <sway/render/ppe/postprocessingpass.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

PostProcessingPass::PostProcessingPass(const std::string &name, ScreenQuad::SharedPtr_t quad)
    : RenderPass(name)
    , target_(nullptr)
    , state_(nullptr)
    , quad_(quad)
    , enabled_(true) {}

void PostProcessingPass::apply(gapi::Framebuffer::Ptr_t framebuf) {
  if (!enabled_) {
    return;
  }
}

void PostProcessingPass::execute() {
  if (!enabled_) {
    return;
  }

  auto tex = target_->getColorBuffer()->getTexture();
  auto texUid = tex->getUid();

  std::cout << "texUid " << texUid.value() << std::endl;

  tex->setActive(texUid.value());
  tex->bind();

  quad_->getShader()->setUniform1i("tex_color", texUid.value());
  quad_->draw();

  tex->unbind();
}

NS_END()  // namespace render
NS_END()  // namespace sway
