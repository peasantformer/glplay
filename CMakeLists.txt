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

    src/renderer/renderer.cpp
    src/renderer/glframe.cpp
    src/renderer/camera.cpp
    src/renderer/glmeshdata.cpp
    src/renderer/glmeshsource.cpp
    src/renderer/shaderprogram.cpp
    src/renderer/packets/glpacket.cpp
    src/renderer/packets/glcompile.cpp
    src/renderer/packets/glcompilegeometry.cpp
    src/renderer/packets/glcompileshader.cpp
    src/renderer/packets/glrender.cpp

    src/world/world.cpp
    src/world/space.cpp
    src/world/worldcontainer.cpp
    src/world/bases/components/base.cpp
    src/world/bases/components/renderable.cpp
    src/world/bases/components/physical.cpp
    src/world/bases/components/animatable.cpp
    src/world/bases/components/controllable.cpp
    src/world/bases/components/character.cpp
    src/world/bases/player.cpp
    src/world/bases/prop.cpp
    src/world/actions/worldaction.cpp
    src/world/actions/keypress.cpp
    src/world/actions/mousemove.cpp
    src/world/gamemodes/sandbox.cpp

    src/world/objects/primitive/cube.cpp

    src/engine/engine.cpp

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

