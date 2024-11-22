
#include <sway/render/experience/pipeline/pipeline.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

Pipeline::Pipeline()
    : passes_(nullptr) {
  initialize();
}

void Pipeline::initialize() { passes_ = std::make_unique<PassCache>(); }

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
