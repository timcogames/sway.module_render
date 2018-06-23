#ifndef SWAY_GRAPHICS_PREREQS_H
#define SWAY_GRAPHICS_PREREQS_H

#include <sway/core.h>
#include <sway/math.h>
#include <sway/gapi.h>

#include <iostream> // std::cout
#include <vector> // std::vector
#include <functional> // std::bind
#include <algorithm> // std::sort

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

#define RENDER_SUBQUEUE_GROUP_COUNT 2

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Material;
class Drawable;
class RenderSubqueue;
class RenderQueue;
class RenderSubsystem;

using DrawableRef_t = boost::shared_ptr<class Drawable>;
using DrawableRefVector_t = std::vector<DrawableRef_t>;

using RenderSubqueueRef_t = boost::shared_ptr<class RenderSubqueue>;
using RenderSubqueueRefVector_t = std::vector<RenderSubqueueRef_t>;

using RenderQueueRef_t = boost::shared_ptr<class RenderQueue>;
using RenderQueueRefVector_t = std::vector<RenderQueueRef_t>;

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_PREREQS_H
