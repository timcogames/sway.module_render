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
include("${MODULE_RENDER_CMAKE_DIR}/modules/create_object.cmake")
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

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fPIE")

#---------------------------------------------------------------------------------
# Executable output path
#---------------------------------------------------------------------------------

set_output_dir(${MODULE_RENDER_BIN_DIR})

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")

# Добавляем пути для поиска хедеров
include_directories("${SYSTEM_X11_INCLUDE_DIRS}")
include_directories("${MODULE_RENDER_LIST_DIR}/lib/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_gapi/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_loader/api/cxx/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_math/lib/cxx/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_rms/lib/cxx/include")

# find_package(OpenGL REQUIRED)
# find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")
link_directories("${SYSTEM_X11_LIBRARY_DIRS}")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_RENDER_HEADERS "${MODULE_RENDER_LIST_DIR}/lib/include/sway/*.*")
file(GLOB_RECURSE MODULE_RENDER_SOURCES "${MODULE_RENDER_LIST_DIR}/lib/src/*.*")

# # target_link_libraries(${MODULE_RENDER_TARGET} GL X11 ${BOOST_LIBRARIES})
# # target_link_libraries(${MODULE_RENDER_TARGET} GL X11 libmodule_core)
# target_link_libraries(${MODULE_RENDER_TARGET})

#---------------------------------------------------------------------------------
# Create interfaces
#---------------------------------------------------------------------------------

set(MODULE_CORE_TARGET_IFACE "module_core_iface")

set(TARGET_OBJECT_LIST)
list(APPEND TARGET_OBJECT_LIST $<TARGET_OBJECTS:module_core>)

create_interface(${MODULE_CORE_TARGET_IFACE} ${TARGET_OBJECT_LIST})

#---------------------------------------------------------------------------------
# [EMSCRIPTEN] Bitcode
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  create_object(${MODULE_RENDER_TARGET} "${MODULE_RENDER_ROOT_DIR}/lib/src/*.*" TRUE)
else()
  create_library(${MODULE_RENDER_TARGET} "${MODULE_RENDER_ROOT_DIR}/lib/src/*.*")
endif()

enable_cxx17(${MODULE_RENDER_TARGET})

if(GLOB_EMSCRIPTEN_PLATFORM AND MODULE_RENDER_BUILD_TYPE STREQUAL "module")
  create_emscripten_library(${MODULE_RENDER_TARGET} ${MODULE_RENDER_ENVIRONMENT} ${MODULE_RENDER_COMPILATION} OUTPUT_TARGET_NAME_LIST)

  foreach(target IN LISTS OUTPUT_TARGET_NAME_LIST)
    target_link_options(${target} PUBLIC 
      "SHELL:-s STRICT=1"
      "SHELL:-s MODULARIZE=1"
      "SHELL:-s FULL_ES3=1"
      "SHELL:-s SUPPORT_LONGJMP=0"
      "SHELL:-s EXPORT_NAME=\"create_render_module\""
      "SHELL:-s EXPORTED_FUNCTIONS=@${MODULE_RENDER_LIB_DIR}/exports.json"
      "SHELL:-s EXPORTED_RUNTIME_METHODS=@${MODULE_RENDER_LIB_DIR}/runtime-exports.json")

    # if(MODULE_RENDER_SHARED_LIB)
    #   target_link_options(${target} PUBLIC 
    #     "SHELL:-shared"
    #     "SHELL:-dynamiclib"
    #     "SHELL:-s SIDE_MODULE=1")
    # endif()

    if(MODULE_RENDER_MT)
      target_link_options(${target} PUBLIC 
        "SHELL:-Wl,--shared-memory,--no-check-features"
        "SHELL:-s USE_PTHREADS=1"
        "SHELL:-s PTHREAD_POOL_SIZE=8"
        "SHELL:-s IMPORTED_MEMORY=1")

      # target_link_options(${target} PUBLIC 
      #   "SHELL:-s PROXY_TO_PTHREAD=1")
    endif()

    # set_target_properties(${target} PROPERTIES COMPILE_FLAGS "-s MEMORY64=1")

    printf_link_options(${target})
  endforeach()
endif()

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
