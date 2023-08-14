#include "client_framework.h"

namespace ToolEngine
{
    void ClientFramework::run()
    {
        /*SceneView view;
        view.viewInit();
        view.vulkanInit();
        view.mainLoop();
        view.cleanup();*/
        Application app;
        app.mainLoop();
    }
}