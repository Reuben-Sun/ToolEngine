#include "include/render/blit_pipeline.h"

namespace ToolEngine
{
	BlitPipeline::BlitPipeline(Device& device, PhysicalDevice& physical_device, SwapChain& swap_chain, uint32_t frames_in_flight_count)
        : m_device(device), m_frames_in_flight_count(frames_in_flight_count), m_physical_device(physical_device), m_swap_chain(swap_chain)
	{
        // pipeline init
        m_descriptor_set_layout = std::make_unique<DescriptorSetLayout>(m_device);
        m_descriptor_pool = std::make_unique<DescriptorPool>(m_device, m_frames_in_flight_count);
        createPipeline();
        // resource init
        m_vertex_buffer = std::make_unique<VertexBuffer>(m_device, m_physical_device, VERTEX_BUFFER);
        m_index_buffer = std::make_unique<IndexBuffer>(m_device, m_physical_device, INDEX_BUFFER);
        m_uniform_buffers.resize(m_frames_in_flight_count);
        for (int i = 0; i < m_frames_in_flight_count; ++i)
        {
            m_uniform_buffers[i] = std::make_unique<UniformBuffer>(m_device, m_physical_device);
        }
        m_texture_image = std::make_unique<TextureImage>(m_device, m_physical_device, "\\textures\\CalibrationFloorDiffuse.png");
        m_texture_image_view = std::make_unique<ImageView>(m_device, m_texture_image->getHandle(), m_texture_image->getFormat());
        m_texture_sampler = std::make_unique<Sampler>(m_device, m_physical_device);
        // resource descriptor
        m_descriptor_sets = std::make_unique<DescriptorSets>(m_device, *m_descriptor_set_layout, *m_descriptor_pool, m_frames_in_flight_count);
        for (int i = 0; i < m_frames_in_flight_count; ++i)
        {
            m_descriptor_sets->updateDescriptorSets(m_uniform_buffers[i]->getHandle(), m_texture_image_view->getHandle(), m_texture_sampler->getHandle(), i);
        }
        
	}
    BlitPipeline::~BlitPipeline()
    {
        
    }
    void BlitPipeline::renderTick(CommandBuffer& command_buffer, FrameBuffer& frame_buffer, uint32_t frame_index)
    {
        command_buffer.beginRecord(frame_index);

        VkRenderPassBeginInfo render_pass_info{};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = m_render_pass->getHandle();
        render_pass_info.framebuffer = frame_buffer.getHandle();
        render_pass_info.renderArea.offset = { 0, 0 };
        render_pass_info.renderArea.extent = m_swap_chain.getExtent();
        VkClearValue clear_color = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
        render_pass_info.clearValueCount = 1;
        render_pass_info.pClearValues = &clear_color;
        command_buffer.beginRenderPass(frame_index, render_pass_info);

        command_buffer.bindPipeline(frame_index, m_pipeline->getHandle());

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)m_swap_chain.getExtent().width;
        viewport.height = (float)m_swap_chain.getExtent().height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        command_buffer.setViewport(frame_index, viewport, 0, 1);

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = m_swap_chain.getExtent();
        command_buffer.setScissor(frame_index, scissor, 0, 1);

        // pass vertex data
        VkBuffer vertex_buffers[] = { m_vertex_buffer->getHandle() };
        VkDeviceSize offsets[] = { 0 };
        uint32_t vertex_count = static_cast<uint32_t>(VERTEX_BUFFER.size());
        uint32_t index_count = static_cast<uint32_t>(INDEX_BUFFER.size());
        updateUniformBuffer(frame_index);
        OPTICK_TAG("VertexCount", vertex_count);
        command_buffer.bindVertexBuffer(frame_index, vertex_buffers, offsets, 0, 1);
        command_buffer.bindIndexBuffer(frame_index, m_index_buffer->getHandle(), 0, VK_INDEX_TYPE_UINT16);
        command_buffer.bindDescriptorSets(frame_index, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline_layout->getHandle(), m_descriptor_sets->getHandlePtr(frame_index), 0, 1);
        command_buffer.draw(frame_index, index_count, 1, 0, 0, 0);

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
        rasterization_state.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterization_state.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterization_state.depthBiasEnable = VK_FALSE;

        // multisampling
        VkPipelineMultisampleStateCreateInfo multi_sample_state{};
        multi_sample_state.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multi_sample_state.sampleShadingEnable = VK_FALSE;
        multi_sample_state.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

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
        m_render_pass = std::make_unique<RenderPass>(m_device, m_swap_chain.getFormat());

        m_state = std::make_unique<PipelineState>();
        m_state->setVertexShaderStage(vert_shader_stage_info);
        m_state->setFragmentShaderStage(frag_shader_stage_info);
        m_state->setPipelineLayout(*m_pipeline_layout);
        m_state->setRenderPass(*m_render_pass);
        m_state->setVertexInputState(vertex_input_state);
        m_state->setInputAssemblyState(input_assembly_state);
        m_state->setViewportState(viewport_state);
        m_state->setRasterizationState(rasterization_state);
        m_state->setMultisampleState(multi_sample_state);
        m_state->setColorBlendState(colorBlending);
        m_state->setDynamicState(dynamicState);
        m_state->setSubpassIndex(0);

        m_pipeline = std::make_unique<GraphicsPipeline>(m_device, *m_state);
    }

    void BlitPipeline::updateUniformBuffer(uint32_t current_image)
    {
        UniformBufferObject ubo{};
        //float time = Timer::CurrentTime();
        float time = 1;
        ubo.model_matrix = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.view_matrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.projection_matrix = glm::perspective(glm::radians(45.0f), m_swap_chain.getWidthDividedByHeight(), 0.1f, 10.0f);
        ubo.projection_matrix[1][1] *= -1;

        m_uniform_buffers[current_image]->bindingBuffer(ubo);
    }
}