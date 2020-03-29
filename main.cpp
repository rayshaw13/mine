#include <iostream>
#include <string>
#include <sstream>
#include "MineMap.h"
#include "player.h"
#include "Juger.h"
#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
// #include <locale.h>

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "mine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
    // // setlocale(LC_CTYPE,"");
    // int height,width,num;
    // std::cout<<"Plz input minemap's height:";
    // std::cin>>height;
    // std::cout<<"Plz input minemap's width:";
    // std::cin>>width;
    // std::cout<<"Plz input mine number:";
    // std::cin>>num;
    // auto m = make_shared<MineMap>(height,width,num);
    // std::cin.clear();
    // //std::cin.sync();
    //  std::cin.ignore();
    // Player pl(m);
    // Juger jl(m);
    // std::string pos;
    // while (std::getline(std::cin, pos))
    // {
    //     if(!pos.empty()&&tolower(pos.front())=='q'){
    //         break;
    //     }
    //     std::cout<<"You Clicked the Position:"<<pos<<std::endl;
    //     istringstream poss(pos);
    //     int x,y;
    //     poss>>x>>y;
    //     std::vector<int> click{x,y};
    //     int ret = pl.SingleLeftClick(click);
    //     if(ret==-1) {
    //         break;
    //     }
    //     ret = jl.DoJuge();
    //     if(ret == 1) {
    //         break;
    //     }
    // }
    // getchar();
    
    // return 0;
}