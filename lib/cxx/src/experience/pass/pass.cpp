#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/technique/technique.hpp>
#include <sway/render/experience/utility/cache.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

auto Pass::get(TechniqueTypedefs::Ptr_t tech, const PassDescriptor &desc) -> PassTypedefs::Ptr_t {
  return tech->passes()->getOrCreate<PassDescriptor, Pass>(desc);
}

Pass::Pass(const PassDescriptor &desc)
    : dirty_(true) {}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
