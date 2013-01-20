include(cmake/toolchains/clang/toolchain.cmake)

project(glplay)
cmake_minimum_required(VERSION 2.8)

include_directories(
    .
    lib/glfw/include
    lib/ezoptionparser
    lib/utfcpp/source
    lib/glm
)

add_definitions(-g -std=c++11 -stdlib=libc++)

set(SRC_LIST
    src/base/thread.cpp
    src/base/gamethread.cpp

    src/util/fileutils.cpp
    src/util/framecounter.cpp
    src/util/framelimiter.cpp
    src/util/blockingqueue.cpp

    src/renderer/glframe.cpp
    src/renderer/gloperation.cpp
    src/renderer/renderer.cpp
    src/renderer/shaderprogram.cpp
    src/renderer/visualdata.cpp
    src/renderer/camera.cpp

    src/renderer/operations/glopupload.cpp
    src/renderer/operations/glopgeometryupload.cpp
    src/renderer/operations/glopshaderupload.cpp
    src/renderer/operations/glopshaderprogramupload.cpp
    src/renderer/operations/glopshaderbatchupload.cpp
    src/renderer/operations/gloprender.cpp


    src/engine/engine.cpp
    src/world/world.cpp

    src/optionparser.cpp
    src/main.cpp
)

add_library(glfw3 STATIC IMPORTED)
set_property(TARGET glfw3 PROPERTY IMPORTED_LOCATION ../lib/glfw/cmake-build/src/libglfw3.a)

set(LIBS_LIST
    glfw3
    GL GLU GLEW Xrandr Xxf86vm
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${LIBS_LIST})
