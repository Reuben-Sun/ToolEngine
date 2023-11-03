#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"
#include "vulkan/vulkan.h"
import DetailPanel;
import Device;
import SwapChain;
import Instance;
import PhysicalDevice;
import RenderPass;
import <vector>;
import <memory>;

namespace ToolEngine
{
    DetailPanel::DetailPanel(Device& device, Instance& instance, PhysicalDevice& physical_device, SwapChain& swap_chain, RenderPass& render_pass)
        : m_device(device), m_instance(instance), m_physical_device(physical_device), m_swap_chain(swap_chain), m_render_pass(render_pass)
    {
        //m_imgui_pass = std::make_unique<ImguiPass>(m_device, m_physical_device);
    }

    DetailPanel::~DetailPanel()
    {
    }

    void DetailPanel::init(uint32_t pass_index)
    {
        ImGui::CreateContext();
        ImGuiIO& io    = ImGui::GetIO();
        io.IniFilename = nullptr;  // Avoiding the INI file
        io.LogFilename = nullptr;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

        std::vector<VkDescriptorPoolSize> pool_size {{VK_DESCRIPTOR_TYPE_SAMPLER, 1}, {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1}};
        VkDescriptorPoolCreateInfo pool_info{VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO};
        pool_info.maxSets       = 1000;
        pool_info.poolSizeCount = 2;
        pool_info.pPoolSizes    = pool_size.data();
        vkCreateDescriptorPool(m_device.getHandle(), &pool_info, nullptr, &m_imgui_desc_pool);

        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance                  = m_instance.getHandle();
        init_info.PhysicalDevice = m_physical_device.getHandle();
        init_info.Device                    = m_device.getHandle();
        init_info.QueueFamily = m_device.getQueueFamilyIndices().graphics_family.value();
        init_info.Queue                     = m_device.getGraphicsQueue().getHandle();
        init_info.PipelineCache             = VK_NULL_HANDLE;
        init_info.DescriptorPool            = m_imgui_desc_pool;
        init_info.Subpass                   = pass_index;
        init_info.MinImageCount             = 2;
        init_info.ImageCount                = static_cast<int>(m_swap_chain.getImages().size());
        init_info.MSAASamples               = VK_SAMPLE_COUNT_1_BIT;  // <--- need argument?
        init_info.CheckVkResultFn           = nullptr;
        init_info.Allocator                 = nullptr;

        ImGui_ImplVulkan_Init(&init_info, m_render_pass.getHandle());
    }

    void DetailPanel::tick()
    {
    }
}