#ifndef SWAY_RENDER_EXPERIENCE_COMMANDQUEUESORTER_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDQUEUESORTER_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

// clang-format off
#define SORT_ORDER_LIST(ITEM) \
  ITEM(ASCENDING, 1) \
  ITEM(DESCENDING, 2)
// clang-format on

DECLARE_ENUM_U32(SortOrder, SORT_ORDER_LIST)

struct SortByPriorityInAscendingOrder {
  constexpr auto operator()(
      const CommandBufferTypedefs::UniquePtr_t &lhs, const CommandBufferTypedefs::UniquePtr_t &rhs) -> bool {
    return lhs->getPriority() < rhs->getPriority();
  }
};

struct SortByPriorityInDescendingOrder {
  constexpr auto operator()(
      const CommandBufferTypedefs::UniquePtr_t &lhs, const CommandBufferTypedefs::UniquePtr_t &rhs) -> bool {
    return lhs->getPriority() > rhs->getPriority();
  }
};

struct CommandQueueSorter {
  static void sort(CommandBufferTypedefs::Container_t &bufs, SortOrder::Enum order) {
    switch (order) {
      case SortOrder::Enum::ASCENDING:
        std::stable_sort(bufs.begin(), bufs.end(), SortByPriorityInAscendingOrder());
        break;
      case SortOrder::Enum::DESCENDING:
        std::stable_sort(bufs.begin(), bufs.end(), SortByPriorityInDescendingOrder());
        break;
      case SortOrder::Enum::INITIAL:
      default:
        break;
    }
  }
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDQUEUESORTER_HPP
