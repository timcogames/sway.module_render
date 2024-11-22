#ifndef SWAY_RENDER_EXPERIENCE_TECHNIQUE_HPP
#define SWAY_RENDER_EXPERIENCE_TECHNIQUE_HPP

#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Technique : public Pipeline {
public:
#pragma region "Ctors/Dtor"

  Technique(const std::string &name) {}

  DTOR_VIRTUAL_DEFAULT(Technique);

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_TECHNIQUE_HPP
