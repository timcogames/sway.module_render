# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_enable_cxx17.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_add_subdirectory.cmake")

# Мета-информация о проекте
set(META_RENDER_PRJNAME "module_render")
set(META_RENDER_LIBNAME "lib${META_RENDER_PRJNAME}")
set(META_RENDER_VERSION_MAJOR 0)
set(META_RENDER_VERSION_MINOR 17)
set(META_RENDER_VERSION_PATCH 65)
set(META_RENDER_VERSION ${META_RENDER_VERSION_MAJOR}.${META_RENDER_VERSION_MINOR}.${META_RENDER_VERSION_PATCH})

# Опции сборки
option(MODULE_RENDER_BUILD_SHARED "Build shared library" OFF)
option(MODULE_RENDER_ENABLE_COVERAGE "Enable coverage builds" OFF)
option(MODULE_RENDER_ENABLE_TESTS "Enable test builds" OFF)

project(${META_RENDER_PRJNAME} CXX)

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MODULE_RENDER_ENABLE_COVERAGE)
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

set(MODULE_RENDER_DIR ${CMAKE_CURRENT_LIST_DIR})

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")

# Добавляем пути для поиска хедеров
include_directories("${SYSTEM_X11_INCLUDE_DIRS}")
include_directories("${MODULE_RENDER_DIR}/lib/include")
include_directories("${MODULE_RENDER_DIR}/submodules/sway.module_core/lib/include")
include_directories("${MODULE_RENDER_DIR}/submodules/sway.module_math/lib/include")
include_directories("${MODULE_RENDER_DIR}/submodules/sway.module_gapi/include")
include_directories("${MODULE_RENDER_DIR}/submodules/sway.module_loader/include")
include_directories("${MODULE_RENDER_DIR}/submodules/sway.module_rms/lib/include")

find_package(OpenGL REQUIRED)
find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")

link_directories("${SYSTEM_X11_LIBRARY_DIRS}")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_RENDER_HEADERS "${MODULE_RENDER_DIR}/lib/include/*.*")
file(GLOB_RECURSE MODULE_RENDER_SOURCES "${MODULE_RENDER_DIR}/lib/src/*.*")

if (MODULE_RENDER_BUILD_SHARED)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default -fPIE")

  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${META_RENDER_LIBNAME} SHARED ${MODULE_RENDER_SOURCES})
  set_target_properties(${META_RENDER_LIBNAME} PROPERTIES OUTPUT_NAME ${META_RENDER_PRJNAME})
  set_target_properties(${META_RENDER_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_RENDER_LIBNAME} PROPERTIES SUFFIX ".so.${META_RENDER_VERSION}")
else ()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${META_RENDER_LIBNAME} STATIC ${MODULE_RENDER_SOURCES})
  set_target_properties(${META_RENDER_LIBNAME} PROPERTIES OUTPUT_NAME ${META_RENDER_PRJNAME})
  set_target_properties(${META_RENDER_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_RENDER_LIBNAME} PROPERTIES SUFFIX ".a.${META_RENDER_VERSION}")
endif ()

# target_link_libraries(${META_RENDER_LIBNAME} GL X11 ${BOOST_LIBRARIES})
target_link_libraries(${META_RENDER_LIBNAME} GL X11)

custom_enable_cxx17(${META_RENDER_LIBNAME})

if (MODULE_RENDER_ENABLE_EXAMPLES OR ENABLE_TESTS)
  if (NOT TARGET libmodule_core)
    add_subdirectory("submodules/sway.module_core")
  endif ()

  if (NOT TARGET libmodule_rms)
  add_subdirectory("submodules/sway.module_rms")
endif ()
endif ()

# Добавляем построение примеров
if (MODULE_RENDER_ENABLE_EXAMPLES)
  message(STATUS "Examples have been enabled")

  # Добавляем пути для поиска хедеров
  include_directories("${CMAKE_SOURCE_DIR}/submodules/sway.module_platform-glx11/include")

  if (NOT TARGET module_pltf)
    add_subdirectory("submodules/sway.module_platform-glx11")
  endif ()

  add_subdirectory("examples/01-material")
endif ()

# Добавляем построение тестов
if (MODULE_RENDER_ENABLE_TESTS)
  message(STATUS "Tests have been enabled")

  add_subdirectory(tests)
endif ()
