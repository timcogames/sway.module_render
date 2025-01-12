#ifndef SWAY_RENDER_TYPEDEFS_HPP
#define SWAY_RENDER_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {

class VertexChannel;
class GeomVertexAttribBase;
class Geom;
class GeomBuilder;
class Geometry;
class Effect;
class RenderQueue;
class RenderQueuePass;
class RenderSubqueue;
class RenderSubsystem;
class PostProcessingPass;
class RenderTarget;
class RenderState;
class PostProcessing;
class Sprite;
class ScreenQuad;

// namespace typedefs {
using GeomVertexAttribBaseSharedPtr_t = std::shared_ptr<GeomVertexAttribBase>;
using GeomBuilderPtr_t = GeomBuilder *;
using RenderQueueSharedPtr_t = std::shared_ptr<RenderQueue>;
using RenderSubqueueSharedPtr_t = std::shared_ptr<RenderSubqueue>;
using RenderSubqueueContainer_t = std::vector<RenderSubqueueSharedPtr_t>;
using RenderSubsystemPtr_t = RenderSubsystem *;
using RenderSubsystemSharedPtr_t = std::shared_ptr<RenderSubsystem>;
using RenderTargetSharedPtr_t = std::shared_ptr<RenderTarget>;
using RenderStateSharedPtr_t = std::shared_ptr<RenderState>;
using PostProcessingSharedPtr_t = std::shared_ptr<PostProcessing>;
using ScreenQuadSharedPtr_t = std::shared_ptr<ScreenQuad>;
// }  // namespace typedefs

using RenderSubqueueSharedPtrVec_t = std::vector<RenderSubqueueSharedPtr_t>;
using RenderQueueSharedPtrVec_t = std::vector<RenderQueueSharedPtr_t>;
using GeomVertexAttribSharedPtrMap_t = std::map<gapi::VertexSemantic, GeomVertexAttribBaseSharedPtr_t>;

}  // namespace sway::render

#endif  // SWAY_RENDER_TYPEDEFS_HPP
