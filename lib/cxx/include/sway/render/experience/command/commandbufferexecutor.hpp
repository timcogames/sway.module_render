#ifndef SWAY_RENDER_EXPERIENCE_COMMANDBUFFEREXECUTOR_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDBUFFEREXECUTOR_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/commandhandler.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class CommandBufferExecutor {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  CommandBufferExecutor() = default;

  DTOR_DEFAULT(CommandBufferExecutor);

  /** @} */
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
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDBUFFEREXECUTOR_HPP
