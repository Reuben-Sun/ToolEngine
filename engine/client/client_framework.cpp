#include "client_framework.h"

namespace ToolEngine
{
    void ClientFramework::run()
    {
        SceneView view;
        view.init();
        view.run();
        view.cleanup();
    }
}