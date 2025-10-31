//
// Created by ju on 10/30/25.
//

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/vec2.hpp"

class WindowManager {
public:

    static constexpr glm::vec2 WINDOW_SIZE = glm::vec2(1600, 800);
    static GLFWwindow * openWindow() ;
    static void closeWindow();
};
