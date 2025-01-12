#ifndef SWAY_RENDER_EXPERIENCE_GRAPHICSPASS_HPP
#define SWAY_RENDER_EXPERIENCE_GRAPHICSPASS_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandqueue.hpp>
#include <sway/render/experience/pass/_typedefs.hpp>
#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/pass/passdescriptor.hpp>
#include <sway/render/experience/pipeline/specs/graphicspipelinestate.hpp>

namespace sway::render {
NS_BEGIN(experience)

class GraphicsPass : public Pass {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  GraphicsPass(const PassDescriptor &desc);

  DTOR_VIRTUAL(GraphicsPass);

  /** @} */
#pragma endregion

#pragma region "Overridden Pass methods"

  MTHD_VIRTUAL_OVERRIDE(void execute(DeviceContextTypedefs::Ptr_t context));

  MTHD_VIRTUAL_OVERRIDE(auto getType() const -> PassType::Enum) { return PassType::Enum::GRAPHICS; }

#pragma endregion

#pragma region "Getters/Setters"

  [[nodiscard]] auto getQueue() -> CommandQueueTypedefs::UniquePtr_t & { return queue_; }

  void setQueue(CommandQueueTypedefs::UniquePtr_t queue) { queue_ = std::move(queue); }

  [[nodiscard]] auto getState() -> GraphicsPipelineState { return state_; }

  void setState(const GraphicsPipelineState &state) { state_ = state; }

#pragma endregion

private:
  CommandQueueTypedefs::UniquePtr_t queue_;
  GraphicsPipelineState state_;
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_GRAPHICSPASS_HPP
