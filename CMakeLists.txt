#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

#---------------------------------------------------------------------------------
# Project directories
#---------------------------------------------------------------------------------

set(MODULE_RENDER_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_RENDER_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_RENDER_CMAKE_DIR "${MODULE_RENDER_ROOT_DIR}/submodules/sway.module_core/cmake_modules")
set(MODULE_RENDER_LIB_DIR "${MODULE_RENDER_ROOT_DIR}/lib")
set(MODULE_RENDER_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

#---------------------------------------------------------------------------------
# Include CMake modules
#---------------------------------------------------------------------------------

include("${MODULE_RENDER_CMAKE_DIR}/options.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/add_submodule.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/logger.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/emscripten/create_bitcode.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/emscripten/create_library.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/emscripten/gen_target_name.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/emscripten/set_optimization.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/emscripten/set_environment.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/emscripten/set_compilation.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/emscripten/set_modularize.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/enable_coverage.cmake")

#---------------------------------------------------------------------------------
# Опции сборки
#---------------------------------------------------------------------------------

option(MODULE_RENDER_BUILD_SHARED "Build shared library" OFF)
option(MODULE_RENDER_ENABLE_COVERAGE "Enable coverage builds" OFF)
option(MODULE_RENDER_ENABLE_EXAMPLES "none" OFF)
option(MODULE_RENDER_ENABLE_TESTS "Enable test builds" OFF)

#---------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#---------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------

project_metadata("render" 0.17.66)
project(${MODULE_RENDER_PROJ_NAME} VERSION ${MODULE_RENDER_VERSION} LANGUAGES CXX)

#---------------------------------------------------------------------------------
# Submodules
#---------------------------------------------------------------------------------

add_submodule("module_core" submodules/sway.module_core)
add_submodule("module_rms" submodules/sway.module_rms)

#---------------------------------------------------------------------------------
# Coverage
#---------------------------------------------------------------------------------

if(MODULE_RENDER_ENABLE_COVERAGE)
  enable_coverage()
endif()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default -fPIE")

if(GLOB_EMSCRIPTEN_PLATFORM)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --no-entry")

  set(CMAKE_CXX_COMPILER "${CUSTOM_EMSCRIPTEN_ROOT_DIR}/em++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -std=c++17")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-no-whole-archive") # < ---
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-unicode-whitespace \
    -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-command-line-argument")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM")

  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s WASM=1 -s MODULARIZE=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s STRICT=1")

  if(GLOB_EMSCRIPTEN_USE_BINDINGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM_USE_BINDING")
  endif()

  if(GLOBAL_EMSCRIPTEN_PLATFORM_USE_ES6)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORT_ES6=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ENVIRONMENT=node")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_ES6_IMPORT_META=1")
  endif()
endif()

#---------------------------------------------------------------------------------
# Executable output path
#---------------------------------------------------------------------------------

set_output_dir(${MODULE_RENDER_BIN_DIR})

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")

# Добавляем пути для поиска хедеров
include_directories("${SYSTEM_X11_INCLUDE_DIRS}")
include_directories("${MODULE_RENDER_LIST_DIR}/lib/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_math/lib/cxx/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_gapi/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_loader/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_rms/lib/include")

# find_package(OpenGL REQUIRED)
# find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")
link_directories("${SYSTEM_X11_LIBRARY_DIRS}")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_RENDER_HEADERS "${MODULE_RENDER_LIST_DIR}/lib/include/sway/*.*")
file(GLOB_RECURSE MODULE_RENDER_SOURCES "${MODULE_RENDER_LIST_DIR}/lib/src/*.*")

if(MODULE_RENDER_BUILD_SHARED)
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default -fPIE")

  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${MODULE_RENDER_TARGET} SHARED ${MODULE_RENDER_SOURCES})
  set_target_properties(${MODULE_RENDER_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_RENDER_PROJ_NAME})
  set_target_properties(${MODULE_RENDER_TARGET} PROPERTIES PREFIX "")
  set_target_properties(${MODULE_RENDER_TARGET} PROPERTIES SUFFIX ".${MODULE_RENDER_VERSION}.so")
else()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${MODULE_RENDER_TARGET} STATIC ${MODULE_RENDER_SOURCES})
  set_target_properties(${MODULE_RENDER_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_RENDER_PROJ_NAME})
  set_target_properties(${MODULE_RENDER_TARGET} PROPERTIES PREFIX "")
  if(GLOB_EMSCRIPTEN_PLATFORM)
    set_target_properties(${MODULE_RENDER_TARGET} PROPERTIES SUFFIX ".${MODULE_RENDER_VERSION}.bc")
    # set(CMAKE_STATIC_LIBRARY_SUFFIX ".bc")
    else()
    set_target_properties(${MODULE_RENDER_TARGET} PROPERTIES SUFFIX ".${MODULE_RENDER_VERSION}.a")
  endif()
endif()

# target_link_libraries(${MODULE_RENDER_TARGET} GL X11 ${BOOST_LIBRARIES})
# target_link_libraries(${MODULE_RENDER_TARGET} GL X11 libmodule_core)
target_link_libraries(${MODULE_RENDER_TARGET})

enable_cxx17(${MODULE_RENDER_TARGET})

#---------------------------------------------------------------------------------
# Построение примеров
#---------------------------------------------------------------------------------

if(MODULE_RENDER_ENABLE_EXAMPLES)
  message(STATUS "Examples have been enabled")

  # Добавляем пути для поиска хедеров
  include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_platform-glx11/lib/cxx/include")

  if(NOT TARGET module_pltf)
    add_subdirectory("submodules/sway.module_platform-glx11")
  endif()

  if(GLOB_EMSCRIPTEN_PLATFORM)
    add_subdirectory("examples/01-material-wasm")
  else()
    add_subdirectory("examples/01-material")
  endif()
endif()

#---------------------------------------------------------------------------------
# Построение тестов
#---------------------------------------------------------------------------------

if(MODULE_RENDER_ENABLE_TESTS)
  message(STATUS "Tests have been enabled")

  add_subdirectory(tests)
endif()
