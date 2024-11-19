#ifndef SWAY_RENDER_EXPERIENCE_COMMANDBUFFER_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDBUFFER_HPP

#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/command.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct CommandBufferCreateInfo {
  u32_t group;
  u32_t priority;
};

class CommandBuffer {
public:
#pragma region "Ctors/Dtor"

  CommandBuffer(const CommandBufferCreateInfo &info)
      : group_(info.group)
      , priority_(info.priority) {}

  DTOR_DEFAULT(CommandBuffer);

#pragma endregion

  void enqueue(CommandTypedefs::UniquePtr_t &&cmd);

  void dequeue();

  auto peek(CommandType::Enum *type) const -> CommandTypedefs::Ptr_t;

  [[nodiscard]] auto empty() const -> bool;

#pragma region "Getters/Setters"

  [[nodiscard]] auto commands() const -> CommandTypedefs::Queue_t const & { return commands_; }

  [[nodiscard]] auto group() const -> u32_t { return group_; }

  [[nodiscard]] auto priority() const -> u32_t { return priority_; }

#pragma endregion

private:
  CommandTypedefs::Queue_t commands_;
  u32_t group_;
  u32_t priority_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDBUFFER_HPP
