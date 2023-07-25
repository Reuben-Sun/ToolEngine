#pragma once

#include "scene_view.h"

namespace ToolEngine
{
    class ClientFramework
    {
    public:
        ClientFramework();
        ~ClientFramework();

        void onInit();
        void onStart();
        void onTick();
        void onExit();
        void onDestroy();
    };
}