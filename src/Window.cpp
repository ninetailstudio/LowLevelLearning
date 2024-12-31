#include "Window.h"

void Window::setWindowHints(const WindowConfig &config)
{
    glfwWindowHint(GLFW_RESIZABLE, config.resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, config.visible ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, config.decorated ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.contextVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.contextVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, config.coreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
}

Window::Window(const WindowConfig &config)
    : width(config.width), height(config.height), title(config.title), glfwWindow(nullptr)
{

    // Initialize GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Set GLFW window hints
    setWindowHints(config);

    // Create the GLFW window
    glfwWindow = glfwCreateWindow(config.width, config.height, config.title, nullptr, nullptr);
    if (!glfwWindow)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Make the window's context current
    glfwMakeContextCurrent(glfwWindow);

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Ensure modern OpenGL functions are available
    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glfwSetWindowUserPointer(glfwWindow, this);

    glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow *window, int button, int action, int mods)
                               { 
        Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (instance) {
            instance->mouseSelector(window, button, action, mods);
        } });

    glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow *window, double xPos, double yPos)
                             { 
        Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (instance) {
            instance->move(window, xPos, yPos);
        } });
    glViewport(0, 0, width, height);
}

Window::~Window()
{
    if (glfwWindow)
    {
        glfwDestroyWindow(glfwWindow);
    }
    glfwTerminate();
}

GLFWwindow *Window::GetGLFWWindow() const
{
    return glfwWindow;
}

void Window::PollEvents() const
{
    glfwPollEvents();
}

int Window::GetWidth() const
{
    return width;
}

int Window::GetHeight() const
{
    return height;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(glfwWindow);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(glfwWindow);
}

#define POINT(s, x, y) std::cout << s << "(" << x << "," << y << ")" << std::endl;

void Window::move(GLFWwindow *window, double xPos, double yPos)
{

    int xWindowCoordinate; // Position of our window top left corner relative to our screen
    int yWindowCoordinate; // Position of our window top left corner relative to our screen
    glfwGetWindowPos(window, &xWindowCoordinate, &yWindowCoordinate);

    // Calculate mouse position relative to screen
    xPosGlobal = static_cast<double>(xWindowCoordinate) + xPos;
    yPosGlobal = static_cast<double>(yWindowCoordinate) + yPos;

    if (dragging)
    {
        glfwSetWindowPos(window, xPosGlobal - xPosLocal, yPosGlobal - yPosLocal);
    }
}

// // Mouse button callback function to initiate dragging or resizing
void Window::mouseSelector(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            // Get the current mouse position when the button is pressed
            glfwGetCursorPos(window, &xPosLocal, &yPosLocal);

            if (yPosLocal <= 30)
            {
                dragging = true;
                // std::cout << "isDraggable" << std::endl;
            }
        }
        else if (action == GLFW_RELEASE)
        {
            dragging = false;
        }
    }
}
