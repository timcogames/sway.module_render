# Мета-информация о проекте
set(META_GRAPHICS_EXAMPLE_PRJNAME "module_graphics_examples_triangle2")
set(META_GRAPGICS_EXAMPLE_LIBNAME "lib${META_GRAPHICS_EXAMPLE_PRJNAME}")

project(${META_GRAPHICS_EXAMPLE_PRJNAME} CXX)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${MODULE_GRAPHICS_DIR}/submodules/sway.module_platform-glx11/lib/include")

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GRAPHICS_SOURCE_EXAMPLES "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable(${META_GRAPGICS_EXAMPLE_LIBNAME} ${MODULE_GRAPHICS_SOURCE_EXAMPLES})
target_link_libraries(${META_GRAPGICS_EXAMPLE_LIBNAME} libmodule_platform_glx11 libmodule_graphics libmodule_core)
