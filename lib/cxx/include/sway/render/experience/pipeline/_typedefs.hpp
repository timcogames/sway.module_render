#ifndef SWAY_RENDER_EXPERIENCE_PIPELINE_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINE_TYPEDEFS_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

class Pipeline;
namespace PipelineTypedefs {
using Ptr_t = Pipeline *;
using UniquePtr_t = std::unique_ptr<Pipeline>;
}  // namespace PipelineTypedefs

class GraphicsPipeline;
namespace GraphicsPipelineTypedefs {
using Ptr_t = GraphicsPipeline *;
using UniquePtr_t = std::unique_ptr<GraphicsPipeline>;
using SharedPtr_t = std::shared_ptr<GraphicsPipeline>;
using SharedFuture_t = std::shared_future<SharedPtr_t>;
using Promise_t = std::promise<SharedPtr_t>;
using Container_t = std::unordered_map<u32_t, SharedFuture_t>;
}  // namespace GraphicsPipelineTypedefs

class ComputePipeline;
namespace ComputePipelineTypedefs {
using UniquePtr_t = std::unique_ptr<ComputePipeline>;
}  // namespace ComputePipelineTypedefs

class PipelineLibrary;
namespace PipelineLibraryTypedefs {
using UniquePtr_t = std::unique_ptr<PipelineLibrary>;
}  // namespace PipelineLibraryTypedefs

/**
 * end of pipeline group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINE_TYPEDEFS_HPP
