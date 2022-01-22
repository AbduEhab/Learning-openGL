#include <Engine.h>

double TICKS_LAST_FRAME = 0;

static double deltaTime = glfwGetTime();

static TUNA::Window *window;

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
};

void Update(float deltatime)
{
    {
        deltaTime = glfwGetTime() - TICKS_LAST_FRAME;

        std::cout << deltaTime << std::endl;

        TICKS_LAST_FRAME = glfwGetTime();

        if (TUNA::Input::is_key_down(GLFW_KEY_ESCAPE))
        {
            window->close();
        }

        if (TUNA::Input::is_key_down(GLFW_KEY_ENTER) && TUNA::Input::is_key_down(GLFW_KEY_RIGHT_ALT))
        {
            return; // temp till I figure out why it lags

            bool full = window->_is_fullscreen;

            glfwDestroyWindow(window->_window);

            window = TUNA::Window::create_window(!full);

            std::cout << "comb reg" << std::endl;
        }
    }
}

// const Vertex challenge1Square[]{
//     {glm::vec3{-0.4f, 0.125f, 0.0f}, glm::vec4{0.4f, 0.521f, 0.960f, 1.0f}},
//     {glm::vec3{-0.125f, 0.125f, 0.0f}, glm::vec4{0.490f, 0.443f, 0.956f, 1.0f}},
//     {glm::vec3{0.0f, 0.5f, 0.0f}, glm::vec4{0.686f, 0.443f, 0.956f, 1.0f}},
//     {glm::vec3{0.125f, 0.125f, 0.0f}, glm::vec4{0.917f, 0.443f, 0.956f, 1.0f}},
//     {glm::vec3{0.4f, 0.125f, 0.0f}, glm::vec4{0.807f, 0.317f, 0.250f, 1.0f}},
//     {glm::vec3{0.13f, -0.125f, 0.0f}, glm::vec4{0.807f, 0.250f, 0.682f, 1.0f}},
//     {glm::vec3{0.29f, -0.6f, 0.0f}, glm::vec4{0.956f, 0.631f, 0.443f, 1.0f}},
//     {glm::vec3{0.0f, -0.29f, 0.0f}, glm::vec4{0.956f, 0.843f, 0.443f, 1.0f}},
//     {glm::vec3{-0.29f, -0.6f, 0.0f}, glm::vec4{0.862f, 0.956f, 0.443f, 1.0f}},
//     {glm::vec3{-0.13f, -0.125f, 0.0f}, glm::vec4{0.584f, 0.956f, 0.443f, 1.0f}},

// };

const Vertex challenge1Square[]{
    {glm::vec3(-0.5, -0.5, 0), glm::vec4(.9f, .8f, .2f, 1)},
    {glm::vec3(-0.5, 0.5, 0), glm::vec4(.2f, .9f, .8f, 1)},
    {glm::vec3(0.5, 0.5, 0), glm::vec4(.8f, .2f, .9f, 1)},
    {glm::vec3(0.5, -0.5, 0), glm::vec4(.2f, .9f, .8f, 1)},

};

const int challenge1Elements[]{0, 1, 1, 2, 2, 3, 3, 0};

void Render(GLFWwindow *window)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.266f, 0.466f, 0.698f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    uint32_t challenge1Vao;
    uint32_t challenge1Vbo;
    uint32_t challenge1Ebo;

    glCreateVertexArrays(1, &challenge1Vao);
    glBindVertexArray(challenge1Vao);

    glGenBuffers(1, &challenge1Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, challenge1Vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(challenge1Square), challenge1Square, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &challenge1Ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, challenge1Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(challenge1Elements), challenge1Elements, GL_STATIC_DRAW);

    glBindVertexArray(challenge1Vao);
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
}

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void GLAPIENTRY MessageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar *message,
                                const void *userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
}

int main(int, char *args[])
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        std::cout << "[ERROR]: GLFW failed to initialize." << std::endl;
        return -1;
    }

    window = TUNA::Window::create_window(1280, 720, "Learning-GL", false);

    // gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    gladLoadGL();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
    // std::string a = TUNA::IO::read_file(BINARY_DIRECTORY + "a");

    {
        TUNA::Shader s("s", BINARY_DIRECTORY + "a");

        s.bind();

        while (!glfwWindowShouldClose(window->_window))
        {
            glfwPollEvents();
            Update(deltaTime);
            Render(window->_window);
        }
    }

    TUNA::Window::free_window(window);
    glfwTerminate();
}
