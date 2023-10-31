#include <vulkan/vulkan.h>

export module IndexBuffer;

import Buffer;
import Index;
import PhysicalDevice;
import Device;
import <vector>;

namespace ToolEngine
{
	export class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(Device& device, PhysicalDevice& physical_device, std::vector<Index> index_buffer);
		virtual ~IndexBuffer();
		void updateBuffer(std::vector<Index> index_buffer);
		VkBuffer getHandle() const { return m_buffer; }
	private:
		VkBuffer m_buffer;
		VkDeviceMemory m_memory;
		void* m_index_buffer_mapped;
	};
}