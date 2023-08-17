#include "client_framework.h"

namespace ToolEngine
{
    void ClientFramework::run()
    {
        Application app;
        app.init();
        app.mainLoop();
        app.cleanup();
    }
}