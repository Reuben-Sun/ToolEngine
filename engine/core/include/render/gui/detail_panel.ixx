#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"
#include "vulkan/vulkan.h"
export module DetailPanel;
import Device;
import Instance;
import PhysicalDevice;
import SwapChain;
import RenderPass;
import ImguiPass;
import <memory>;

namespace ToolEngine
{
    export class DetailPanel
    {
    public:
        DetailPanel(Device& device, Instance& instance, PhysicalDevice& physical_device, SwapChain& swap_chain, RenderPass& render_pass);
        ~DetailPanel();

        void init(uint32_t pass_index);
        void tick();
    private:
        Device& m_device;
        Instance& m_instance;
        PhysicalDevice& m_physical_device;
        SwapChain& m_swap_chain;
        RenderPass& m_render_pass;
        VkDescriptorPool m_imgui_desc_pool;
        std::unique_ptr<ImguiPass> m_imgui_pass;
    };
}