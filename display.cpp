#include "display.h"
#include "elements.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Display::Display(GLFWwindow* w, std::shared_ptr< MineMap> m):
    m_window(w),m_minemap(m)
{
    std::string path="res/";
    auto vertexShader=path+"texture.vs";
    auto fragmentShader=path+"texture.fs";
    m_shader = std::make_unique<Shader>(vertexShader, fragmentShader);
    Init();
}

void Display::Init()
{
    float hlen = 2.0f/m_minemap->GetRows();
    float wlen = 2.0f/m_minemap->GetColums();
    numBlocks = m_minemap->GetRows() * m_minemap->GetColums();
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    Block block;
    block.position= {
        glm::vec3(-1.0f+wlen, 1.0f-hlen, 0.0f),
        glm::vec3(-1.0f+wlen, 1.0f+0.0f, 0.0f),
        glm::vec3(-1.0f+0.0f, 1.0f-hlen, 0.0f),
        glm::vec3(-1.0f+0.0f, 1.0f+0.0f, 0.0f),
        glm::vec3(-1.0f+0.0f, 1.0f-hlen, 0.0f),
        glm::vec3(-1.0f+wlen, 1.0f+0.0f, 0.0f)
    };
    block.color = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    };
    block.textue = {
        glm::vec2(1.0f, 1.0f), // top right
        glm::vec2(1.0f, 0.0f), // bottom right
        glm::vec2(0.0f, 1.0f),  // top left
        glm::vec2(0.0f, 0.0f), // bottom left
        glm::vec2(0.0f, 1.0f),  // top left
        glm::vec2(1.0f, 0.0f) // bottom right
    };
    numVertices = block.position.size();

    vector<vector<decltype(block.position)>> block_positions(m_minemap->GetRows(), 
        vector<decltype(block.position)>(m_minemap->GetColums(), block.position));
    for (int i = 0; i < block_positions.size(); ++i){
        if (i != 0){
            for (int k = 0; k < block_positions[i][0].size(); ++k){
                block_positions[i][0][k] = block_positions[i - 1][0][k] + glm::vec3(0.0f, -hlen, 0.0f);
            }
        }
        for (int j = 1; j < block_positions[i].size(); ++j){
            for (int k = 0; k < block_positions[i][j].size(); ++k){
                block_positions[i][j][k] = block_positions[i][j - 1][k] + glm::vec3(wlen, 0.0f, 0.0f);
            }
        }
    }

    positions = std::unique_ptr<float[]> (new float[numBlocks * block.position.size()*3]);
    for (int i = 0; i < block_positions.size(); ++i){
        for (int j = 0; j < block_positions[i].size(); ++j){
            for (int k = 0; k < block_positions[i][j].size(); ++k){
                positions[((i*10+j)*numVertices+k)*3] = block_positions[i][j][k].x;
                positions[((i*10+j)*numVertices+k)*3+1] = block_positions[i][j][k].y;
                positions[((i*10+j)*numVertices+k)*3+2] = block_positions[i][j][k].z;
            }
        }
    }

    vector<vector<decltype(block.color)>> block_colors(m_minemap->GetRows(), 
        vector<decltype(block.color)>(m_minemap->GetColums(), block.color));
    colors = std::unique_ptr<float[]> (new float[numBlocks * block.color.size()*3]);
    for (int i = 0; i < block_colors.size(); ++i){
        for (int j = 0; j < block_colors[i].size(); ++j){
            for (int k = 0; k < block_colors[i][j].size(); ++k){
                colors[((i*10+j)*numVertices+k)*3] = block_colors[i][j][k].r;
                colors[((i*10+j)*numVertices+k)*3+1] = block_colors[i][j][k].g;
                colors[((i*10+j)*numVertices+k)*3+2] = block_colors[i][j][k].b;
            }
        }
    }

    vector<vector<decltype(block.textue)>> block_textures(m_minemap->GetRows(), 
        vector<decltype(block.textue)>(m_minemap->GetColums(), block.textue));
    textures = std::unique_ptr<float[]> (new float[numBlocks * block.textue.size()*3]);
    for (int i = 0; i < block_textures.size(); ++i){
        for (int j = 0; j < block_textures[i].size(); ++j){
            for (int k = 0; k < block_textures[i][j].size(); ++k){
                textures[((i*10+j)*numVertices+k)*2] = block_textures[i][j][k].x;
                textures[((i*10+j)*numVertices+k)*2+1] = block_textures[i][j][k].y;
            }
        }
    }

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(3, VBOs);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, numBlocks*numVertices*3*sizeof(float), positions.get(), GL_STATIC_DRAW);


    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, numBlocks*numVertices*3*sizeof(float), colors.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(0));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER,numBlocks*numVertices*2*sizeof(float), textures.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)(0));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("res/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}


void Display::Update()
{
    std::shared_lock<std::shared_timed_mutex> reader(m_protect);
    glClear(GL_COLOR_BUFFER_BIT);
    m_shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0 , numVertices*numBlocks);
    glFlush();
}

void Display::UpdateDrawing()
{
    std::unique_lock<std::shared_timed_mutex> writer(m_protect);
    auto &mineMap = m_minemap->GetMineMap();
    for(int i=0;i<mineMap.size();++i) {
        for(int j=0;j<mineMap[i].size();++j) {
            for(int k=0;k<numVertices;++k) {
                if(mineMap[i][j] == MineSymbol::BLANK) {
                    colors[((i*10+j)*numVertices+k)*3] = 0.5f;
                    colors[((i*10+j)*numVertices+k)*3 +1] = 0.5f;
                    colors[((i*10+j)*numVertices+k)*3 +2] = 0.5f;
                }
            }
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, numBlocks*numVertices*3*sizeof(float), colors.get(), GL_STATIC_DRAW);

}