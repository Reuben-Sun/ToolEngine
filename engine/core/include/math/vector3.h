#pragma once

//#include "vulkan/vulkan.h"

namespace ToolEngine
{
    class Vector3
    {   
    public:
        union
        {
            struct
            {
                float x;
                float y;
                float z;
            };
        };

        Vector3();
        Vector3(float x, float y, float z);
        ~Vector3();
    };
}