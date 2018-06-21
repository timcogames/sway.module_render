#include <sway/graphics/rendersubsystem.h>
#include <iostream>

#include <boost/format.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderSubsystem::RenderSubsystem() {
	_caps = new gapi::Capabilities();
	
	auto version = _caps->getGLVersion();
	std::cout << boost::str(boost::format("%1%.%2%") % version.getMajor() % version.getMinor()) << std::endl;
}

RenderSubsystem::~RenderSubsystem() {
	SAFE_DELETE(_caps);
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
