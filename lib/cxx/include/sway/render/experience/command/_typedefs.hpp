#ifndef SWAY_RENDER_EXPERIENCE_COMMAND_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_COMMAND_TYPEDEFS_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Command;
namespace CommandTypedefs {
using Ptr_t = Command *;
using UniquePtr_t = std::unique_ptr<Command>;
using Queue_t = std::queue<UniquePtr_t>;
}  // namespace CommandTypedefs

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
using SubContainer_t = std::vector<UniquePtr_t>;
using SubContainerArray_t = std::array<SubContainer_t, 2 /* OPAQUE/TRANSPARENT */>;
}  // namespace CommandBufferTypedefs

class CommandQueue;
namespace CommandQueueTypedefs {
using SharedPtr_t = std::shared_ptr<CommandQueue>;
using UniquePtr_t = std::unique_ptr<CommandQueue>;
}  // namespace CommandQueueTypedefs

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMAND_TYPEDEFS_HPP
