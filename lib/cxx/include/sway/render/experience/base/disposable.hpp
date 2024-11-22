#ifndef SWAY_RENDER_EXPERIENCE_DISPOSABLE_HPP
#define SWAY_RENDER_EXPERIENCE_DISPOSABLE_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Disposable {
public:
  PURE_VIRTUAL(void dispose());
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_DISPOSABLE_HPP
