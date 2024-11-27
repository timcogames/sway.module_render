#ifndef SWAY_RENDER_EXPERIENCE_PASS_HPP
#define SWAY_RENDER_EXPERIENCE_PASS_HPP

#include <sway/render/experience/pass/_typedefs.hpp>
#include <sway/render/experience/pass/passdescriptor.hpp>
#include <sway/render/experience/pipeline/pipelinedescriptor.hpp>
#include <sway/render/experience/utility/disposable.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Pass : public core::misc::Enableable, public Disposable {
public:
#pragma region "Static methods"

  static auto get(const PipelineDescriptor &pipeDesc, const PassDescriptor &passDesc) -> PassTypedefs::Ptr_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  Pass(const PassDescriptor &desc);

  DTOR_VIRTUAL_DEFAULT(Pass);

#pragma endregion

#pragma region "Override Disposable methods"

  MTHD_OVERRIDE(void dispose());

#pragma endregion

private:
  bool dirty_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PASS_HPP
