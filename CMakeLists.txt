# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_enable_cxx17.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_add_subdirectory.cmake")

# Мета-информация о проекте
set(META_GRAPHICS_PRJNAME "module_graphics")
set(META_GRAPHICS_LIBNAME "lib${META_GRAPHICS_PRJNAME}")
set(META_GRAPHICS_VERSION_MAJOR 0)
set(META_GRAPHICS_VERSION_MINOR 17)
set(META_GRAPHICS_VERSION_PATCH 65)
set(META_GRAPHICS_VERSION ${META_GRAPHICS_VERSION_MAJOR}.${META_GRAPHICS_VERSION_MINOR}.${META_GRAPHICS_VERSION_PATCH})

# Опции сборки
option(MODULE_GRAPHICS_BUILD_SHARED "Build shared library" OFF)
option(MODULE_GRAPHICS_ENABLE_COVERAGE "Enable coverage builds" OFF)
option(MODULE_GRAPHICS_ENABLE_TESTS "Enable test builds" OFF)

project(${META_GRAPHICS_PRJNAME} CXX)

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MODULE_GRAPHICS_ENABLE_COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Определяем каталог вывода по умолчанию
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
else ()
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
endif ()

set(MODULE_GRAPHICS_DIR ${CMAKE_CURRENT_LIST_DIR})

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")
set(MODULE_GAPI_GL_DIR ${CMAKE_CURRENT_LIST_DIR})

# Добавляем пути для поиска хедеров
include_directories("${SYSTEM_X11_INCLUDE_DIRS}")
include_directories("${MODULE_GRAPHICS_DIR}/lib/include")
include_directories("${MODULE_GRAPHICS_DIR}/submodules/sway.module_core/lib/include")
include_directories("${MODULE_GRAPHICS_DIR}/submodules/sway.module_math/lib/include")
include_directories("${MODULE_GRAPHICS_DIR}/submodules/sway.module_gapi/include")
include_directories("${MODULE_GRAPHICS_DIR}/submodules/sway.module_gapi-dummy/include")
include_directories("${MODULE_GRAPHICS_DIR}/submodules/sway.module_gapi-gl/lib/include")

find_package(OpenGL REQUIRED)
find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")

link_directories("${SYSTEM_X11_LIBRARY_DIRS}")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_GRAPHICS_HEADERS "${MODULE_GRAPHICS_DIR}/lib/include/*.*")
file(GLOB_RECURSE MODULE_GRAPHICS_SOURCES "${MODULE_GRAPHICS_DIR}/lib/src/*.*")

if (MODULE_GRAPHICS_BUILD_SHARED)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default -fPIE")

  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${META_GRAPHICS_LIBNAME} SHARED ${MODULE_GRAPHICS_SOURCES})
  set_target_properties(${META_GRAPHICS_LIBNAME} PROPERTIES OUTPUT_NAME ${META_GRAPHICS_PRJNAME})
  set_target_properties(${META_GRAPHICS_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_GRAPHICS_LIBNAME} PROPERTIES SUFFIX ".so.${META_GRAPHICS_VERSION}")
else ()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${META_GRAPHICS_LIBNAME} STATIC ${MODULE_GRAPHICS_SOURCES})
  set_target_properties(${META_GRAPHICS_LIBNAME} PROPERTIES OUTPUT_NAME ${META_GRAPHICS_PRJNAME})
  set_target_properties(${META_GRAPHICS_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_GRAPHICS_LIBNAME} PROPERTIES SUFFIX ".a.${META_GRAPHICS_VERSION}")
endif ()

# target_link_libraries(${META_GRAPHICS_LIBNAME} GL X11 ${BOOST_LIBRARIES})
target_link_libraries(${META_GRAPHICS_LIBNAME} GL X11)

custom_enable_cxx17(${META_GRAPHICS_LIBNAME})

if (MODULE_GRAPHICS_ENABLE_EXAMPLES OR ENABLE_TESTS)
  if (NOT TARGET libmodule_core)
    add_subdirectory("submodules/sway.module_core")
  endif ()
endif ()

# Добавляем построение примеров
if (MODULE_GRAPHICS_ENABLE_EXAMPLES)
  message(STATUS "Examples have been enabled")

  # Добавляем пути для поиска хедеров
  include_directories("${CMAKE_SOURCE_DIR}/submodules/sway.module_platform-glx11/include")

  if (NOT TARGET module_platform_glx11)
    add_subdirectory("submodules/sway.module_platform-glx11")
  endif ()

  if (NOT TARGET module_gapi_gl)
    add_subdirectory("submodules/sway.module_gapi-gl")
  endif ()

  add_subdirectory("examples/triangle2")
endif ()

# Добавляем построение тестов
if (MODULE_GRAPHICS_ENABLE_TESTS)
  message(STATUS "Tests have been enabled")

  if (NOT TARGET libmodule_gapi_dummy)
    add_subdirectory("submodules/sway.module_gapi-dummy")
  endif ()

  add_subdirectory(tests)
endif ()
