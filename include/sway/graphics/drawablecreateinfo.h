#ifndef SWAY_GRAPHICS_DRAWABLECREATEINFO_H
#define SWAY_GRAPHICS_DRAWABLECREATEINFO_H

#include <sway/graphics/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

struct DrawableCreateInfo {
	gapi::BufferCreateInfo vboInfo;
	gapi::BufferCreateInfo iboInfo;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_DRAWABLECREATEINFO_H
