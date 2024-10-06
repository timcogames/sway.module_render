#ifndef SWAY_RENDER_FLIPPABLE_HPP
#define SWAY_RENDER_FLIPPABLE_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/flipper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

struct Flippable {
  static auto compute(const math::rect4f_t &origin,
      core::detail::EnumClassBitset<Flipper> flips) -> std::array<f32_t, math::vec4f_t::DataElementCount_t> {
    std::array<f32_t, math::vec4f_t::DataElementCount_t> result;

    auto flippedHorz = flips.has(Flipper::HORZ);
    result[core::detail::toBase(flippedHorz ? math::RectEdge::Enum::IDX_R : math::RectEdge::Enum::IDX_L)] =
        origin.getL();
    result[core::detail::toBase(flippedHorz ? math::RectEdge::Enum::IDX_L : math::RectEdge::Enum::IDX_R)] =
        origin.getR();

    auto flippedVert = flips.has(Flipper::VERT);
    result[core::detail::toBase(flippedVert ? math::RectEdge::Enum::IDX_B : math::RectEdge::Enum::IDX_T)] =
        origin.getT();
    result[core::detail::toBase(flippedVert ? math::RectEdge::Enum::IDX_T : math::RectEdge::Enum::IDX_B)] =
        origin.getB();

    return result;
  }

  static auto asRect(const math::rect4f_t &origin, core::detail::EnumClassBitset<Flipper> flips) -> math::rect4f_t {
    return math::rect4f_t(Flippable::compute(origin, flips));
  }
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_FLIPPABLE_HPP
