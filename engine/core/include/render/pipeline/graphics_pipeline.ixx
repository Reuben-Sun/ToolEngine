#include "include/common/macro.h"

export module GraphicsPipeline;
import Pipeline;
import ShaderModule;
import Device;

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