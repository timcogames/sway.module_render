#ifndef SWAY_RENDER_EXPERIENCE_PIPELINE_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINE_TYPEDEFS_HPP

#include <sway/render/experience/utility/cache.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Pipeline;
namespace PipelineTypedefs {
using Ptr_t = Pipeline *;
using UniquePtr_t = std::unique_ptr<Pipeline>;
using Container_t = std::unordered_map<u32_t, UniquePtr_t>;
using Cache_t = Cache<Pipeline>;
}  // namespace PipelineTypedefs

namespace PipelineCacheTypedefs {
using UniquePtr_t = std::unique_ptr<Cache<Pipeline>>;
}  // namespace PipelineCacheTypedefs

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINE_TYPEDEFS_HPP
