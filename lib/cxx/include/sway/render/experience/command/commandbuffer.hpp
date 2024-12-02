#ifndef SWAY_RENDER_EXPERIENCE_COMMANDBUFFER_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDBUFFER_HPP

#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/command.hpp>
#include <sway/render/experience/command/commandbufferdescriptor.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class CommandBuffer {
public:
#pragma region "Ctors/Dtor"

  CommandBuffer(const CommandBufferDescriptor &desc)
      : group_(desc.group)
      , priority_(desc.priority) {}

  DTOR_DEFAULT(CommandBuffer);

#pragma endregion

  void enqueue(CommandTypedefs::UniquePtr_t &&cmd);

  void dequeue();

  auto peek(CommandType::Enum *type) const -> CommandTypedefs::Ptr_t;

#pragma region "Getters/Setters"

  [[nodiscard]] auto getCommands() const -> CommandTypedefs::Queue_t const & { return commands_; }

  [[nodiscard]] auto getGroup() const -> u32_t { return group_; }

  [[nodiscard]] auto getPriority() const -> u32_t { return priority_; }

  [[nodiscard]] auto getSize() const -> std::size_t { return commands_.size(); }

  [[nodiscard]] auto isEmpty() const -> bool { return commands_.empty(); }

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
