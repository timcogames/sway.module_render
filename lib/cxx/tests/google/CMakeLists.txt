#--------------------------------------------------------------------------------
# CMake version
#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#--------------------------------------------------------------------------------
# Enable testing
#--------------------------------------------------------------------------------

enable_testing()

#--------------------------------------------------------------------------------
# Set dependency paths
#--------------------------------------------------------------------------------

set(GTEST_ROOT "${GLOB_GTEST_ROOT_DIR}")
set(GTEST_INC_DIR "${GTEST_ROOT}/include")
set(GTEST_SRC_DIR "${GTEST_ROOT}/src")

set(GMOCK_ROOT "${GLOB_GMOCK_ROOT_DIR}")
set(GMOCK_INC_DIR "${GMOCK_ROOT}/include")

#--------------------------------------------------------------------------------
# Include dependency headers
#--------------------------------------------------------------------------------

include_directories("${GTEST_INC_DIR}")
include_directories("${GMOCK_INC_DIR}")
include_directories("${MODULE_RENDER_LIST_DIR}/lib/cxx/include")
include_directories("${MODULE_RENDER_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")

#--------------------------------------------------------------------------------
# Find project test files
#--------------------------------------------------------------------------------

file(GLOB MODULE_RENDER_TEST_SOURCES "${MODULE_RENDER_ROOT_DIR}/lib/cxx/tests/*/*.spec.cpp")

#--------------------------------------------------------------------------------
# Build tests
#--------------------------------------------------------------------------------

add_executable(${MODULE_RENDER_TEST_TARGET} ${MODULE_RENDER_TEST_SOURCES} "${GTEST_SRC_DIR}/gtest_main.cc")
target_link_libraries(${MODULE_RENDER_TEST_TARGET} module_render_obj module_core_obj pthread ${GLOB_GTEST_LIB_DIR}/libgtest.a ${GLOB_GMOCK_LIB_DIR}/libgmock.a)
enable_cxx17(${MODULE_RENDER_TEST_TARGET})

add_test(NAME ${MODULE_RENDER_TEST_TARGET} COMMAND ${MODULE_RENDER_TEST_TARGET})
