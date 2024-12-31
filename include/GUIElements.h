#pragma once

#include "imgui.h"
#include <iostream>
#include <fstream>
#include <sys/utsname.h> // For uname
#include <sys/sysinfo.h> // For memory info
#include "GL/glew.h"     // OpenGL and GLEW
#include "glm/glm.hpp"   // GLM library
#include "Mesh.h"

class Mesh;

void MainMenu(bool *);
void sidebarElement();
void ShowToolsAndUtilityWindows();
void ShowStatus(bool isRunning);

void ShowSystemInfo();
std::string GetOSInfo();
std::string GetCPUInfo();

void ShowColorPicker(ImVec4 &color);
void ShowOpenGLViewport();
void RenderImGui(Mesh &mesh); // Function prototype
