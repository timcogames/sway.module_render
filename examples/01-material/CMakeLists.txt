#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

#---------------------------------------------------------------------------------
# Project directories
#---------------------------------------------------------------------------------

set(MODULE_RENDER_EX_01_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_RENDER_EX_01_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_RENDER_EX_01_CMAKE_DIR "${MODULE_RENDER_EX_01_ROOT_DIR}/../../submodules/sway.module_core/cmake_modules")
set(MODULE_RENDER_EX_01_LIB_DIR "${MODULE_RENDER_EX_01_ROOT_DIR}/../../lib")
set(MODULE_RENDER_EX_01_BIN_DIR "${CMAKE_SOURCE_DIR}/../../bin")

#---------------------------------------------------------------------------------
# Include CMake modules
#---------------------------------------------------------------------------------

include("${MODULE_RENDER_EX_01_CMAKE_DIR}/options.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/add_submodule.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/enable_coverage.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/modules/logger.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/modules/compiler/emscripten/create_bitcode.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/modules/compiler/emscripten/create_library.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/modules/compiler/emscripten/gen_target_name.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/modules/compiler/emscripten/set_optimization.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/modules/compiler/emscripten/set_environment.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/modules/compiler/emscripten/set_compilation.cmake")
include("${MODULE_RENDER_EX_01_CMAKE_DIR}/modules/compiler/emscripten/set_modularize.cmake")

#---------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------

project_metadata("render_ex_01" 0.1.0)
project(${MODULE_RENDER_EX_01_PROJ_NAME} VERSION ${MODULE_RENDER_EX_01_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${MODULE_RENDER_EX_01_ROOT_DIR}/../../submodules/sway.module_platform-glx11/lib/cxx/include")

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_RENDER_SOURCE_EXAMPLES "${PROJECT_SOURCE_DIR}/*.cpp")

# find_package(OpenGL REQUIRED)
# find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")

add_executable(${MODULE_RENDER_EX_01_TARGET} ${MODULE_RENDER_SOURCE_EXAMPLES})
target_link_libraries(${MODULE_RENDER_EX_01_TARGET} GLU module_render module_rms module_pltf module_core)
enable_cxx17(${MODULE_RENDER_EX_01_TARGET})
