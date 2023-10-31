#include <vulkan/vulkan.h>
#include "device.h"

export module UniformBuffer;

import Buffer;
import PhysicalDevice;
import <glm/glm.hpp>;

namespace ToolEngine
{
	export struct UniformBufferObject
	{
		glm::mat4 model_matrix;
		glm::mat4 view_matrix;
		glm::mat4 projection_matrix;
	};

	export class UniformBuffer: public Buffer
	{
	public:
		UniformBuffer(Device& device, PhysicalDevice& physical_device);
		virtual ~UniformBuffer();
		void updateBuffer(UniformBufferObject ubo);
		VkBuffer getHandle() const { return m_buffer; }
	private:
		VkBuffer m_buffer;
		VkDeviceMemory m_memory;
		void* m_uniform_buffer_mapped;
	};
}