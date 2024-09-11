#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

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
include("${MODULE_RENDER_CMAKE_DIR}/modules/create_object_library.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/create_interface.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/logger.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_RENDER_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
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
option(MODULE_RENDER_BUILD_TYPE "" "module") # module, bitcode
option(MODULE_RENDER_ENVIRONMENT "Environment variable" OFF)
option(MODULE_RENDER_COMPILATION "Compilation variable" OFF)
option(MODULE_RENDER_MT "Enable multithreading" OFF)
option(MODULE_RENDER_ENABLE_COVERAGE "Enable coverage builds" OFF)
option(MODULE_RENDER_ENABLE_TESTS "Enable test builds" OFF)
option(MODULE_RENDER_USE_GMOCK "Use google mock" OFF)

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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fPIE")

set(MODULE_RENDER_DEPENDENCY_LIST "module_render_dependences")

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

#---------------------------------------------------------------------------------
# Executable output path
#---------------------------------------------------------------------------------

set_output_dir(${MODULE_RENDER_BIN_DIR})

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")

# Добавляем пути для поиска хедеров
include_directories("${SYSTEM_X11_INCLUDE_DIRS}")
include_directories("${GLOB_THIRD_PARTY_DIR}/json/include")

include_directories("${MODULE_RENDER_LIST_DIR}/lib/cxx/include")
if(MODULE_RENDER_ENABLE_TESTS)
  include_directories("${GLOB_GTEST_ROOT_DIR}/include")
  include_directories("${GLOB_GMOCK_ROOT_DIR}/include")
  include_directories("${MODULE_RENDER_LIST_DIR}/lib/cxx/tests")
endif()

include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_gapi/api/cxx/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_loader/api/cxx/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_math/lib/cxx/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_rms/lib/cxx/include")

# find_package(OpenGL REQUIRED)
# find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")
link_directories("${SYSTEM_X11_LIBRARY_DIRS}")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_RENDER_HEADERS "${MODULE_RENDER_LIST_DIR}/lib/cxx/include/sway/*.*")
file(GLOB_RECURSE MODULE_RENDER_SOURCES "${MODULE_RENDER_LIST_DIR}/lib/cxx/src/*.*")

# # target_link_libraries(${MODULE_RENDER_TARGET} GL X11 ${BOOST_LIBRARIES})
# # target_link_libraries(${MODULE_RENDER_TARGET} GL X11 libmodule_core)
# target_link_libraries(${MODULE_RENDER_TARGET})

#---------------------------------------------------------------------------------
# Library
#---------------------------------------------------------------------------------

add_subdirectory(lib/cxx)

#---------------------------------------------------------------------------------
# Tests
#---------------------------------------------------------------------------------

if(MODULE_RENDER_ENABLE_TESTS)
  if(${MODULE_RENDER_LIB_TYPE} MATCHES "static")
    message(STATUS "[${MODULE_RENDER_PROJ_NAME}]: Tests have been enabled")
    add_subdirectory(lib/cxx/tests/google)
  else()
    message(STATUS "[${MODULE_RENDER_PROJ_NAME}]: Tests are only allowed with a static lib")
  endif()
endif()
