# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/../../submodules/sway.module_core/cmakehelpers/custom_enable_cxx17.cmake")

# Мета-информация о проекте
set(META_MATERIAL_PRJNAME "module_material")
set(META_MATERIAL_LIBNAME "lib${META_MATERIAL_PRJNAME}")
set(META_MATERIAL_VERSION_MAJOR 0)
set(META_MATERIAL_VERSION_MINOR 1)
set(META_MATERIAL_VERSION_PATCH 0)
set(META_MATERIAL_VERSION ${META_MATERIAL_VERSION_MAJOR}.${META_MATERIAL_VERSION_MINOR}.${META_MATERIAL_VERSION_PATCH})

# Опции сборки
option(CUSTOM_EMSCRIPTEN_ROOT_DIR "Emscripten root directory" OFF)
option(CUSTOM_BOOST_ROOT_DIR "Boost root directory" OFF)
option(CUSTOM_GTEST_ROOT_DIR "GTest root directory" OFF)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${CUSTOM_EMSCRIPTEN_ROOT_DIR}/cmake/Modules/Platform/Emscripten.cmake")
  include(${CMAKE_TOOLCHAIN_FILE})
endif()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif()

project(${META_MATERIAL_PRJNAME} VERSION ${META_MATERIAL_VERSION} LANGUAGES CXX)

# if (GLOB_EMSCRIPTEN_PLATFORM)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM")
#   set(CMAKE_CXX_COMPILER "${CUSTOM_EMSCRIPTEN_ROOT_DIR}/em++")
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

if(GLOB_EMSCRIPTEN_PLATFORM)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM")
  set(CMAKE_CXX_COMPILER "${CUSTOM_EMSCRIPTEN_ROOT_DIR}/em++")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--shared-memory,--no-check-features")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-check-features")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -Wall -Wno-return-type -Wno-int-to-pointer-cast -Wno-unknown-pragmas -Wno-unicode-whitespace \
  -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-parameter -Wno-unused-variable -Wno-unused-command-line-argument -Wno-gnu-zero-variadic-macro-arguments")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_DISABLE_EXCEPTION_CATCHING=1")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s WASM=1")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s MODULARIZE=1 -s EXPORT_NAME=yourWasmModule")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s MODULARIZE=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MAIN_MODULE=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ASSERTIONS=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FORCE_FILESYSTEM=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ENVIRONMENT=node,worker")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=8")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s IMPORTED_MEMORY=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ERROR_ON_UNDEFINED_SYMBOLS=0")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s LINKABLE=1")

  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FULL_ES3=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_LIBPNG=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ENVIRONMENT=web,worker")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FETCH_DEBUG=1 -s GL_DEBUG=1 -s FS_DEBUG=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS=\"[_main]\"")

  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ${WASM_PRELOAD_DIR}/bin/@")
  # set(POST_JS ${CMAKE_CURRENT_SOURCE_DIR}/wasm/prolog.js)
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --pre-js ${POST_JS}")
  # set(PRE_JS ${CMAKE_CURRENT_SOURCE_DIR}/wasm/pre.js)
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --post-js ${PRE_JS}")

  if(GLOB_EMSCRIPTEN_USE_BINDINGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM_USE_BINDING")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
  endif()
endif()

# Определяем каталог вывода по умолчанию
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/dbg")
  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/dbg")
else()
  set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
endif()

# find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")
# find_package(OpenGL REQUIRED)
# if(OPENGL_FOUND)
#   include_directories(${OPENGL_INCLUDE_DIRS})
#   link_directories(${OPENGL_LIBRARY_DIRS})
#   add_definitions(${OPENGL_DEFINITIONS})
# endif()

set(MODULE_MATERIAL_DIR ${CMAKE_CURRENT_LIST_DIR})

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_MATERIAL_HEADERS "${MODULE_MATERIAL_DIR}/*.hpp")
file(GLOB_RECURSE MODULE_MATERIAL_SOURCES "${MODULE_MATERIAL_DIR}/*.cpp")

# add_executable(${META_MATERIAL_LIBNAME} ${MODULE_MATERIAL_SOURCES})
# set_target_properties(${META_MATERIAL_LIBNAME} PROPERTIES OUTPUT_NAME "index")
# # set_target_properties(${META_MATERIAL_LIBNAME} PROPERTIES SUFFIX ".html")

add_executable(${META_MATERIAL_LIBNAME} ${MODULE_MATERIAL_SOURCES})
set_target_properties(${META_MATERIAL_LIBNAME} PROPERTIES OUTPUT_NAME ${META_MATERIAL_PRJNAME})
if (GLOB_EMSCRIPTEN_PLATFORM)
  if (GLOB_EMSCRIPTEN_USE_BINDINGS)
    set_target_properties(${META_MATERIAL_LIBNAME} PROPERTIES SUFFIX ".${META_MATERIAL_VERSION}.js")
  else ()
    set_target_properties(${META_MATERIAL_LIBNAME} PROPERTIES SUFFIX ".${META_MATERIAL_VERSION}.wasm")
  endif ()
endif ()

custom_enable_cxx17(${META_MATERIAL_LIBNAME})
# target_link_libraries(${META_MATERIAL_LIBNAME} GL GLESv2 ${GLUT_LIBRARY} ${OPENGL_LIBRARY} libmodule_render libmodule_pltf libmodule_rms libmodule_core)
target_link_libraries(${META_MATERIAL_LIBNAME} libmodule_render libmodule_pltf libmodule_core)
