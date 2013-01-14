#include "renderer.h"

#include <iostream>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GL/glfw3.h>


Renderer::Renderer(int width, int height)
    : GameThread(100)
    , width(width)
    , height(height)
{
}

Renderer::~Renderer()
{
}

void Renderer::operator ()()
{
    init();
    done = false;
    while (!done) {
        beginTick();
        glfwSwapBuffers(window);
        endTick();
    }
}

void Renderer::init()
{
    if (!glfwInit()) {
        std::cout << "Renderer initalization failure\n";
        exit(1);
    }

    window = glfwCreateWindow(width, height, "Peasantformer", 0, 0);

    if (!window) {
        std::cout << "Window creation failure\n";
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glShadeModel(GL_FLAT);

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);


    glewInit();

    glfwSwapInterval(0);

    glfwSetTime(0);

    initNotify();
}
