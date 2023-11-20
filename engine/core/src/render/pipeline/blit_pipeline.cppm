#include "include/common/macro.h"
import BlitPipeline;
import RenderScene;
import Model;
import DescriptorPool;
import DescriptorSetLayout;
import UniformBuffer;
import ImageView;
import TextureImage;
import SwapChain;
import Sampler;
import ShaderModule;
import Device;
import Vertex;
import Global_Context;
import BindingManager;

namespace ToolEngine
{
	BlitPipeline::BlitPipeline(Device& device, PhysicalDevice& physical_device, SwapChain& swap_chain, uint32_t frames_in_flight_count)
        : m_device(device), m_frames_in_flight_count(frames_in_flight_count), m_physical_device(physical_device), m_swap_chain(swap_chain)
	{
        // pipeline init
        m_descriptor_set_layout = std::make_unique<DescriptorSetLayout>(m_device);
        createPipeline();

        m_uniform_buffer = std::make_unique<UniformBuffer>(m_device, m_physical_device);

        m_texture_image = std::make_unique<TextureImage>(m_device, m_physical_device, "CalibrationFloorDiffuse.png");
        
        m_descriptor_sets = std::make_unique<DescriptorSet>(m_device, *m_descriptor_set_layout, g_global_context.m_binding_manager->getDescriptorPool());
        for (int i = 0; i < m_frames_in_flight_count; ++i)
        {
            m_descriptor_sets->updateDescriptorSets(*m_uniform_buffer, *m_texture_image);
        }
        
	}
    BlitPipeline::~BlitPipeline()
    {
        
    }
    void BlitPipeline::renderTick(CommandBuffer& command_buffer, FrameBuffer& frame_buffer, uint32_t frame_index, RenderScene& render_scene)
    {
        command_buffer.beginRecord(frame_index);

        command_buffer.beginRenderPass(frame_index, *m_forward_pass, frame_buffer, m_swap_chain.getExtent());

        command_buffer.bindPipeline(frame_index, m_pipeline->getHandle());

        command_buffer.setViewport(frame_index, m_swap_chain.getExtent(), 0.0f, 1.0f, 0, 1);

        command_buffer.setScissor(frame_index, m_swap_chain.getExtent(), 0, 1);

        uint32_t vertex_buffer_count = render_scene.models.size();
        for(int i = 0; i < vertex_buffer_count; i++)
        {
            Model& model = render_scene.models[i];
            VertexBuffer& vertex_buffer = g_global_context.m_binding_manager->getVertexBuffer(model.name);
            IndexBuffer& index_buffer = g_global_context.m_binding_manager->getIndexBuffer(model.name);
            
            VkDeviceSize offsets[] = { 0 };
            uint32_t index_count = static_cast<uint32_t>(model.indices.size());
            updateUniformBuffer(render_scene, i);
            command_buffer.bindVertexBuffer(frame_index, vertex_buffer, offsets, 0, 1);
            command_buffer.bindIndexBuffer(frame_index, index_buffer, 0, VK_INDEX_TYPE_UINT16);
            // TODO: each draw call have a descriptor sets
            command_buffer.bindDescriptorSets(frame_index, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline_layout->getHandle(), m_descriptor_sets->getHandlePtr(), 0, 1);
            command_buffer.draw(frame_index, index_count, 1, 0, 0, 0);
        }

        command_buffer.endRenderPass(frame_index);

        command_buffer.endRecord(frame_index);
    }
    void BlitPipeline::createPipeline()
    {
        // shader
        ShaderModule vertex_shader_module(m_device, "vert.spv");
        ShaderModule fragment_shader_module(m_device, "frag.spv");

        VkPipelineShaderStageCreateInfo vert_shader_stage_info{};
        vert_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vert_shader_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vert_shader_stage_info.module = vertex_shader_module.getHandle();
        vert_shader_stage_info.pName = "main";
        VkPipelineShaderStageCreateInfo frag_shader_stage_info{};
        frag_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        frag_shader_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        frag_shader_stage_info.module = fragment_shader_module.getHandle();
        frag_shader_stage_info.pName = "main";

        // vertex input
        auto vertex_binding_description = Vertex::getBindingDescription();
        auto vertex_attribute_descriptions = Vertex::getAttributeDescriptions();
        VkPipelineVertexInputStateCreateInfo vertex_input_state{};
        vertex_input_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertex_input_state.vertexBindingDescriptionCount = 1;
        vertex_input_state.pVertexBindingDescriptions = &vertex_binding_description;
        vertex_input_state.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertex_attribute_descriptions.size());
        vertex_input_state.pVertexAttributeDescriptions = vertex_attribute_descriptions.data();

        // input assembly
        VkPipelineInputAssemblyStateCreateInfo input_assembly_state{};
        input_assembly_state.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        input_assembly_state.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        input_assembly_state.primitiveRestartEnable = VK_FALSE;

        // viewport and scissors
        VkPipelineViewportStateCreateInfo viewport_state{};
        viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewport_state.viewportCount = 1;
        viewport_state.scissorCount = 1;

        // rasterizer
        VkPipelineRasterizationStateCreateInfo rasterization_state{};
        rasterization_state.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterization_state.depthClampEnable = VK_FALSE;
        rasterization_state.rasterizerDiscardEnable = VK_FALSE;
        rasterization_state.polygonMode = VK_POLYGON_MODE_FILL;
        rasterization_state.lineWidth = 1.0f;
        rasterization_state.cullMode = VK_CULL_MODE_NONE;
        rasterization_state.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterization_state.depthBiasEnable = VK_FALSE;

        // multisampling
        VkPipelineMultisampleStateCreateInfo multi_sample_state{};
        multi_sample_state.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multi_sample_state.sampleShadingEnable = VK_FALSE;
        multi_sample_state.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        // depth stencil
        VkPipelineDepthStencilStateCreateInfo depth_stencil_state{};
        depth_stencil_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depth_stencil_state.depthTestEnable = VK_TRUE;
        depth_stencil_state.depthWriteEnable = VK_TRUE;
        depth_stencil_state.depthCompareOp = VK_COMPARE_OP_LESS;
        depth_stencil_state.depthBoundsTestEnable = VK_FALSE;
        depth_stencil_state.minDepthBounds = 0.0f; // Optional
        depth_stencil_state.maxDepthBounds = 1.0f; // Optional
        depth_stencil_state.stencilTestEnable = VK_FALSE;
        depth_stencil_state.front = {}; // Optional
        depth_stencil_state.back = {}; // Optional

        // color blending
        VkPipelineColorBlendAttachmentState color_blend_attachment_state{};
        color_blend_attachment_state.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        color_blend_attachment_state.blendEnable = VK_FALSE;
        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &color_blend_attachment_state;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        // dynamic state
        std::vector<VkDynamicState> dynamicStates = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };
        VkPipelineDynamicStateCreateInfo dynamicState{};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
        dynamicState.pDynamicStates = dynamicStates.data();

        VkPipelineLayoutCreateInfo pipeline_layout_info{};
        pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipeline_layout_info.setLayoutCount = 1;
        pipeline_layout_info.pSetLayouts = m_descriptor_set_layout->getHandlePtr();

        m_pipeline_layout = std::make_unique<PipelineLayout>(m_device, pipeline_layout_info);
        m_forward_pass = std::make_unique<ForwardPass>(m_device, m_physical_device, m_swap_chain.getFormat());

        m_state.m_vertex_shader_stage = vert_shader_stage_info;
        m_state.m_fragment_shader_stage = frag_shader_stage_info;
        m_state.m_pipeline_layout = m_pipeline_layout->getHandle();
        m_state.m_render_pass = m_forward_pass->getHandle();
		m_state.m_vertex_input_state = vertex_input_state;
        m_state.m_input_assembly_state = input_assembly_state;
        m_state.m_viewport_state = viewport_state;
        m_state.m_rasterization_state = rasterization_state;
        m_state.m_multisample_state = multi_sample_state;
        m_state.m_depth_stencil_state = depth_stencil_state;
        m_state.m_color_blend_state = colorBlending;
        m_state.m_dynamic_state = dynamicState;
        m_state.m_subpass_index = 0;

        m_pipeline = std::make_unique<GraphicsPipeline>(m_device, m_state);
    }

    void BlitPipeline::updateUniformBuffer(RenderScene& render_scene, uint32_t model_index)
    {
        UniformBufferObject ubo{};
        ubo.model_matrix = render_scene.models[model_index].transform.getModelMatrix();
        ubo.view_matrix = render_scene.render_camera.getViewMatrix();
        ubo.projection_matrix = render_scene.render_camera.getProjectionMatrix();
        m_uniform_buffer->updateBuffer(ubo);
    }
}