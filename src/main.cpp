
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include "Assets.h"

#include "Mesh.h"
#include "Shader.h"
#include "WindowManager.h"
#include "Camera.h"



glm::mat4 calculateMvpMatrix(const Camera & camera) {

    glEnable(GL_DEPTH_TEST);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f));
    model = glm::scale(model, glm::vec3(1.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 view = camera.getView();
    glm::mat4 projection = glm::perspective(glm::radians(30.0f),
        WindowManager::WINDOW_SIZE.x/ WindowManager::WINDOW_SIZE.y, 0.1f, 100.0f);

    return projection * view * model;
}

int main() {
    GLFWwindow *window = WindowManager::openWindow();

    Shader* shader =new Shader("shaders/triangle.vert", "shaders/triangle.frag");
    shader->use();
    Mesh* mesh =new Mesh();
    Camera camera;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //loading image here
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, nrChannels;
    const fs::path path = resolveAssetPath("textures/container.jpg");
    const char* texture_path = path.c_str();
    unsigned char *data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

    if (!data) {
        std::cout << "Failed to load texture: " << texture_path << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);



    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        shader->setInt("ourTexture", 0);

        camera.processInput(window);
        shader->setMatrix("mvp", calculateMvpMatrix(camera)) ;
        mesh->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    delete shader;
    delete mesh;
    WindowManager::closeWindow();
    return 0;
}




