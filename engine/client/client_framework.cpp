#include "client_framework.h"

namespace ToolEngine
{
    void ClientFramework::run(int argc, char* argv[])
    {
        Application app;
        app.init(argc, argv);
        app.mainLoop();
        app.cleanup();
    }
}