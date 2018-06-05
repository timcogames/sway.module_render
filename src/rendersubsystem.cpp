#include <sway/graphics/rendersubsystem.h>
#include <iostream>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderSubsystem::RenderSubsystem() {
	_caps = new gapi::Capabilities();
	
	auto version = _caps->getVersion();
	std::cout << static_cast<unsigned>(version.getMajor()) << "." << static_cast<unsigned>(version.getMinor()) << std::endl;
}

RenderSubsystem::~RenderSubsystem() {
	SAFE_DELETE(_caps);
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
