#include "include/math/vector3.h"

namespace ToolEngine
{
    Vector3::Vector3()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    Vector3::Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    Vector3::~Vector3()
    {
    }
}