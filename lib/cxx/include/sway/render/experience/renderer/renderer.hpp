#ifndef SWAY_RENDER_EXPERIENCE_RENDERER_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERER_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandqueue.hpp>
#include <sway/render/experience/command/specs/beginpasscommandhandler.hpp>
#include <sway/render/experience/command/specs/bindpipelinecommandhandler.hpp>
#include <sway/render/experience/command/specs/clearcommandhandler.hpp>
#include <sway/render/experience/command/specs/drawcommandhandler.hpp>
#include <sway/render/experience/command/specs/endpasscommandhandler.hpp>
#include <sway/render/experience/pipeline/_typedefs.hpp>
#include <sway/render/experience/pipeline/specs/computepipeline.hpp>
#include <sway/render/experience/pipeline/specs/graphicspipeline.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/experience/technique/technique.hpp>

namespace sway::render {
NS_BEGIN(experience)

class Renderer {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Renderer(u32_t type);

  DTOR_VIRTUAL_DEFAULT(Renderer);

  /** @} */
#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(void render());

#pragma endregion

#pragma region "Getters/Setters"

  [[nodiscard]] auto getType() const -> u32_t { return type_; }

  [[nodiscard]] auto getTechnique() const -> TechniqueTypedefs::SharedPtr_t { return technique_; }

  void setTechnique(TechniqueTypedefs::SharedPtr_t tech) { technique_ = tech; }

#pragma endregion

private:
  void registerCommandHandlers_();

protected:
  u32_t type_;
  CommandQueueTypedefs::UniquePtr_t commandQueue_;
  TechniqueTypedefs::SharedPtr_t technique_;
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_RENDERER_HPP
