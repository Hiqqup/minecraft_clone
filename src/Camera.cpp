//
// Created by ju on 10/31/25.
//

#include "Camera.h"
  glm::vec2 Camera::getMousePosition(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {xpos, ypos};
}

 glm::vec2 Camera::getDeltaMousePosition(GLFWwindow *window) {
    if (firstMousePos) {
        firstMousePos = false;
        mousePosition = getMousePosition(window);
        return {0,0};
    }
    auto newMousePosition = getMousePosition(window);
    glm::vec2 deltaMousePosition = mousePosition - newMousePosition;
    mousePosition = newMousePosition;
    return deltaMousePosition;
}
void Camera::processInput(GLFWwindow* window) {
  const float cameraSpeed = 0.2f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += glm::normalize( front) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= glm::normalize( front) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * cameraSpeed;

    glm::vec2 mouseDelta = getDeltaMousePosition(window);
    float sensitivity = 0.02f;
    mouseDelta*= sensitivity;

    yaw   -= mouseDelta.x;
    pitch += mouseDelta.y;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

}
