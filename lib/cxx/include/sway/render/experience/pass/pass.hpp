#ifndef SWAY_RENDER_EXPERIENCE_PASS_HPP
#define SWAY_RENDER_EXPERIENCE_PASS_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/_typedefs.hpp>
#include <sway/render/experience/pass/_typedefs.hpp>
#include <sway/render/experience/pass/passdescriptor.hpp>
#include <sway/render/experience/pass/passtypes.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/stage/stage.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/experience/utility/cacheable.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup pass
 * @{
 */

class Pass : public core::Enableable, public Cacheable {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto get(TechniqueTypedefs::Ptr_t tech, const PassDescriptor &desc) -> PassTypedefs::Ptr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  Pass(const PassDescriptor &desc);

  DTOR_VIRTUAL_DEFAULT(Pass);

#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(void execute(DeviceContextTypedefs::Ptr_t context));

  PURE_VIRTUAL(auto getType() const -> PassType::Enum);

#pragma endregion

private:
  StageTypedefs::Container_t stages_;
  bool dirty_;
};

/**
 * end of pass group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PASS_HPP
