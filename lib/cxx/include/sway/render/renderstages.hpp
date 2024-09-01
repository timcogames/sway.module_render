#ifndef SWAY_RENDER_RENDERSTAGES_HPP
#define SWAY_RENDER_RENDERSTAGES_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

enum class RenderStage : i32_t { IDX_DEPTH = GLOB_IDX_INITIAL, IDX_COLOR, IDX_STENCIL, Latest };

#define MAX_RENDER_STAGES core::detail::toBase(RenderStage::Latest)

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERSTAGES_HPP
