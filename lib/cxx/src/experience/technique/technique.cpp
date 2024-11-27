
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/technique/technique.hpp>
#include <sway/render/experience/technique/techniquemanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

Technique::Technique(const PipelineDescriptor &desc)
    : Pipeline(desc) {}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
