#include "GUIElements.h"
void MainMenu(bool *runningState)
{

    // Menu Bar
    if (ImGui::BeginMainMenuBar()) // Begin the menu bar
    {
        // Left-aligned title
        ImGui::Text("Application Builder");

        ImGuiStyle &style = ImGui::GetStyle();

        // Adjust the vertical padding to set the menu bar height
        style.FramePadding.y = 20.0f; // Increase for a taller menu bar

        // Dynamically align buttons to the right
        float menuBarWidth = ImGui::GetWindowWidth();
        float buttonWidth = 80.0f; // Approximate button width
        float spacing = 10.0f;     // Space between buttons

        // ImGui Menu
        if (ImGui::BeginMenu("File"))
        {
            ImGui::Button("Open File");
            ImGui::MenuItem("Save");
            ImGui::MenuItem("Save As");
            ImGui::EndMenu();
        }

        // Calculate starting position for the buttons
        float startX = menuBarWidth - (buttonWidth * 3 + spacing * 2);
        ImGui::SameLine(startX);
        // Minimize button
        if (ImGui::Button("Minimize", ImVec2(buttonWidth, 0)))
        {
            // std::cout << "Minimize clicked" << std::endl;
        }

        ImGui::SameLine();
        // Maximize button
        if (ImGui::Button("Maximize", ImVec2(buttonWidth, 0)))
        {
            // std::cout << "Maximize clicked" << std::endl;
        }

        ImGui::SameLine();
        // Close button
        if (ImGui::Button("Close", ImVec2(buttonWidth, 0)))
        {
            // std::cout << "Close clicked" << std::endl;
            // glfwSetWindowShouldClose(window.GetGLFWWindow(), true); // Close the GLFW window
            *runningState = false;
        }

        ImGui::EndMainMenuBar(); // End the menu bar
    }
}
void sidebarElement()
{
    // Set sidebar width and position
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 300, 52));        // Top-left corner
    ImGui::SetNextWindowSize(ImVec2(400, (ImGui::GetIO().DisplaySize.y / 2) - 52)); // Fixed width, full height

    // Create the window
    ImGui::Begin("Sidebar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    // Add content to the sidebar
    if (ImGui::Button("Button 1"))
    { /* Do something */
    }
    if (ImGui::Button("Button 2"))
    { /* Do something else */
    }
    ImGui::Text("Sidebar Content");

    ImGui::End();
}

void ShowToolsAndUtilityWindows()
{
    // Console Logger
    static ImGuiTextBuffer buffer;
    ImGui::Begin("Console");
    if (ImGui::Button("Clear"))
        buffer.clear();
    ImGui::TextUnformatted(buffer.begin());
    ImGui::End();

    // Settings Panel
    static int resolution = 0; // 0: Low, 1: Medium, 2: High
    static float volume = 0.5f;
    ImGui::Begin("Settings");
    ImGui::Text("Graphics Settings");
    ImGui::Combo("Resolution", &resolution, "Low\0Medium\0High\0");
    ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f, "%.1f");
    ImGui::End();
}

void ShowStatus(bool isRunning)
{
    ImGui::Begin("Application Status");
    ImGui::Text("isRunning = %s", isRunning ? "True" : "False"); // Display bool
    ImGui::End();
}

// Helper function to read /proc/cpuinfo
std::string GetCPUInfo()
{
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line, modelName;
    while (std::getline(cpuinfo, line))
    {
        if (line.find("model name") != std::string::npos)
        {
            modelName = line.substr(line.find(":") + 2); // Skip "model name : "
            break;
        }
    }
    return modelName;
}

// Helper function to read /etc/os-release
std::string GetOSInfo()
{
    std::ifstream osrelease("/etc/os-release");
    std::string line, osName;
    while (std::getline(osrelease, line))
    {
        if (line.find("PRETTY_NAME") != std::string::npos)
        {
            osName = line.substr(line.find("=") + 2); // Skip "PRETTY_NAME="
            osName.pop_back();                        // Remove trailing "
            break;
        }
    }
    return osName;
}

// Display system info in ImGui
void ShowSystemInfo()
{
    // OS Info
    struct utsname unameData;
    uname(&unameData);

    // Memory Info
    struct sysinfo sysInfo;
    sysinfo(&sysInfo);
    long totalRam = sysInfo.totalram / (1024 * 1024); // Convert to MB

    // GPU Info
    const char *gpuRenderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    const char *gpuVendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
    const char *gpuVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));

    // CPU Info
    std::string cpuModel = GetCPUInfo();
    std::string osName = GetOSInfo();

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 500, (ImGui::GetIO().DisplaySize.y) - 500)); // Top-left corner
    ImGui::SetNextWindowSize(ImVec2(500, (ImGui::GetIO().DisplaySize.y / 2) - 52));                            // Fixed width, full height
    // Display in ImGui
    ImGui::Begin("System Info");

    // Operating System
    ImGui::Text("OS: %s", osName.c_str());
    ImGui::Text("Kernel: %s", unameData.release);

    // Memory
    ImGui::Text("Total RAM: %ld MB", totalRam);

    // CPU
    ImGui::Text("CPU: %s", cpuModel.c_str());

    // GPU
    ImGui::Text("GPU Vendor: %s", gpuVendor ? gpuVendor : "Unknown");
    ImGui::Text("GPU Renderer: %s", gpuRenderer ? gpuRenderer : "Unknown");
    ImGui::Text("OpenGL Version: %s", gpuVersion ? gpuVersion : "Unknown");
    ImGui::Text("OpenGL Running Version: %s", glGetString(GL_VERSION));

    ImGui::End();
}

void ShowColorPicker(ImVec4 &color)
{
    ImGui::Begin("Color Picker");
    ImGui::ColorEdit4("Pick Color", (float *)&color);
    ImGui::End();
}
void RenderImGui(Mesh &mesh)
{
    auto &vertices = mesh.GetVertexData(); // Access vertices via Mesh's public API

    ImGui::Begin("Vertex Manipulator");

    for (size_t i = 0; i < vertices.size(); i++)
    {
        auto &vertex = vertices[i]; // Access vertex by reference

        ImGui::Text("Vertex %zu", i);

        // Editable position
        if (ImGui::DragFloat3(("Position##" + std::to_string(i)).c_str(), &vertex.position.x, 0.01f))
        {
            std::cout << "Updated Position: "
                      << vertex.position.x << ", "
                      << vertex.position.y << ", "
                      << vertex.position.z << std::endl;
        }

        // Editable normal
        if (ImGui::DragFloat3(("Normal##" + std::to_string(i)).c_str(), &vertex.normal.x, 0.01f))
        {
            vertex.normal = glm::normalize(vertex.normal); // Normalize after editing
        }

        // Editable color
        if (ImGui::ColorEdit4(("Color##" + std::to_string(i)).c_str(), &vertex.color.r))
        {
            std::cout << "Updated Color: "
                      << vertex.color.r << ", "
                      << vertex.color.g << ", "
                      << vertex.color.b << ", "
                      << vertex.color.a << std::endl;
        }

        ImGui::Separator(); // Optional: Add a visual separator between vertices
    }
    ImGui::End();
}
