#ifndef SWAY_GRAPHICS_MATERIALINITIALINFO_H
#define SWAY_GRAPHICS_MATERIALINITIALINFO_H

#include <sway/graphics/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

struct MaterialInitialInfo {
	gapi::ShaderObjectCreateInfo vsoInfo;
	gapi::ShaderObjectCreateInfo fsoInfo;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_MATERIALINITIALINFO_H
