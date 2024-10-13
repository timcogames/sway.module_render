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

DECLARE_CLASS_POINTER_TYPES(VertexChannel)
DECLARE_CLASS_POINTER_TYPES(GeomVertexAttribBase)
DECLARE_CLASS_POINTER_TYPES(Geom)
DECLARE_CLASS_POINTER_TYPES(GeomBuilder)
DECLARE_CLASS_POINTER_TYPES(Geometry)
DECLARE_CLASS_POINTER_TYPES(Effect)
DECLARE_CLASS_POINTER_TYPES(Material)
DECLARE_CLASS_POINTER_TYPES(MaterialManager)
DECLARE_CLASS_POINTER_TYPES(RenderPass)
DECLARE_CLASS_POINTER_TYPES(RenderPassManager)
DECLARE_CLASS_POINTER_TYPES(RenderQueue)
DECLARE_CLASS_POINTER_TYPES(RenderQueuePass)
DECLARE_CLASS_POINTER_TYPES(RenderSubqueue)
DECLARE_CLASS_POINTER_TYPES(RenderSubsystem)
DECLARE_CLASS_POINTER_TYPES(PostProcessingPass)
DECLARE_CLASS_POINTER_TYPES(RenderTarget)
DECLARE_CLASS_POINTER_TYPES(RenderState)
DECLARE_CLASS_POINTER_TYPES(PostProcessing)
DECLARE_CLASS_POINTER_TYPES(Image)
DECLARE_CLASS_POINTER_TYPES(Sprite)
DECLARE_CLASS_POINTER_TYPES(ScreenQuad)

DECLARE_CLASS_POINTER_TYPES(Pipeline)
DECLARE_CLASS_POINTER_TYPES(Renderer)
DECLARE_CLASS_POINTER_TYPES(Pass)
DECLARE_CLASS_POINTER_TYPES(Stage)

using RenderSubqueueSharedPtrVec_t = std::vector<RenderSubqueueSharedPtr_t>;
using RenderQueueSharedPtrVec_t = std::vector<RenderQueueSharedPtr_t>;
using MaterialSharedPtrMap_t = std::map<std::string, MaterialSharedPtr_t>;
using GeomVertexAttribSharedPtrMap_t = std::map<gapi::VertexSemantic, GeomVertexAttribBaseSharedPtr_t>;

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TYPEDEFS_HPP
