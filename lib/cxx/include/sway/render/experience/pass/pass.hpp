#ifndef SWAY_RENDER_EXPERIENCE_PASS_HPP
#define SWAY_RENDER_EXPERIENCE_PASS_HPP

#include <sway/render/experience/pass/_typedefs.hpp>
#include <sway/render/experience/pass/passdescriptor.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/experience/utility/cacheable.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Pass : public core::misc::Enableable, public Cacheable {
public:
#pragma region "Static methods"

  static auto get(TechniqueTypedefs::Ptr_t tech, const PassDescriptor &desc) -> PassTypedefs::Ptr_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  Pass(const PassDescriptor &desc);

  DTOR_VIRTUAL_DEFAULT(Pass);

#pragma endregion

private:
  bool dirty_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PASS_HPP
