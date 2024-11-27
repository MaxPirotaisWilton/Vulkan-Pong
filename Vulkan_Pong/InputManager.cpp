#include "InputManager.h"

#include <iostream>

InputManager* inputManagerPointer = new InputManager();

InputManager::InputManager()
{
    normMousePos = glm::vec2(0.5f);
}

void InputManager::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    inputManagerPointer->onCursorPosCallback(window,xpos,ypos);
}

void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    inputManagerPointer->onKeyCallback(window, key, scancode,action,mods);
}

void InputManager::onCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    int width, height;

    glfwGetWindowSize(window, &width, &height);
    normMousePos = glm::vec2(2 * (xpos / (float)width) - 1.0f,
        2 * (ypos / (float)height) - 1.0f);
}

void InputManager::onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {

        const char* key_name = glfwGetKeyName(key, scancode);
        std::cout << "Key pressed: { key:" << key << " } \n";
        inputs[key] = true;

    }
    else if (action == GLFW_RELEASE) {

        const char* key_name = glfwGetKeyName(key, scancode);
        std::cout << "Key released: { key:" << key << " } \n";
        inputs[key] = false;

    }
}
