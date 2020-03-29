#include "cursor.h"
#include <iostream>

void Cursor::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "Cursor Position at (" << xpos << " : " << ypos << std::endl;
    }
}

Cursor::Cursor(GLFWwindow* m) : m_window(m)
{
    if(m_window==nullptr) {
        std::cerr<<"Cursor:Cursor m_window is null"<<std::endl;
        return;
    }
    glfwSetMouseButtonCallback(m_window, Cursor::mouse_button_callback);
}

Cursor::~Cursor()
{
}
