#ifndef SWAY_RENDER_EXPERIENCE_COMMANDQUEUE_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDQUEUE_HPP

#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/commandbufferexecutor.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class CommandQueue {
public:
#pragma region "Ctors/Dtor"

  CommandQueue() = default;

  DTOR_DEFAULT(CommandQueue);

#pragma endregion

#pragma region "Adding/Removing"

  void add(CommandBufferTypedefs::Ptr_t buf);

  void remove(const CommandBufferTypedefs::UniquePtr_t &buf);

#pragma endregion

#pragma region "Processing"

  void process(OperationContext *ctx);

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
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDQUEUE_HPP
