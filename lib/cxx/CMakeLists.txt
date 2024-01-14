#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#---------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#---------------------------------------------------------------------------------
# Coverage
#---------------------------------------------------------------------------------

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fPIE")

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")

# Добавляем пути для поиска хедеров
include_directories("${SYSTEM_X11_INCLUDE_DIRS}")
include_directories("${GLOB_THIRD_PARTY_DIR}/json/include")
include_directories("${GLOB_GTEST_ROOT_DIR}/include")
include_directories("${GLOB_GMOCK_ROOT_DIR}/include")
include_directories("${MODULE_RENDER_LIST_DIR}/lib/cxx/include")
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
# Build object library
#---------------------------------------------------------------------------------

if(NOT TARGET ${MODULE_RENDER_OBJ_TARGET})
  set(MODULE_RENDER_LIB_SOURCES "${MODULE_RENDER_ROOT_DIR}/lib/cxx/src/*.*")
  set(MODULE_RENDER_ENABLE_FILE_EXPORT TRUE)

  create_object_library(${MODULE_RENDER_OBJ_TARGET} ${MODULE_RENDER_LIB_SOURCES} ${MODULE_RENDER_ENABLE_FILE_EXPORT})
  enable_cxx17(${MODULE_RENDER_OBJ_TARGET})
endif()

if(MODULE_RENDER_ENABLE_TESTS OR MODULE_RENDER_USE_GMOCK)
  target_compile_definitions(${MODULE_RENDER_OBJ_TARGET} PUBLIC -DRENDER_USE_GMOCK)
endif()

#---------------------------------------------------------------------------------
# Create interfaces
#---------------------------------------------------------------------------------

set(MODULE_RENDER_DEPENDENCY_LIST "module_render_dependences")

set(TARGET_OBJECT_LIST)
set(MODULE_CORE_OBJ_TARGET "module_core_obj")
set(MODULE_RMS_OBJ_TARGET "module_rms_obj")

if(TARGET ${MODULE_CORE_OBJ_TARGET})
  list(APPEND TARGET_OBJECT_LIST $<TARGET_OBJECTS:${MODULE_CORE_OBJ_TARGET}>)
endif()

if(TARGET ${MODULE_RMS_OBJ_TARGET})
  list(APPEND TARGET_OBJECT_LIST $<TARGET_OBJECTS:${MODULE_RMS_OBJ_TARGET}>)
endif()

# if(TARGET ${MODULE_RENDER_OBJ_TARGET})
#   list(APPEND TARGET_OBJECT_LIST $<TARGET_OBJECTS:${MODULE_RENDER_OBJ_TARGET}>)
# endif()

create_interface(${MODULE_RENDER_DEPENDENCY_LIST} ${TARGET_OBJECT_LIST})

#---------------------------------------------------------------------------------
# [EMSCRIPTEN] Bitcode
#---------------------------------------------------------------------------------

if(NOT MODULE_RENDER_LIB_TYPE STREQUAL "object")
  if(GLOB_EMSCRIPTEN_PLATFORM)
    create_emscripten_library(${MODULE_RENDER_LIB_TARGET} ${MODULE_RENDER_ENVIRONMENT} ${MODULE_RENDER_COMPILATION} OUTPUT_TARGET_NAME_LIST)

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

    # target_link_libraries(${MODULE_RENDER_LIB_TARGET} ${MODULE_RENDER_DEPENDENCY_LIST})
  else()
    create_clang_library(${MODULE_RENDER_LIB_TARGET} "${MODULE_RENDER_ROOT_DIR}/lib/cxx/src/*.*")
  endif()
endif()
