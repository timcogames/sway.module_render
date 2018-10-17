#ifndef SWAY_GRAPHICS_PREREQS_H
#define SWAY_GRAPHICS_PREREQS_H

#include <sway/core.h>
#include <sway/math.h>
#include <sway/gapi/gl.h>

#include <iostream> // std::cout
#include <vector> // std::vector
#include <functional> // std::bind
#include <algorithm> // std::sort

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp> // boost::property_tree::ptree

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

typedef core::binding::TFunction<CapabilityRef_t (void)> CreateCapabilityFunc_t;
typedef core::binding::TFunction<ShaderRef_t (const ShaderCreateInfo &)> CreateShaderFunc_t;
typedef core::binding::TFunction<ShaderProgramRef_t (void)> CreateShaderProgramFunc_t;
typedef core::binding::TFunction<BufferRef_t (const BufferCreateInfo &)> CreateBufferFunc_t;
typedef core::binding::TFunction<VertexLayoutRef_t (ShaderProgramRef_t)> CreateVertexLayoutFunc_t;
typedef core::binding::TFunction<DrawCallRef_t (void)> CreateDrawCallFunc_t;
typedef core::binding::TFunction<ViewportRef_t (void)> CreateViewportFunc_t;

NAMESPACE_END(gapi)
NAMESPACE_BEGIN(graphics)

class StaticMesh;
class Material;
class MaterialManager;
class Drawable;
class RenderSubqueue;
class RenderQueue;
class RenderSubsystem;

typedef boost::shared_ptr<class StaticMesh> StaticMeshRef_t;
typedef boost::shared_ptr<class Material> MaterialRef_t;
typedef boost::shared_ptr<class MaterialManager> MaterialManagerRef_t;

typedef boost::shared_ptr<class Drawable> DrawableRef_t;
typedef std::vector<DrawableRef_t> DrawableRefVec_t;

typedef boost::shared_ptr<class RenderSubqueue> RenderSubqueueRef_t;
typedef std::vector<RenderSubqueueRef_t> RenderSubqueueRefVec_t;

typedef boost::shared_ptr<class RenderQueue> RenderQueueRef_t;
typedef std::vector<RenderQueueRef_t> RenderQueueRefVector_t;

typedef boost::shared_ptr<class RenderSubsystem> RenderSubsystemRef_t;

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_PREREQS_H
