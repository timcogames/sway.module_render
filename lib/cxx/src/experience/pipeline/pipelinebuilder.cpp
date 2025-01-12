
#include <sway/render/experience/pipeline/pipelinebuilder.hpp>

namespace sway::render {
NS_BEGIN(experience)

PipelineBuilder::PipelineBuilder() {}

void PipelineBuilder::createGraphicsPipeline(
    GraphicsPipelineTypedefs::Promise_t &&promise, const GraphicsPipelineDescriptor &desc) {
  promise.set_value(std::shared_ptr<GraphicsPipeline>(new GraphicsPipeline(desc)));
}

NS_END()  // namespace experience
}  // namespace sway::render
