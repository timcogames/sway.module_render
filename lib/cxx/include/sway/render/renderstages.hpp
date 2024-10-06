#ifndef SWAY_RENDER_RENDERSTAGES_HPP
#define SWAY_RENDER_RENDERSTAGES_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

enum class RenderStage : i32_t { IDX_COLOR = GLOB_IDX_INITIAL, IDX_DEPTH, IDX_STENCIL, Latest };

#define MAX_RENDER_STAGES core::detail::toBase(RenderStage::Latest)

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERSTAGES_HPP
