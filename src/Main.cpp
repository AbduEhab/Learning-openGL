#include <glad/glad.h>
#include <iostream>

#include <GLFW/glfw3.h>

void Update()
{
}

void Render(GLFWwindow *window)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

void HandleKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void HandleCursorInput(GLFWwindow *window, double xpos, double ypos)
{
}

void HandleMouseInput(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        ;
}

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main(int, char **)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        std::cout << "[ERROR]: GLFW failed to initialize." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Learning-openGL", NULL, NULL);

    if (!window)
    {
        std::cout << "[ERROR]: GLFW failed to create a window." << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetKeyCallback(window, HandleKeyboardInput);

    glfwSetCursorPosCallback(window, HandleCursorInput);

    glfwSetMouseButtonCallback(window, HandleMouseInput);

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        Update();
        Render(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
