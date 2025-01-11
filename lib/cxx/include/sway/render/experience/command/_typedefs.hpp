#ifndef SWAY_RENDER_EXPERIENCE_COMMAND_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_COMMAND_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class Command;
namespace CommandTypedefs {
using Ptr_t = Command *;
using UniquePtr_t = std::unique_ptr<Command>;
using Queue_t = std::queue<UniquePtr_t>;
}  // namespace CommandTypedefs

class BindPipelineCommand;
namespace BindPipelineCommandTypedefs {
using Ptr_t = BindPipelineCommand *;
}  // namespace BindPipelineCommandTypedefs

class BeginPassCommand;
namespace BeginPassCommandTypedefs {
using Ptr_t = BeginPassCommand *;
}  // namespace BeginPassCommandTypedefs

class ClearCommand;
namespace ClearCommandTypedefs {
using Ptr_t = ClearCommand *;
}  // namespace ClearCommandTypedefs

class DrawCommand;
namespace DrawCommandTypedefs {
using Ptr_t = DrawCommand *;
}  // namespace DrawCommandTypedefs

class EndPassCommand;
namespace EndPassCommandTypedefs {
using Ptr_t = EndPassCommand *;
}  // namespace EndPassCommandTypedefs

class CommandHandler;
namespace CommandHandlerTypedefs {
using Ptr_t = CommandHandler *;
using UniquePtr_t = std::unique_ptr<CommandHandler>;
using Container_t = std::unordered_map<std::string, UniquePtr_t>;
}  // namespace CommandHandlerTypedefs

class CommandBuffer;
namespace CommandBufferTypedefs {
using Ref_t = std::reference_wrapper<CommandBuffer>;
using RefArray_t = std::vector<Ref_t>;
using OptionalRef_t = std::optional<Ref_t>;
using Ptr_t = CommandBuffer *;
using UniquePtr_t = std::unique_ptr<CommandBuffer>;
using Container_t = std::vector<UniquePtr_t>;
}  // namespace CommandBufferTypedefs

class CommandQueue;
namespace CommandQueueTypedefs {
using SharedPtr_t = std::shared_ptr<CommandQueue>;
using UniquePtr_t = std::unique_ptr<CommandQueue>;
}  // namespace CommandQueueTypedefs

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMAND_TYPEDEFS_HPP
