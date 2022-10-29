# Мета-информация о проекте
set(META_PROJECT_NAME_EXAMPLES module_graphics_examples_triangle2)
set(META_LIB_NAME_EXAMPLES lib${META_PROJECT_NAME_EXAMPLES})

project(${META_PROJECT_NAME_EXAMPLES} C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_NO_SYSTEM_PATHS TRUE)
# set(BOOST_COMPONENTS filesystem)
# set(BOOST_INCLUDEDIR "${BOOST_ROOT}/")
# set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")

# find_package(Boost 1.69.0 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
# if(NOT Boost_FOUND)
#   message(FATAL_ERROR "Fatal error: Boost (version >= 1.69.0) required.")
# else()
#   message(STATUS "Boost includes: ${BOOST_INCLUDEDIR}")
#   message(STATUS "Boost libs: ${BOOST_LIBRARYDIR}")

#   include_directories(${BOOST_INCLUDEDIR})
# endif()

include_directories("${MODULE_GRAPHICS_DIR}/submodules/sway.module_platform-glx11/lib/include")

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GRAPHICS_SOURCE_EXAMPLES ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${META_LIB_NAME_EXAMPLES} ${MODULE_GRAPHICS_SOURCE_EXAMPLES})

# target_include_directories(${META_LIB_NAME_EXAMPLES} PRIVATE ${BOOST_INCLUDEDIR})
# target_link_libraries(${META_LIB_NAME_EXAMPLES} libmodule_platform_glx11 libmodule_graphics libmodule_core ${BOOST_LIBRARIES})
target_link_libraries(${META_LIB_NAME_EXAMPLES} libmodule_platform_glx11 libmodule_graphics libmodule_core)
