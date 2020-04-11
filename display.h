#ifndef DISPLAY
#define DISPLAY
#include "shader_s.h"
#include <GLFW/glfw3.h>
#include "MineMap.h"
#include <memory>

class Display
{
public:
    explicit Display(GLFWwindow* w, std::shared_ptr< MineMap> m);
    ~Display() = default;
    void Init();

    void Update();
private:
    GLFWwindow* m_window;
    std::shared_ptr<MineMap> m_minemap;
    std::unique_ptr<Shader> m_shader;
    unsigned int VBO, VAO, EBO;
};



#endif	// DISPLAY