//
// Created by ju on 10/31/25.
//

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_transform.hpp"


class Camera {

    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up    = glm::vec3(0.0f, 1.0f,  0.0f);
    glm::vec3 position = glm::vec3(0.0f, 30.0f,  3.0f);;
    float yaw   = -90.0f;
    float pitch = 0.0f;


    glm::vec2 mousePosition = glm::vec2(0.0f);
    bool firstMousePos = true;
    static glm::vec2 getMousePosition(GLFWwindow* window);
    glm::vec2 getDeltaMousePosition(GLFWwindow *window);
public:
    [[nodiscard]] glm::mat4 getView() const {
        return glm::lookAt(position, position + front, up);
    }
    void processInput(GLFWwindow* window);
};
