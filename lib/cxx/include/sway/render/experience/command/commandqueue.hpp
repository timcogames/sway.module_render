#ifndef SWAY_RENDER_EXPERIENCE_COMMANDQUEUE_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDQUEUE_HPP

#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/commandbufferexecutor.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class CommandQueue {
public:
#pragma region "Ctors/Dtor"

  CommandQueue() = default;

  DTOR_DEFAULT(CommandQueue);

#pragma endregion

  auto createBuffer(const CommandBufferDescriptor &desc) -> CommandBufferTypedefs::OptionalRef_t;

  void add(CommandBufferTypedefs::Ptr_t buf);

  void remove(const CommandBufferTypedefs::UniquePtr_t &buf);

  void process(u32_t idx);

#pragma region "Getters/Setters"

  [[nodiscard]] auto subqueue(u32_t idx) -> CommandBufferTypedefs::SubContainer_t & { return groups_[idx]; }

#pragma endregion

private:
  CommandBufferTypedefs::SubContainerArray_t groups_;
  CommandBufferExecutor executor_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDQUEUE_HPP
