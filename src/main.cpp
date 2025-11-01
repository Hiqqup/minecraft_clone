
#include <iostream>
#include <optional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include "Assets.h"

#include "ChunkMesh.h"
#include "Shader.h"
#include "WindowManager.h"
#include "Camera.h"
#include "tiny_gltf.h"


glm::mat4 calculateMvpMatrix(const Camera & camera) {

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f));
    model = glm::scale(model, glm::vec3(1.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 view = camera.getView();
    glm::mat4 projection = glm::perspective(glm::radians(30.0f),
        WindowManager::WINDOW_SIZE.x/ WindowManager::WINDOW_SIZE.y, 0.1f, 100.0f);

    return projection * view * model;
}

class ChunkMeshRenderDistance {
    static constexpr glm::uvec2 RENDER_DISTANCE = glm::uvec2(8, 8);
    ChunkMesh* chunks[RENDER_DISTANCE.x][RENDER_DISTANCE.y];
public:
    ChunkMeshRenderDistance() {
        for (int x = 0; x < RENDER_DISTANCE.x; x++) {
            for (int y = 0; y < RENDER_DISTANCE.y; y++) {
                chunks[x][y] = new ChunkMesh(glm::ivec2{x,y});
            }
        }
    }
    void draw()const {
        for (int x = 0; x < RENDER_DISTANCE.x; x++) {
            for (int y = 0; y < RENDER_DISTANCE.y; y++) {
                chunks[x][y]->draw();
            }
        }
    }
    ~ChunkMeshRenderDistance() {
        for (int x = 0; x < RENDER_DISTANCE.x; x++) {
            for (int y = 0; y < RENDER_DISTANCE.y; y++) {
                delete chunks[x][y];
            }
        }

    }
};

int main() {
    GLFWwindow *window = WindowManager::openWindow();


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

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
    auto  shader = std::make_optional<Shader>("shaders/triangle.vert", "shaders/triangle.frag");
    shader->use();
    //auto mesh = std::make_optional<ChunkMesh>(glm::ivec2{0,0});
    auto meshes = std::make_optional<ChunkMeshRenderDistance>();
    Camera camera;


    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        shader->setInt("ourTexture", 0);

        camera.processInput(window);
        shader->setMatrix("mvp", calculateMvpMatrix(camera)) ;
        meshes->draw();
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    meshes.reset();
    shader.reset();
    WindowManager::closeWindow();
    return 0;
}//