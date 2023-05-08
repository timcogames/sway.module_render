# Мета-информация о проекте
set(META_RENDER_EXAMPLE_PRJNAME "module_render_examples_material")
set(META_RENDER_EXAMPLE_LIBNAME "lib${META_RENDER_EXAMPLE_PRJNAME}")

project(${META_RENDER_EXAMPLE_PRJNAME} CXX)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${MODULE_RENDER_DIR}/submodules/sway.module_platform-glx11/lib/include")

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_RENDER_SOURCE_EXAMPLES "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable(${META_RENDER_EXAMPLE_LIBNAME} ${MODULE_RENDER_SOURCE_EXAMPLES})
target_link_libraries(${META_RENDER_EXAMPLE_LIBNAME} GLU libmodule_render libmodule_rms libmodule_pltf libmodule_core)
