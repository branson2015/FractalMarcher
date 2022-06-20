#include <iostream>
#include <memory>
#include <vector>

#include <openvkl/openvkl.h>
#include <glm/glm.hpp>

#include "window.hpp"
#include "shader.hpp"

VKLDevice initializeOpenVKL(){
    VKLDevice device = nullptr;

    vklLoadModule("cpu_device");
    device = vklNewDevice("cpu");
    vklCommitDevice(device);

    assert(device != nullptr);
    
    return device;
}

struct Vertex{
    Vertex(const glm::vec3 p):position(p){}
    glm::vec3 position;
};

/* struct Texture{
    Texture(int _id, std::string _type, std::string _path): id(_id), type(_type), path(_path){}
    bool operator==(const Texture& rhs){ return id == rhs.id; }
    unsigned int id;
    std::string type;
    std::string path;
}; */


unsigned int VAO, VBO, EBO;
std::vector<Vertex> vertices;
std::vector<unsigned int> indices;
//std::vector<Texture> textures;



void setupDrawTest(){

    vertices.insert(vertices.end(), {
        glm::vec3(-1.f, -1.f, 0.f),
        glm::vec3(0.f, 1.f, 0.f),
        glm::vec3(1.f, -1.f, 0.f)
    });
    indices.insert(indices.end(), {0, 1, 2});


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    /* glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)); */

    glBindVertexArray(0);

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
        // glfwGetFramebufferSize(window, &display_w, &display_h);
        // glViewport(0, 0, display_w, display_h);
        


        glfwSwapBuffers(window);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




        /*unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
         for(unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            std::string number;
            std::string name = textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++);

            std::string uniformName = name + number;
            shader->setInt(uniformName, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        } 
        glActiveTexture(GL_TEXTURE0);*/

        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        
    }
}

int main(int argc, char **argv){
    
    Window window;
    if(!window.createWindow()){
        return -1;
    }

    Shader shader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs");
    shader.bind();
    
    setupDrawTest();
    
    run(window.getGLFWWindow());

    return 0;
    VKLDevice device = initializeOpenVKL();

    

    




    
}