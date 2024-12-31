#include <iosteam>
#include <memory>

// Base Interface for Renderers
class IRenderer
{
public:
    virtual void Initialize() = 0;  // Initialize the renderer
    virtual void RenderFrame() = 0; // Render a frame
    virtual void Shutdown() = 0;    // Clean up renderer resources
    virtual ~IRenderer() = default; // Virtual destructor for polymorphism
};
