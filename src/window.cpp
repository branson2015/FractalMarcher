#include "window.hpp"

Window::Window() {}

Window::~Window() {}

//case 0: fullscreen (default)
//case 1: fullscreen borderless
//case 2: windowed
bool Window::createWindow(int window_mode){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    switch(window_mode){
        case 0:
        default:
            window = glfwCreateWindow(0, 0, "Fractal Marcher", monitor, NULL);
            break;

        case 1:
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

            window = glfwCreateWindow(mode->width, mode->height, "Fractal Marcher", monitor, NULL);
            break;

        case 2:
            window = glfwCreateWindow(640, 480, "Fractal Marcher", NULL, NULL);
            break;
    }

    if(window == nullptr){
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return false;
    }

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    return true;
}