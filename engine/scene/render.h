#include <stdexcept>
#include <vector>
#include "include/vulkan/vulkan.h"
#include "include/math/vector3.h"

namespace ToolEngine
{
    class Render
    {
    public:
        Render();
        ~Render();
        void createInstance(std::vector<const char*> requiredExtensions);
        void destroyInstance();
    private:
        VkInstance instance;

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

#ifdef NDEBUG
        const bool enableValidationLayers = false;
#else
        const bool enableValidationLayers = true;
#endif
        bool checkValidationLayerSupport();
    };
}