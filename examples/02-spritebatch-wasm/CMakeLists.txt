#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#---------------------------------------------------------------------------------
# Project directories
#---------------------------------------------------------------------------------

set(MODULE_RENDER_EX_02_SPRITEBATCH_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_RENDER_EX_02_SPRITEBATCH_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_RENDER_EX_02_SPRITEBATCH_CMAKE_DIR "${MODULE_RENDER_EX_02_SPRITEBATCH_ROOT_DIR}/../../submodules/sway.module_core/cmake_modules")
set(MODULE_RENDER_EX_02_SPRITEBATCH_LIB_DIR "${MODULE_RENDER_EX_02_SPRITEBATCH_ROOT_DIR}/../../lib")
set(MODULE_RENDER_EX_02_SPRITEBATCH_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

#---------------------------------------------------------------------------------
# Include CMake modules
#---------------------------------------------------------------------------------

include("${MODULE_RENDER_EX_02_SPRITEBATCH_CMAKE_DIR}/options.cmake")
include("${MODULE_RENDER_EX_02_SPRITEBATCH_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_RENDER_EX_02_SPRITEBATCH_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_RENDER_EX_02_SPRITEBATCH_CMAKE_DIR}/add_submodule.cmake")
include("${MODULE_RENDER_EX_02_SPRITEBATCH_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_RENDER_EX_02_SPRITEBATCH_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")

#---------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#---------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------

project_metadata("render_ex_02_spritebatch" 0.1.0)
project(${MODULE_RENDER_EX_02_SPRITEBATCH_PROJ_NAME} VERSION ${MODULE_RENDER_EX_02_SPRITEBATCH_VERSION} LANGUAGES CXX)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default -fPIE")

# if (GLOB_EMSCRIPTEN_PLATFORM)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM")
#   set(CMAKE_CXX_COMPILER "${GLOB_EMSCRIPTEN_ROOT_DIR}/em++")
#   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s WASM=1")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-return-type -Wno-int-to-pointer-cast -Wno-unknown-pragmas -Wno-unicode-whitespace \
#     -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-parameter -Wno-unused-variable -Wno-unused-command-line-argument -Wno-gnu-zero-variadic-macro-arguments")

#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MODULARIZE=1")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORT_NAME=Module")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORT_ES6=1")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FULL_ES3=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s LLD_REPORT_UNDEFINED=1")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS=\"[_main]\"")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ASSERTIONS=1")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MAIN_MODULE=1")

#   if(GLOB_EMSCRIPTEN_USE_BINDINGS)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM_USE_BINDING")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
#   endif()
# endif()

# if(GLOB_EMSCRIPTEN_PLATFORM)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM")
#   set(CMAKE_CXX_COMPILER "${GLOB_EMSCRIPTEN_ROOT_DIR}/em++")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--shared-memory,--no-check-features")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-check-features")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -Wall -Wno-return-type -Wno-int-to-pointer-cast -Wno-unknown-pragmas -Wno-unicode-whitespace \
#   -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-parameter -Wno-unused-variable -Wno-unused-command-line-argument -Wno-gnu-zero-variadic-macro-arguments")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_DISABLE_EXCEPTION_CATCHING=1")
#   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s WASM=1")
#   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s MODULARIZE=1 -s EXPORT_NAME=Module")
#   # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s MODULARIZE=1")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MAIN_MODULE=1")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ASSERTIONS=1")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FORCE_FILESYSTEM=1")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ENVIRONMENT=node,worker")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=8")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s IMPORTED_MEMORY=1")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ERROR_ON_UNDEFINED_SYMBOLS=0")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s LINKABLE=1")

#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FULL_ES3=1")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_LIBPNG=1")
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ENVIRONMENT=web,worker")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FETCH_DEBUG=1 -s GL_DEBUG=1 -s FS_DEBUG=1")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS=\"[_main]\"")

#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ${WASM_PRELOAD_DIR}/bin/@")
#   # set(POST_JS ${CMAKE_CURRENT_SOURCE_DIR}/wasm/prolog.js)
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --pre-js ${POST_JS}")
#   # set(PRE_JS ${CMAKE_CURRENT_SOURCE_DIR}/wasm/pre.js)
#   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --post-js ${PRE_JS}")

#   if(GLOB_EMSCRIPTEN_USE_BINDINGS)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM_USE_BINDING")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
#   endif()
# endif()

if(GLOB_EMSCRIPTEN_PLATFORM)
  set(CMAKE_CXX_COMPILER "${GLOB_EMSCRIPTEN_ROOT_DIR}/emcc")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
    -s MODULARIZE=1 \
    -s EXPORT_NAME=Module \
    -s MAIN_MODULE=1 \
    -s EXPORT_ES6=1 \
    -s FULL_ES3=1 \
    -s LLD_REPORT_UNDEFINED=1 \
    -s EXPORTED_FUNCTIONS=[\"_main\"]")

  # thread
  # unsupported option '-fsanitize=thread' for target 'wasm32-unknown-emscripten'
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")

  # address
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
  # undefined
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MIN_SAFARI_VERSION=-1")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ASSERTIONS=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s STACK_OVERFLOW_CHECK=2")

  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s PTHREAD_POOL_SIZE_STRICT=2")

  # emscripten_get_preloaded_image_data
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --use-preload-plugins")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s STB_IMAGE=1")

  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --proxy-to-worker")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s PROXY_TO_PTHREAD=1")
  
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s PTHREAD_POOL_SIZE_STRICT=0")

  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s TOTAL_MEMORY=34574312")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s INITIAL_MEMORY=23203944")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1")
  
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MEMORY64=1")
  # set_target_properties(${target} PROPERTIES COMPILE_FLAGS "-s MEMORY64=1")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FORCE_FILESYSTEM=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    --preload-file ../../@/wwwroot/dist/module_gapi_gl_wasm_async.wasm \
    --preload-file ../../@/wwwroot/dist/module_loader_png_wasm_async.wasm")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    --embed-file ../../@/wwwroot/dist/assets/web")

  # USE_FREETYPE
  # USE_ZLIB
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_LIBPNG=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_WEBGL2=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s OFFSCREENCANVAS_SUPPORT=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s OFFSCREENCANVASES_TO_PTHREAD=\"#canvas\"")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s OFFSCREEN_FRAMEBUFFER=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

  # preload-file
  # set_target_properties(${target_name} PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/data.json)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--shared-memory,--no-check-features")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_PTHREADS=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s PTHREAD_POOL_SIZE=8")

  # при вкл.: pthread_create: could not find canvas with ID "#canvas" to transfer to thread!
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s PROXY_TO_PTHREAD=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ASYNCIFY=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_BLOCKING_ON_MAIN_THREAD=1")

  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FETCH_DEBUG=1 -s GL_DEBUG=1 -s FS_DEBUG=1")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
  #   -s FORCE_FILESYSTEM=1")

  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
  #   --shared-memory \
  #   -s SHARED_MEMORY=1 \
  #   -s USE_PTHREADS=1 \
  #   -s PROXY_TO_PTHREAD=1")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
  #   -s SHARED_MEMORY=1 -pthread")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-return-type -Wno-int-to-pointer-cast -Wno-unknown-pragmas -Wno-unicode-whitespace \
    -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-parameter -Wno-unused-variable -Wno-unused-command-line-argument -Wno-gnu-zero-variadic-macro-arguments")
endif()

#---------------------------------------------------------------------------------
# Executable output path
#---------------------------------------------------------------------------------

set_output_dir(${MODULE_RENDER_EX_02_SPRITEBATCH_BIN_DIR})

# find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")
# find_package(OpenGL REQUIRED)
# if(OPENGL_FOUND)
#   include_directories(${OPENGL_INCLUDE_DIRS})
#   link_directories(${OPENGL_LIBRARY_DIRS})
#   add_definitions(${OPENGL_DEFINITIONS})
# endif()

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_RENDER_EX_02_SPRITEBATCH_HEADERS "${MODULE_RENDER_EX_02_SPRITEBATCH_LIST_DIR}/*.hpp")
file(GLOB_RECURSE MODULE_RENDER_EX_02_SPRITEBATCH_SOURCES "${MODULE_RENDER_EX_02_SPRITEBATCH_LIST_DIR}/*.cpp")

add_executable(${MODULE_RENDER_EX_02_SPRITEBATCH_LIB_TARGET} ${MODULE_RENDER_EX_02_SPRITEBATCH_SOURCES})
set_target_properties(${MODULE_RENDER_EX_02_SPRITEBATCH_LIB_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_RENDER_EX_02_SPRITEBATCH_PROJ_NAME})

enable_cxx17(${MODULE_RENDER_EX_02_SPRITEBATCH_LIB_TARGET})
# target_link_libraries(${MODULE_RENDER_EX_02_SPRITEBATCH_LIB_TARGET} ${MODULE_RENDER_DEPENDENCY_LIST} module_pltf -I/Users/apriori85/Documents/Projects/sway.module_loader-png/bin/module_loader_png_wasm_async.wasm/png)
target_link_libraries(${MODULE_RENDER_EX_02_SPRITEBATCH_LIB_TARGET} module_rms_obj module_render_obj ${MODULE_RENDER_DEPENDENCY_LIST} module_pltf -I/Users/apriori85/Documents/Projects/sway.module_loader-png/bin/module_loader_png_wasm_async.wasm/png)
