#ifndef SWAY_RENDER_EXPERIENCE_COMMANDQUEUESORTER_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDQUEUESORTER_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

DECLARE_ENUM(SortOrder, ASCENDING, DESCENDING)

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
      case SortOrder::Enum::NONE:
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
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDQUEUESORTER_HPP
