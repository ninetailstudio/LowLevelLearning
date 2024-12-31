#include "Application.h"

Application::Application(WindowConfig &config) : window(config) { isRunning = true; }

void Application::Stage()
{
  std::cout << "Application Running" << std::endl;

  // Load Objects
  // Define vertices for a triangle
  std::vector<Mesh::Vertex> vertices = {
      {{0.0f, 0.5f, 0.0f}, // Position
       {},                 // Normal
       {},
       {},
       {},
       {0.0f, 0.0f, 1.0f, 1.0f}, // Texture Coordinate
       {},
       {}}, // Tangent, Bitangent, Color, Joint data (unused)

      {{-0.5f, -0.5f, 0.0f},
       {}, // Normal
       {},
       {},
       {},
       {0.0f, 1.0f, 0.0f, 1.0f}, // Texture Coordinate
       {},
       {}}, // Tangent, Bitangent, Color, Joint data (unused)

      {{0.5f, -0.5f, 0.0f},
       {}, // Normal
       {},
       {},
       {},
       {1.0f, 0.0f, 0.0f, 1.0}, // Color
       {},
       {}}}; // Tangent, Bitangent, Color, Joint data (unused)

  // Define indices for the triangle
  std::vector<uint32_t> indices = {0, 1, 2};

  // Create the mesh
  Mesh triangleMesh;
  triangleMesh.SetVertices(vertices);
  triangleMesh.SetIndices(indices);
  triangleMesh.SetName("TriangleMesh");

  std::vector<Mesh::Vertex> verticesSquare = {
      // Top-left corner
      {{-0.5f, 0.5f, 0.0f}, // Position
       {},                  // Normal
       {},
       {},
       {},
       {0.0f, 1.0f, 0.0f, 1.0f}, // Color
       {},
       {}},

      // Bottom-left corner
      {{-0.5f, -0.5f, 0.0f},
       {}, // Normal
       {},
       {},
       {},
       {1.0f, 0.0f, 0.0f, 1.0f}, // Color
       {},
       {}},

      // Bottom-right corner
      {{0.5f, -0.5f, 0.0f},
       {}, // Normal
       {},
       {},
       {},
       {0.0f, 0.0f, 1.0f, 1.0f}, // Color
       {},
       {}},

      // Top-right corner
      {{0.5f, 0.5f, 0.0f},
       {}, // Normal
       {},
       {},
       {},
       {1.0f, 1.0f, 0.0f, 1.0f}, // Color
       {},
       {}}};
  std::vector<uint32_t> indicesSquare = {
      0, 1, 2, // First triangle (Top-left, Bottom-left, Bottom-right)
      2, 3, 0  // Second triangle (Bottom-right, Top-right, Top-left)
  };

  Mesh squareMesh;
  squareMesh.SetVertices(verticesSquare);
  squareMesh.SetIndices(indicesSquare);
  squareMesh.SetName("SquareMesh");

  // Shader source code (local to this file)
  // std::string vShaderSource = R"(

  //     #version 330 core
  //     layout(location = 0) in vec3 aPos;

  //     void main()
  //     {
  //       gl_Position = vec4(aPos, 1.0);
  //     }

  // )";
  // std::string fShaderSource = R"(
  //     #version 330 core
  //     out vec4 FragColor;

  //     void main() {
  //         FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Green color
  //     }
  // )";

  std::string vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 5) in vec4 aColor;
    out vec4 vertexColor;

    void main() {
        gl_Position = vec4(aPos, 1.0);
        vertexColor = aColor;
    }
)";

  std::string fragmentShaderSource = R"(
    #version 330 core
    in vec4 vertexColor;
    out vec4 FragColor;

    void main() {
        FragColor = vec4(vertexColor);
    }
)";

  Shader shaders;
  shaders.addShaderSource(ShaderTypes::Vertex, vertexShaderSource);
  shaders.addShaderSource(ShaderTypes::Fragment, fragmentShaderSource);

  // Send shaders to renderer
  //  shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
  renderer.CompileAndLinkShader(shaders);
  renderer.Enqueue(triangleMesh);
  renderer.Enqueue(squareMesh);
  meshCollection.push_back(triangleMesh);
  meshCollection.push_back(squareMesh);

  // Initialize ImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window.GetGLFWWindow(), true);
  ImGui_ImplOpenGL3_Init("#version 130");
}

void Application::Render()
{
  // Poll events
  glfwPollEvents();

  // Clear screen
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear depth buffer too
  renderer.Render();

  for (unsigned int i = 0; i < meshCollection.size(); i++)
  {
    renderer.Enqueue(meshCollection[i]);
  }

  // Start ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  RenderImGui(meshCollection[0]);

  // Render your UI
  MainMenu(&isRunning);
  sidebarElement();
  ShowSystemInfo();

  // Render ImGui
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Re-enable depth testing (if required for subsequent OpenGL rendering)
  glEnable(GL_DEPTH_TEST);

  // Swap buffers
  glfwSwapBuffers(window.GetGLFWWindow());
}

void Application::Cleanup()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void Application::Run()
{
  Stage();
  while (isRunning)
  {
    Render();
  }
  Cleanup();
}