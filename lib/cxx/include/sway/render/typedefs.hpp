#ifndef SWAY_RENDER_TYPEDEFS_HPP
#define SWAY_RENDER_TYPEDEFS_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

#define DECLARE_CLASS_VECTOR(CLASS, TYPE) \
public:                                   \
  using TYPE##Vec_t = std::vector<CLASS::TYPE##_t>;

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

using RenderSubqueueSharedPtrVec_t = std::vector<RenderSubqueueSharedPtr_t>;
using RenderQueueSharedPtrVec_t = std::vector<RenderQueueSharedPtr_t>;
using MaterialSharedPtrMap_t = std::map<std::string, MaterialSharedPtr_t>;
using GeomVertexAttribSharedPtrMap_t = std::map<gapi::VertexSemantic, GeomVertexAttribBaseSharedPtr_t>;

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TYPEDEFS_HPP
