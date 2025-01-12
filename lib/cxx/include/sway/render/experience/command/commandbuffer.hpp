#ifndef SWAY_RENDER_EXPERIENCE_COMMANDBUFFER_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDBUFFER_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/command.hpp>
#include <sway/render/experience/command/commandbufferdescriptor.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class CommandBuffer {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto create(CommandQueueTypedefs::UniquePtr_t &owner, const CommandBufferDescriptor &desc)
      -> CommandBufferTypedefs::OptionalRef_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  CommandBuffer(const CommandBufferDescriptor &desc)
      : priority_(desc.priority) {}

  DTOR_DEFAULT(CommandBuffer);

  /** @} */
#pragma endregion

  void enqueue(CommandTypedefs::UniquePtr_t &&cmd);

  void dequeue();

  auto peek(CommandType::Enum *type) const -> CommandTypedefs::Ptr_t;

#pragma region "Getters/Setters"

  [[nodiscard]] auto getCommands() const -> CommandTypedefs::Queue_t const & { return commands_; }

  [[nodiscard]] auto getPriority() const -> u32_t { return priority_; }

  [[nodiscard]] auto getSize() const -> std::size_t { return commands_.size(); }

  [[nodiscard]] auto isEmpty() const -> bool { return commands_.empty(); }

#pragma endregion

private:
  CommandTypedefs::Queue_t commands_;
  u32_t priority_;
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDBUFFER_HPP
