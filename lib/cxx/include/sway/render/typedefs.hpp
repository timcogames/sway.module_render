#ifndef SWAY_RENDER_TYPEDEFS_HPP
#define SWAY_RENDER_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

// clang-format off
#define CONTAINER_TYPE_(PRE, TYPE) PRE##TYPE##_t

#define DECLARE_REF_ARRAY(OBJ, SIZE)                                          \
  public: using CONTAINER_TYPE_(Ref, Arr) = std::array<OBJ, SIZE>;

#define DECLARE_PTR_ARRAY(OBJ, TYPE, SIZE)                                    \
  public: using CONTAINER_TYPE_(TYPE, Arr) = std::array<OBJ::TYPE##_t, SIZE>;

#define DECLARE_PTR_VECTOR(OBJ, TYPE)                                         \
  public:                                                                     \
    using Index_t = i32_t;                                                    \
    using CONTAINER_TYPE_(TYPE, Vec) = std::vector<OBJ::TYPE##_t>;
// clang-format on

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

namespace typedefs {
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
}  // namespace typedefs

using RenderSubqueueSharedPtrVec_t = std::vector<typedefs::RenderSubqueueSharedPtr_t>;
using RenderQueueSharedPtrVec_t = std::vector<typedefs::RenderQueueSharedPtr_t>;
using GeomVertexAttribSharedPtrMap_t = std::map<gapi::VertexSemantic, typedefs::GeomVertexAttribBaseSharedPtr_t>;

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TYPEDEFS_HPP
