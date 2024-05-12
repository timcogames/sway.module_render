#ifndef SWAY_RENDER_FLIPPABLE_HPP
#define SWAY_RENDER_FLIPPABLE_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/flipper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct Flippable {
  static auto compute(const math::rect4f_t &origin,
      core::detail::EnumClassBitset<Flipper> flips) -> std::array<f32_t, math::vec4f_t::DataElementCount_t> {
    std::array<f32_t, math::vec4f_t::DataElementCount_t> result;

    auto flippedHorz = flips.has(Flipper::HORZ);
    result[core::detail::toUnderlying(flippedHorz ? math::RectEdge::IDX_R : math::RectEdge::IDX_L)] = origin.getL();
    result[core::detail::toUnderlying(flippedHorz ? math::RectEdge::IDX_L : math::RectEdge::IDX_R)] = origin.getR();

    auto flippedVert = flips.has(Flipper::VERT);
    result[core::detail::toUnderlying(flippedVert ? math::RectEdge::IDX_B : math::RectEdge::IDX_T)] = origin.getT();
    result[core::detail::toUnderlying(flippedVert ? math::RectEdge::IDX_T : math::RectEdge::IDX_B)] = origin.getB();

    return result;
  }
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_FLIPPABLE_HPP
