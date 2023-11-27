#include "include/common/macro.h"

export module UniformBuffer;

import Buffer;
import PhysicalDevice;
import Device;

namespace ToolEngine
{
	export struct GlobalUniformBufferObject
	{
		glm::mat4 model_matrix;		// TODO: move to per mesh ubo
		glm::mat4 view_matrix;
		glm::mat4 projection_matrix;
	};

	export struct PerMeshUniformBufferObject
	{
		glm::mat4 model_matrix;
	};

	export enum class UniformBufferType
	{
		Global,
		PerMesh
	};

	export class UniformBuffer: public Buffer
	{
	public:
		UniformBuffer(Device& device, PhysicalDevice& physical_device, UniformBufferType ubo_type);
		virtual ~UniformBuffer();
		void updateBuffer(const void* ubo);
		VkBuffer getHandle() const { return m_buffer; }
		VkDescriptorBufferInfo* getDescriptor()
		{
			return &m_descriptor;
		};
		uint32_t getAlignmentSize();
	private:
		VkBuffer m_buffer;
		VkDeviceMemory m_memory;
		void* m_uniform_buffer_mapped;
		VkDescriptorBufferInfo m_descriptor;
		UniformBufferType m_ubo_type;
		VkDeviceSize m_ubo_size;
	};
}