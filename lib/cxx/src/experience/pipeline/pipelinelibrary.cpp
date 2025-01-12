
#include <sway/render/experience/pipeline/pipelinebuilder.hpp>
#include <sway/render/experience/pipeline/pipelinelibrary.hpp>

namespace sway::render {
NS_BEGIN(experience)

PipelineLibrary::PipelineLibrary() {}

auto PipelineLibrary::getGraphicsPipeline(const GraphicsPipelineDescriptor &desc)
    -> GraphicsPipelineTypedefs::SharedFuture_t {
  GraphicsPipelineTypedefs::Promise_t promise;
  auto [inserted, _] = pipelines_.emplace(desc.getHash(), promise.get_future());
  PipelineBuilder::createGraphicsPipeline(std::move(promise), desc);
  return inserted->second;
}

NS_END()  // namespace experience
}  // namespace sway::render
