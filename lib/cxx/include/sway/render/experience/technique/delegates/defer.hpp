#ifndef SWAY_RENDER_EXPERIENCE_DEFER_HPP
#define SWAY_RENDER_EXPERIENCE_DEFER_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/experience/technique/techniquedelegate.hpp>

namespace sway::render {
NS_BEGIN(experience)

class DeferTechniqueDelegate : public TechniqueDelegate {
public:
  static void create(Technique &tech, const TechniqueMetadata &meta);
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_DEFER_HPP
