
#include "Application.h"
#include "Window.h"

int main()
{

  WindowConfig windowConfig = {
      "Test Window", // Title
      2560, 1440,    // Width, Height
      true,          // Resizable
      true,          // Visible
      false,         // Decorated
      4, 5,          // OpenGL Version
      true,          // Core profile
  };

  Application app(windowConfig);
  app.Run();

  return 0;
}
