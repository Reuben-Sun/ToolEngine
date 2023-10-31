#include <vulkan/vulkan.h>
#include "device.h"

export module PipelineLayout;

namespace ToolEngine
{
	export class PipelineLayout
	{
	public:
		PipelineLayout(Device& device, const VkPipelineLayoutCreateInfo& create_info);
		~PipelineLayout();

		VkPipelineLayout getHandle() const { return m_pipeline_layout; }

	private:
		VkPipelineLayout m_pipeline_layout;
		Device& m_deivce;
	};
}