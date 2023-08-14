#include "include/render/blit_pipeline.h"

namespace ToolEngine
{
	BlitPipeline::BlitPipeline(Device& device, VkFormat format): m_device(device)
	{
		m_pipeline_layout = std::make_unique<PipelineLayout>(m_device);
		m_render_pass = std::make_unique<RenderPass>(m_device, format);

        // vertex input
        VkPipelineVertexInputStateCreateInfo vertex_input_state{};
        vertex_input_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertex_input_state.vertexBindingDescriptionCount = 0;
        vertex_input_state.vertexAttributeDescriptionCount = 0;

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
        rasterization_state.frontFace = VK_FRONT_FACE_CLOCKWISE;
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

		m_state = std::make_unique<PipelineState>();
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
    BlitPipeline::~BlitPipeline()
    {
        
    }
}