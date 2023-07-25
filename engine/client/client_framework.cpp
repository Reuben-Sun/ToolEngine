#include "client_framework.h"

namespace ToolEngine
{
    void ClientFramework::run()
    {
        SceneView view;
        view.viewInit();
        view.vulkanInit();
        view.run();
        view.cleanup();
    }
}