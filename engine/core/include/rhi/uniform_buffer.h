#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include "device.h"
#include "physical_device.h"
#include "buffer.h"

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
		void bindingBuffer(UniformBufferObject ubo);
	private:
		void* m_uniform_buffer_mapped;
	};
}