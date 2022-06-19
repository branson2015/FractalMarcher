#ifndef FRACTAL_MARCHER_WINDOW_HPP
#define FRACTAL_MARCHER_WINDOW_HPP

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

//singleton
class Window {
public:
    Window();
    ~Window();

    GLFWwindow * getGLFWWindow() { return window; }
    bool createWindow(int window_mode=1);

private:
    int width;
    int height;
    GLFWwindow* window;
};

#endif