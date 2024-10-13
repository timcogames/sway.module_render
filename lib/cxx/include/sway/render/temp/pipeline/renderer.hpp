#ifndef SWAY_RENDER_RENDERER_HPP
#define SWAY_RENDER_RENDERER_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/temp/pipeline/renderertypes.hpp>
#include <sway/render/temp/pipeline/stage/stagegroupindexes.hpp>
#include <sway/render/temp/pipeline/stage/stagequeue.hpp>

#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Renderer {
  DECLARE_CLASS_POINTER_ALIASES(Renderer)
  DECLARE_PTR_VECTOR(Renderer, SharedPtr)

public:
#pragma region "Ctors/Dtor"

  Renderer(RendererType::Enum type)
      : type_(type) {}

  DTOR_VIRTUAL_DEFAULT(Renderer);

#pragma endregion

  auto getStageQueue(StageGroupIndex::Enum group) -> StageQueue { return queues_[core::detail::toBase(group)]; }

  auto type() const -> RendererType::Enum { return type_; }

private:
  StageQueue::RefArr_t queues_;
  RendererType::Enum type_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERER_HPP
