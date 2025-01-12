#include <sway/render/experience/technique/technique.hpp>
#include <sway/render/experience/technique/techniquemanager.hpp>

namespace sway::render {
NS_BEGIN(experience)

Technique::Technique(const std::string &name)
    : passes_(std::make_unique<Cache>()) {}

NS_END()  // namespace experience
}  // namespace sway::render
