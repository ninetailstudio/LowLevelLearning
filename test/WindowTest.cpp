#include "../include/Window.h"
#include <iostream>



int main() {
    try {

        // Define a test configuration for the window
        WindowConfig testConfig = {
            "Test Window",  // Title
            800, 600,       // Width, Height
            true,           // Resizable
            true,           // Visible
            false,          // Decorated
            4, 5,           // OpenGL Version
            true,           // Core profile
        };

        // Create the window object
        Window testWindow(testConfig);

        // Set up callbacks for dragging
        // glfwSetMouseButtonCallback(testWindow.GetGLFWWindow(), titleBarSelector);
        // glfwSetCursorPosCallback(testWindow.GetGLFWWindow(), move);

        // Main loop for testing
        while (!testWindow.ShouldClose()) {
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Swap buffers and poll events
            testWindow.SwapBuffers();
            testWindow.PollEvents();
        }

        std::cout << "Window test passed successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Window test failed: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
