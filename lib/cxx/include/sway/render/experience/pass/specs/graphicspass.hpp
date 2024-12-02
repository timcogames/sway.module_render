#ifndef SWAY_RENDER_EXPERIENCE_GRAPHICSPASS_HPP
#define SWAY_RENDER_EXPERIENCE_GRAPHICSPASS_HPP

#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandqueue.hpp>
#include <sway/render/experience/pass/_typedefs.hpp>
#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/pass/passdescriptor.hpp>
#include <sway/render/experience/pipeline/pipelinestate.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class GraphicsPass : public Pass {
public:
#pragma region "Ctors/Dtor"

  GraphicsPass(const PassDescriptor &desc);

  DTOR_VIRTUAL_DEFAULT(GraphicsPass);

#pragma endregion

  void render();

#pragma region "Getters/Setters"

  [[nodiscard]] auto getQueue() -> CommandQueueTypedefs::UniquePtr_t & { return queue_; }

  void setQueue(CommandQueueTypedefs::UniquePtr_t queue) { queue_ = std::move(queue); }

  [[nodiscard]] auto getState() -> PipelineState { return state_; }

  void setState(const PipelineState &state) { state_ = state; }

#pragma endregion

private:
  CommandQueueTypedefs::UniquePtr_t queue_;
  PipelineState state_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_GRAPHICSPASS_HPP
