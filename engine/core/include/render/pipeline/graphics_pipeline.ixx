#include <vulkan/vulkan.h>
#include "include/rhi/pipeline.h"
#include "include/rhi/device.h"
#include "include/rhi/shader_module.h"

export module GraphicsPipeline;

namespace ToolEngine
{
	/// <summary>
	/// Pipeline don't own frame resources, but process them.
	/// Input resources, and output rendered resources.
	/// </summary>
	export class GraphicsPipeline: public Pipeline
	{
	public:
		GraphicsPipeline(Device& device, PipelineState pipeline_state);
		virtual ~GraphicsPipeline() = default;
	};
}