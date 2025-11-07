#include "processInput.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ConsoleInput.h"

void processInput(GLFWwindow* window, Snake& snake)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        snake.setDirection({0.0f, 1.0f});
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        snake.setDirection({0.0f, -1.0f});
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        snake.setDirection({-1.0f, 0.0f});
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        snake.setDirection({1.0f, 0.0f});
        
    char c = readCharNonBlocking();
    switch (c)
    {
    case 'w': case 'W': snake.setDirection({0.0f, 1.0f}); break;
    case 's': case 'S': snake.setDirection({0.0f, -1.0f}); break;
    case 'a': case 'A': snake.setDirection({-1.0f, 0.0f}); break;
    case 'd': case 'D': snake.setDirection({1.0f, 0.0f}); break;
    }
}
