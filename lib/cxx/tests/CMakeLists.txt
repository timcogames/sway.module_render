# Мета-информация о проекте
set(META_RENDER_PRJNAME_TESTS "module_render_tests")
set(META_RENDER_LIBNAME_TESTS "lib${META_RENDER_PRJNAME_TESTS}")

project(${META_RENDER_PRJNAME_TESTS} CXX)
enable_testing()

set(GTEST_ROOT "${GLOB_GTEST_ROOT_DIR}")
set(GTEST_INC_DIR "${GTEST_ROOT}/include")
set(GTEST_SRC_DIR "${GTEST_ROOT}/src")

set(GMOCK_ROOT "${GLOB_GMOCK_ROOT_DIR}")
set(GMOCK_INC_DIR "${GMOCK_ROOT}/include")

# find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INC_DIR} ${GMOCK_INC_DIR})

file(GLOB MODULE_RENDER_SOURCE_TESTS ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${META_RENDER_LIBNAME_TESTS} ${MODULE_RENDER_SOURCE_TESTS} "${GTEST_SRC_DIR}/gtest_main.cc")
target_link_libraries(${META_RENDER_LIBNAME_TESTS} module_render_obj module_core_obj 
  ${GLOB_GTEST_LIB_DIR}/libgtest.a ${GLOB_GMOCK_LIB_DIR}/libgmock.a)
enable_cxx17(${META_RENDER_LIBNAME_TESTS})

add_test(NAME ${META_RENDER_LIBNAME_TESTS} COMMAND ${META_RENDER_LIBNAME_TESTS})
