#include <sway/render/experience/technique/technique.hpp>
#include <sway/render/experience/technique/techniquemanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

Technique::Technique(const std::string &name)
    : passes_(std::make_unique<Cache>()) {}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
