#pragma once

#include <vulkan/vulkan.h>
#include "include/rhi/pipeline.h"
#include "include/rhi/device.h"
#include "include/rhi/shader_module.h"

namespace ToolEngine
{
	class GraphicsPipeline: public Pipeline
	{
	public:
		GraphicsPipeline(Device& device, PipelineState& pipeline_state);
		virtual ~GraphicsPipeline() = default;
	};
}