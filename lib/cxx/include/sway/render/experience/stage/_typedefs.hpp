#ifndef SWAY_RENDER_EXPERIENCE_STAGE_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_STAGE_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
NS_BEGIN(experience)

class Stage;
namespace StageTypedefs {
using UniquePtr_t = std::unique_ptr<Stage>;
using Container_t = std::vector<UniquePtr_t>;
}  // namespace StageTypedefs

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_STAGE_TYPEDEFS_HPP
