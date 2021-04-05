#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/window.hpp"
#include "engine/shader.hpp"

#include "engine/input.hpp"

#include <iostream>

static float R = 0.2f, G = 0.0f, B = 0.0F; 
//const static Shader shader("../games/AG03/vertex.vs", "../games/AG03/fragment.fs");

void handleInput(float dt, const Shader& s) 
{
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_R) && (R < 1.0f)) {        
        R += 0.005;
        s.use();
        s.set("addColor", R, G, B);
        std::cout << "Red:   " << R << std::endl;  
    }

    if (input->isKeyPressed(GLFW_KEY_B) && (B < 1.0f)) {        
        B += 0.005;
        s.use();
        s.set("addColor", R, G, B);
        std::cout << "Blue:  " << B << std::endl;  
    }

    if (input->isKeyPressed(GLFW_KEY_G) && (G < 1.0f)) {        
        G += 0.005;
        s.use();
        s.set("addColor", R, G, B);
        std::cout << "Green: " << G << std::endl;  
    }
}

uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
    float vertices[] = {
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f
    };

    uint32_t indices[] = {
        0, 2, 1
    };

    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}


void render() {
    glClear(GL_COLOR_BUFFER_BIT);

   
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    

    uint32_t VBO, EBO;
    const uint32_t VAO = createVertexData(&VBO, &EBO);
    

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //shaderLoad();
    const Shader shader("../games/AG03/vertex.vs", "../games/AG03/fragment.fs");
    shader.use();
    shader.set("addColor", R, G, B);
    

    glBindVertexArray(VAO);

    float lastFrame = 0.0f;

    while (window->alive())
    {
        const float currentFrame = glfwGetTime();
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInput(deltaTime, shader);

        render();

        window->frame();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return 0;
}