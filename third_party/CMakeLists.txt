cmake_minimum_required(VERSION 3.14)

project(third_party LANGUAGES C CXX)

# GLFW
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_INSTALL OFF)

add_subdirectory(glfw)

set_property(TARGET glfw PROPERTY FOLDER "ThirdParty")

# docopts
set(DOCOPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docopt)
file(GLOB DOCOPT_FILES "${DOCOPT_DIR}/docopt.cpp" "${DOCOPT_DIR}/*.h")
add_library(docopt STATIC ${DOCOPT_FILES})
target_include_directories(docopt PUBLIC ${DOCOPT_DIR})
set_property(TARGET docopt PROPERTY FOLDER "ThirdParty")

# GLEW
# set(GLEW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glew)
add_subdirectory(glew)
set_property(TARGET libglew_static PROPERTY FOLDER "ThirdParty")

# imgui
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
set(IMGUI_FILES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imconfig.h"
    "${IMGUI_DIR}/imgui.h"
    "${IMGUI_DIR}/imgui_internal.h"
    "${IMGUI_DIR}/imstb_rectpack.h"
    "${IMGUI_DIR}/imstb_textedit.h"
    "${IMGUI_DIR}/imstb_truetype.h"
    "${IMGUI_DIR}/examples/imgui_impl_glfw.h"
    "${IMGUI_DIR}/examples/imgui_impl_opengl3.h"
    "${IMGUI_DIR}/examples/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp")

add_library(imgui STATIC ${IMGUI_FILES})

target_link_libraries(imgui
    glfw
    libglew_static)

target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_include_directories(imgui PUBLIC ${IMGUI_DIR}/examples)

set_property(TARGET imgui PROPERTY FOLDER "ThirdParty")