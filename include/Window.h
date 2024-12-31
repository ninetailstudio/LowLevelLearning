#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cmath>

#define DEBUG 1
#define WINDOW_ESCAPE_TO_CLOSE 1

// Configuration struct for window properties
struct WindowConfig {
    const char* title = "Window";       // Window title
    int width = 800;                     // Width of the window
    int height = 600;                    // Height of the window
    bool resizable = true;               // Allow resizing
    bool visible = true;                 // Start as visible
    bool decorated = false;               // Include borders and controls
    int contextVersionMajor = 4;         // OpenGL major version
    int contextVersionMinor = 5;         // OpenGL minor version
    bool coreProfile = true;             // Use core profile
};

class Window {
public:
    // Constructor takes a WindowConfig struct
    explicit Window(const WindowConfig& config);

    // Destructor handles cleanup
    ~Window();

    // Get the raw GLFWwindow pointer
    GLFWwindow* GetGLFWWindow() const;

    // Poll input events (if input handling is desired here)
    void PollEvents() const;

    // Getters for width and height
    int GetWidth() const;
    int GetHeight() const;



    // Check if the window should close
    bool ShouldClose() const;

    // Swap buffers
    void SwapBuffers() const;

private:

    GLFWwindow* glfwWindow;
    int width, height;
    std::string title;

    bool dragging = false;  // State to track whether we're dragging the window
    double xPosGlobal; // X Position of the mouse with respect to the screen
    double yPosGlobal; // Y Position of the mouse with respect to the screen
    double xPosLocal; // X Position of the mouse with respect to the window
    double yPosLocal; // Y Position of the mouse with respect to the window 
    double startx;
    double starty;
    // Set GLFW window hints based on the config
    void setWindowHints(const WindowConfig& config);

    void move(GLFWwindow* window, double xpos, double ypos); 
    
    void mouseSelector(GLFWwindow* window, int button, int action, int mods);

};



