#ifndef DISPLAY
#define DISPLAY
#include "shader_s.h"
#include <GLFW/glfw3.h>
#include "MineMap.h"
#include <memory>
#include <mutex>
#include <shared_mutex>

class Display
{
public:
    explicit Display(GLFWwindow* w, std::shared_ptr< MineMap> m);
    ~Display() = default;
    void Init();

    void Update();
    void UpdateDrawing();
private:
    GLFWwindow* m_window;
    std::shared_ptr<MineMap> m_minemap;
    std::unique_ptr<Shader> m_shader;
    unsigned int VBO, VAO, EBO;
    GLuint VBOs[3];
    GLsizei numVertices;
    GLsizei numBlocks;
    std::unique_ptr<float[]> positions;
    std::unique_ptr<float[]> colors;
    std::unique_ptr<float[]> textures;
    std::shared_timed_mutex m_protect;
};



#endif	// DISPLAY