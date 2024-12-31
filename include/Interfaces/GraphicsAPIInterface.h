#pragma once

// Base Interface for Graphics API
class IGraphicsAPI
{
public:
    virtual void Initialize() = 0;     // Initialize the graphics API
    virtual void CreateBuffer() = 0;   // Create GPU buffers
    virtual void Draw() = 0;           // Issue draw commands
    virtual void Shutdown() = 0;       // Clean up resources
    virtual ~IGraphicsAPI() = default; // Virtual destructor for polymorphism
};

// OpenGL Implementation of IGraphicsAPI
class OpenGLAPI : public IGraphicsAPI
{
public:
    void Initialize() override;   // OpenGL initialization
    void CreateBuffer() override; // OpenGL buffer creation
    void Draw() override;         // OpenGL draw commands
    void Shutdown() override;     // OpenGL cleanup
};

// Vulkan Implementation of IGraphicsAPI
class VulkanAPI : public IGraphicsAPI
{
public:
    void Initialize() override;   // Vulkan initialization
    void CreateBuffer() override; // Vulkan buffer creation
    void Draw() override;         // Vulkan draw commands
    void Shutdown() override;     // Vulkan cleanup
};
