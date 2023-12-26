#ifndef SWAY_WEBAPP_HPP
#define SWAY_WEBAPP_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/pltf.hpp>
#include <sway/pltf/timer.hpp>
#include <sway/pltf/web/emscontext.hpp>
#include <sway/pltf/web/emslooper.hpp>
#include <sway/pltf/web/emswindow.hpp>
#include <sway/render/geometry.hpp>
#include <sway/render/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/procedurals/prims/plane.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>
#include <sway/rms.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/threading.h>
#include <memory>

NAMESPACE_BEGIN(sway)

void createWorker();

NAMESPACE_END(sway)

#endif  // SWAY_WEBAPP_HPP
