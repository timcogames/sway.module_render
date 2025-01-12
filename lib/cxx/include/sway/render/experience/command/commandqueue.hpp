#ifndef SWAY_RENDER_EXPERIENCE_COMMANDQUEUE_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDQUEUE_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/commandbufferexecutor.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class CommandQueue {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  CommandQueue() = default;

  DTOR_DEFAULT(CommandQueue);

  /** @} */
#pragma endregion

#pragma region "Adding/Removing"

  void add(CommandBufferTypedefs::Ptr_t buf);

  void remove(const CommandBufferTypedefs::UniquePtr_t &buf);

#pragma endregion

#pragma region "Processing"

  void process(DeviceContextTypedefs::Ptr_t context);

#pragma endregion

#pragma region "Getters/Setters"

  [[nodiscard]] auto getCommandBuffers() -> CommandBufferTypedefs::Container_t & { return buffers_; }

  [[nodiscard]] auto getExecutor() -> CommandBufferExecutor & { return executor_; }

#pragma endregion

private:
  CommandBufferTypedefs::Container_t buffers_;
  CommandBufferExecutor executor_;
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDQUEUE_HPP
