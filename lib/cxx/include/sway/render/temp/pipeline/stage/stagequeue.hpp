#ifndef SWAY_RENDER_STAGEQUEUE_HPP
#define SWAY_RENDER_STAGEQUEUE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/temp/pipeline/stage/stage.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class StageQueue {
  DECLARE_REF_ARRAY(StageQueue, StageGroupIndexLatest)

public:
#pragma region "Ctors/Dtor"

  StageQueue() {}

  DTOR_VIRTUAL_DEFAULT(StageQueue);

#pragma endregion

  auto addStage() -> Stage::SharedPtr_t {
    stages_.push_back(std::make_shared<Stage>());
    return stages_.back();
  }

  auto getStages() -> Stage::SharedPtrVec_t { return stages_; }

  auto getNumOfStages() const -> u32_t { return stages_.size(); }

private:
  Stage::SharedPtrVec_t stages_{};
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_STAGEQUEUE_HPP
