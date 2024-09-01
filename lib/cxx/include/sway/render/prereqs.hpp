#ifndef SWAY_RENDER_PREREQS_HPP
#define SWAY_RENDER_PREREQS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>

#include <algorithm>  // std::sort
#include <functional>  // std::bind
#include <iostream>  // std::cout
#include <map>
#include <memory>  // std::unique_ptr, std::shared_ptr
#include <string>
#include <unordered_map>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

#define DECLARE_CLSPTR_TYPES(CLASS)                  \
  class CLASS;                                       \
  using CLASS##Ptr_t = CLASS *;                      \
  using CLASS##UniquePtr_t = std::unique_ptr<CLASS>; \
  using CLASS##SharedPtr_t = std::shared_ptr<CLASS>;

#define DECLARE_CLASSPTR_ALIAS(CLASS)     \
public:                                   \
  using Ptr_t = CLASS##Ptr_t;             \
  using UniquePtr_t = CLASS##UniquePtr_t; \
  using SharedPtr_t = CLASS##SharedPtr_t;

DECLARE_CLSPTR_TYPES(VertexChannel)
DECLARE_CLSPTR_TYPES(Geometry)
DECLARE_CLSPTR_TYPES(Effect)
DECLARE_CLSPTR_TYPES(Material)
DECLARE_CLSPTR_TYPES(MaterialManager)
DECLARE_CLSPTR_TYPES(RenderSubqueue)
DECLARE_CLSPTR_TYPES(RenderQueue)
DECLARE_CLSPTR_TYPES(RenderSubsystem)
DECLARE_CLSPTR_TYPES(RenderPass)
DECLARE_CLSPTR_TYPES(RenderTarget)
DECLARE_CLSPTR_TYPES(RenderState)
DECLARE_CLSPTR_TYPES(PostProcessing)
DECLARE_CLSPTR_TYPES(Sprite)

#undef DECLARE_CLSPTR_TYPES

using RenderSubqueueSharedPtrVec_t = std::vector<RenderSubqueueSharedPtr_t>;
using RenderQueueSharedPtrVec_t = std::vector<RenderQueueSharedPtr_t>;
using MaterialSharedPtrMap_t = std::map<std::string, MaterialSharedPtr_t>;

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PREREQS_HPP
