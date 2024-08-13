#ifndef SWAY_RENDER_PREREQS_HPP
#define SWAY_RENDER_PREREQS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>

#include <algorithm>  // std::sort
#include <functional>  // std::bind
#include <iostream>  // std::cout
#include <memory>  // std::shared_ptr, std::make_shared
#include <unordered_map>  // std::unordered_map
#include <vector>  // std::vector

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class VertexChannel;
template <typename TYPE>
class GeometryVertexChannel;
class GeometryData;
class Effect;
class Geometry;
class RenderSubqueue;
class RenderQueue;
class RenderSubsystem;

using VertexChannelRef_t = std::shared_ptr<VertexChannel>;
using VertexChannelRefMap_t = std::map<gapi::VertexSemantic, VertexChannelRef_t>;

using EffectPtr_t = Effect *;

using GeometryRef_t = std::shared_ptr<Geometry>;
using GeometryRefVec_t = std::vector<GeometryRef_t>;

using RenderSubqueuePtr_t = RenderSubqueue *;
using RenderSubqueueSharedPtr_t = std::shared_ptr<RenderSubqueue>;
using RenderSubqueueRefVec_t = std::vector<RenderSubqueueSharedPtr_t>;

using RenderQueuePtr_t = RenderQueue *;
using RenderQueueSharedPtr_t = std::shared_ptr<RenderQueue>;
using RenderQueueRefVector_t = std::vector<RenderQueueSharedPtr_t>;

using RenderSubsystemPtr_t = RenderSubsystem *;
using RenderSubsystemSharedPtr_t = std::shared_ptr<RenderSubsystem>;

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PREREQS_HPP
