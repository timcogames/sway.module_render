#ifndef SWAY_RENDER_EXPERIENCE_RENDERER_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERER_HPP

#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/experience/technique/technique.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Renderer {
public:
#pragma region "Static methods"

#pragma endregion

#pragma region "Ctors/Dtor"

  Renderer(u32_t type)
      : type_(type) {}

  DTOR_VIRTUAL_DEFAULT(Renderer);

#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(void render());

#pragma endregion

#pragma region "Getters/Setters"

  [[nodiscard]] inline auto type() const -> u32_t { return type_; }

  [[nodiscard]] inline auto technique() const -> TechniqueTypedefs::SharedPtr_t { return technique_; }

  void setTechnique(TechniqueTypedefs::SharedPtr_t technique) { technique_ = technique; }

#pragma endregion

protected:
  u32_t type_;
  TechniqueTypedefs::SharedPtr_t technique_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_RENDERER_HPP
