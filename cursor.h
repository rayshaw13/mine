#ifndef CURSOR
#define CURSOR
#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <memory>
class Cursor
{
public:
    explicit Cursor(GLFWwindow* m);
    ~Cursor();

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
private:
    GLFWwindow* m_window;
};

#endif	// CURSOR