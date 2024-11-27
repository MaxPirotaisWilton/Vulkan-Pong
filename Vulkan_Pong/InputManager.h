#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager
{
    private:
        glm::vec2 normMousePos;
        inline static InputManager* inputManagerPointer;

        bool inputs[500] = { false };

    public:
        InputManager();

        static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        void setInputManagerPtr(InputManager* ptr) const { inputManagerPointer = ptr; }

        void onCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        bool getInput(int key) const { return inputs[key]; }
};

