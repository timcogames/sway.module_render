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

  tex->setActive(texUid.value());
  tex->bind();

  math::mat4f_t proj;
  proj.setData(math::Projection(
      (struct math::ProjectionDescription){.rect = {{-1.0F /* L */, 1.0F /* B->T */, 1.0F /* R */, -1.0F /* T->B
      */}},
          .fov = 0,
          .aspect = 800 / 600,
          .znear = 0.0F,
          .zfar = 10.0F})
                   .makeOrtho());

  math::mat4f_t view;
  view = math::xform3f_t::translate(view, -1.0F, -1.0F, 0.0F);

  auto vp = view * proj;

  math::mat4f_t tfrm;

  quad_->getShader()->setUniformMat4f("mat_view_proj", vp);
  quad_->getShader()->setUniformMat4f("mat_tfrm", tfrm);
  quad_->getShader()->setUniform1i("tex_color", texUid.value());
  quad_->draw();

  tex->unbind();
}

NS_END()  // namespace render
NS_END()  // namespace sway
