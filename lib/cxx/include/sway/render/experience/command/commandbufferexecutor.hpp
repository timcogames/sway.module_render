#ifndef SWAY_RENDER_EXPERIENCE_COMMANDBUFFEREXECUTOR_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDBUFFEREXECUTOR_HPP

#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class CommandBufferExecutor {
public:
#pragma region "Ctors/Dtor"

  CommandBufferExecutor() = default;

  DTOR_DEFAULT(CommandBufferExecutor);

#pragma endregion

  void submit(const CommandBufferTypedefs::RefArray_t &refs);

private:
  void handleBeginPass_(CommandTypedefs::Ptr_t cmd) { std::cout << "Handling BEGIN_PASS" << std::endl; }

  void handleDraw_(CommandTypedefs::Ptr_t cmd) { std::cout << "Handling DRAW" << std::endl; }

  void handleEndPass_(CommandTypedefs::Ptr_t cmd) { std::cout << "Handling END_PASS" << std::endl; }
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDBUFFEREXECUTOR_HPP
