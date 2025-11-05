#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "GetCellVertices.h"
#include "Vec2.h"
#include "Snake.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Snake", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    std::ifstream vertexFile("shaders/snake.vs");
    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();
    std::string vertexShaderCode = vertexStream.str();
    const char* vertexShaderSource = vertexShaderCode.c_str();

    std::ifstream fragmentFile("shaders/snake.fs");
    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    std::string fragmentShaderCode = fragmentStream.str();
    const char* fragmentShaderSource = fragmentShaderCode.c_str();

    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    std::vector<float> fieldVerts;

    for (int y = 0; y < 32; y++)
{
    for (int x = 0; x < 32; x++)
    {
        std::vector<vec2> Vertices = GetCellVertices(x, y, SCR_WIDTH, SCR_HEIGHT, 32, 32);

        for (auto& v : Vertices)
        {
            fieldVerts.push_back(v.x);
            fieldVerts.push_back(v.y);
        }
    }
}

        GLuint vao, vbo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);


        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, fieldVerts.size() * sizeof(float), fieldVerts.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        
        
        Snake snake;
        
        std::vector<float> snakeVerts;
    for (auto& cell : snake.getBody())
    {
        auto verts = GetCellVertices(cell.x, cell.y, SCR_WIDTH, SCR_HEIGHT, 32, 32);
        for (auto& v : verts)
        {
            snakeVerts.push_back(v.x);
            snakeVerts.push_back(v.y);
        }
    }
    
    GLuint snakeVAO, snakeVBO;
    glGenVertexArrays(1, &snakeVAO);
    glGenBuffers(1, &snakeVBO);

    glBindVertexArray(snakeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, snakeVBO);
    glBufferData(GL_ARRAY_BUFFER, snakeVerts.size() * sizeof(float), snakeVerts.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    // render loop
    // ---------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // ---------------------------------------
        processInput(window);

        // render
        // ---------------------------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 32*32*6);
        glBindVertexArray(0);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(snakeVAO);
        glDrawArrays(GL_TRIANGLES, 0, snake.getBody().size() * 6);
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
