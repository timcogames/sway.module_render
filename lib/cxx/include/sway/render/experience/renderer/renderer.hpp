#ifndef SWAY_RENDER_EXPERIENCE_RENDERER_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERER_HPP

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
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Renderer {
public:
#pragma region "Ctors/Dtor"

  Renderer(u32_t type);

  DTOR_VIRTUAL_DEFAULT(Renderer);

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
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_RENDERER_HPP
