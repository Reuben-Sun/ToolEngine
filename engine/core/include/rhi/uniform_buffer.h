#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include "device.h"
#include "physical_device.h"

import Buffer;

namespace ToolEngine
{
	struct UniformBufferObject
	{
		glm::mat4 model_matrix;
		glm::mat4 view_matrix;
		glm::mat4 projection_matrix;
	};

	class UniformBuffer: public Buffer
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