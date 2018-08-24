#ifndef SWAY_GRAPHICS_PLUGINDESCRIPTOR_H
#define SWAY_GRAPHICS_PLUGINDESCRIPTOR_H

#include <sway/graphics/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

struct PluginDescriptor {
	std::string fullname;
	core::Version version;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_PLUGINDESCRIPTOR_H
