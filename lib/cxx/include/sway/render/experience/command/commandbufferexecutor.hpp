#ifndef SWAY_RENDER_EXPERIENCE_COMMANDBUFFEREXECUTOR_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDBUFFEREXECUTOR_HPP

#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/commandhandler.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class CommandBufferExecutor {
public:
#pragma region "Ctors/Dtor"

  CommandBufferExecutor() = default;

  DTOR_DEFAULT(CommandBufferExecutor);

#pragma endregion

  void registerHandler(CommandHandlerTypedefs::UniquePtr_t &&handler);

  void submit(DeviceContextTypedefs::Ptr_t context, const CommandBufferTypedefs::RefArray_t &refs);

protected:
  void run_(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t cmd);

private:
  CommandHandlerTypedefs::Container_t handlers_;
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDBUFFEREXECUTOR_HPP
