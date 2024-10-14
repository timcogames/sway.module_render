#ifndef SWAY_RENDER_PIPELINE_HPP
#define SWAY_RENDER_PIPELINE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/temp/pipeline/stage/stagegroupindexes.hpp>
#include <sway/render/temp/pipeline/stage/stagequeue.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Pipeline {
  DECLARE_PTR_ALIASES(Pipeline)

public:
#pragma region "Ctors/Dtor"

  Pipeline() {}

  DTOR_VIRTUAL_DEFAULT(Pipeline);

#pragma endregion

  auto getStageQueue(StageGroupIndex::Enum group) -> StageQueue { return queues_[core::detail::toBase(group)]; }

private:
  StageQueue::RefArr_t queues_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PIPELINE_HPP
