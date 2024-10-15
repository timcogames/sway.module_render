#ifndef SWAY_RENDER_TYPEDEFS_HPP
#define SWAY_RENDER_TYPEDEFS_HPP

#include <sway/render/prereqs.hpp>

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

DECLARE_PTR_TYPES(VertexChannel)
DECLARE_PTR_TYPES(GeomVertexAttribBase)
DECLARE_PTR_TYPES(Geom)
DECLARE_PTR_TYPES(GeomBuilder)
DECLARE_PTR_TYPES(Geometry)
DECLARE_PTR_TYPES(Effect)
DECLARE_PTR_TYPES(Material)
DECLARE_PTR_TYPES(MaterialManager)
DECLARE_PTR_TYPES(RenderQueue)
DECLARE_PTR_TYPES(RenderQueuePass)
DECLARE_PTR_TYPES(RenderSubqueue)
DECLARE_PTR_TYPES(RenderSubsystem)
DECLARE_PTR_TYPES(PostProcessingPass)
DECLARE_PTR_TYPES(RenderTarget)
DECLARE_PTR_TYPES(RenderState)
DECLARE_PTR_TYPES(PostProcessing)
DECLARE_PTR_TYPES(Image)
DECLARE_PTR_TYPES(Sprite)
DECLARE_PTR_TYPES(ScreenQuad)

DECLARE_PTR_TYPES(Pipeline)
DECLARE_PTR_TYPES(Renderer)
DECLARE_PTR_TYPES(Pass)
DECLARE_PTR_TYPES(Stage)

using RenderSubqueueSharedPtrVec_t = std::vector<RenderSubqueueSharedPtr_t>;
using RenderQueueSharedPtrVec_t = std::vector<RenderQueueSharedPtr_t>;
using MaterialSharedPtrMap_t = std::map<std::string, MaterialSharedPtr_t>;
using GeomVertexAttribSharedPtrMap_t = std::map<gapi::VertexSemantic, GeomVertexAttribBaseSharedPtr_t>;

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TYPEDEFS_HPP
