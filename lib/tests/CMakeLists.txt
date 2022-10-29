# Мета-информация о проекте
set(META_PROJECT_NAME_TESTS module_graphics_tests)
set(META_LIB_NAME_TESTS lib${META_PROJECT_NAME_TESTS})

project(${META_PROJECT_NAME_TESTS} C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_NO_SYSTEM_PATHS TRUE)
set(BOOST_COMPONENTS unit_test_framework)
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")

find_package(Boost 1.69.0 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
if(NOT Boost_FOUND)
  message(FATAL_ERROR "Fatal error: Boost (version >= 1.69.0) required.")
else()
  message(STATUS "Boost includes: ${BOOST_INCLUDEDIR}")
  message(STATUS "Boost libs: ${BOOST_LIBRARYDIR}")

  include_directories(${BOOST_INCLUDEDIR})
endif()

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GRAPHICS_SOURCE_TESTS ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${META_LIB_NAME_TESTS} ${MODULE_GRAPHICS_SOURCE_TESTS})

target_include_directories(${META_LIB_NAME_TESTS} PRIVATE ${BOOST_INCLUDEDIR})
target_link_libraries(${META_LIB_NAME_TESTS} libmodule_graphics libmodule_gapi_dummy libmodule_core ${BOOST_LIBRARYDIR} ${CMAKE_DL_LIBS})

add_custom_command(TARGET ${META_LIB_NAME_TESTS} POST_BUILD COMMAND ${META_LIB_NAME_TESTS})
