#include <iostream>
#include <memory>

#include <openvkl/openvkl.h>

#include "window.hpp"

VKLDevice initializeOpenVKL(){
    VKLDevice device = nullptr;

    vklLoadModule("cpu_device");
    device = vklNewDevice("cpu");
    vklCommitDevice(device);

    assert(device != nullptr);
    
    return device;
}



void run(GLFWwindow *window){
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        // Start the Dear ImGui frame
        // ImGui_ImplOpenGL2_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // ImGui::NewFrame();
        // ImGui::Begin( ... );
        // ImGui::End();
        // ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);

    }
}

int main(int argc, char **argv){
    VKLDevice device = initializeOpenVKL();

    Window window;
    if(!window.createWindow()){
        return -1;
    }

    run(window.getGLFWWindow());
}