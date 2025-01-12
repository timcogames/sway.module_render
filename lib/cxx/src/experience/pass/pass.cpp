#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/pass/specs/graphicspass.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/technique/technique.hpp>
#include <sway/render/experience/utility/cache.hpp>

namespace sway::render {
NS_BEGIN(experience)

auto Pass::get(TechniqueTypedefs::Ptr_t tech, const PassDescriptor &desc) -> PassTypedefs::Ptr_t {
  return tech->getPasses()->getOrCreate<GraphicsPass>(desc);
}

Pass::Pass(const PassDescriptor &desc)
    : dirty_(true) {}

NS_END()  // namespace experience
}  // namespace sway::render
