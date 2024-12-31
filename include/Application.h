#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Component.h"
#include "Mesh.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GL/glew.h"
#include "GUIElements.h"
#include "Renderer.h"
#include <iostream>
#include <vector>

class Application
{
private:
    Window window;
    bool isRunning;
    std::vector<Mesh> meshCollection;
    OpenGLRenderer renderer;
    unsigned int shaderProgram;

public:
    Application(WindowConfig &config);
    void Run();    // Entry point to tell it to run the application
    void Stage();  // Stage all your items, setup, initialize, etc items should do this themselves and only be used here
    void Render(); // The main loop to allow rendering audio, input control
    void Cleanup();
};

#endif // APPLICATION_H
