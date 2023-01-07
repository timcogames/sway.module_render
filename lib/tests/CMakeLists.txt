# Мета-информация о проекте
set(META_GRAPHICS_PRJNAME_TESTS "module_graphics_tests")
set(META_GRAPHICS_LIBNAME_TESTS "lib${META_GRAPHICS_PRJNAME_TESTS}")

project(${META_GRAPHICS_PRJNAME_TESTS} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(GTest_ROOT "${CUSTOM_GTEST_ROOT_DIR}")
set(GTEST_INCLUDE_DIR "${GTest_ROOT}/googletest/include")
set(GTEST_LIBRARY_DIR "${GTest_ROOT}/build/lib")

set(GTEST_MAIN_LIBRARY "${GTEST_LIBRARY_DIR}/gtest_main.lib")

# find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GRAPHICS_SOURCE_TESTS ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${META_GRAPHICS_LIBNAME_TESTS} ${MODULE_GRAPHICS_SOURCE_TESTS} "${GTest_ROOT}/googletest/src/gtest_main.cc")
target_link_libraries(${META_GRAPHICS_LIBNAME_TESTS} libmodule_graphics libmodule_render libmodule_core ${GTEST_LIBRARY_DIR}/libgtest.a ${CMAKE_DL_LIBS})

add_custom_command(TARGET ${META_GRAPHICS_LIBNAME_TESTS} POST_BUILD COMMAND ${META_GRAPHICS_LIBNAME_TESTS})
