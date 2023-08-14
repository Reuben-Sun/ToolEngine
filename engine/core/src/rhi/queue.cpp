#include "include/rhi/queue.h"

namespace ToolEngine
{
	Queue::Queue(VkDevice& device, uint32_t family_index, VkBool32 can_present, uint32_t index): 
		m_device(device), m_family_index(family_index), m_can_present(can_present), m_index(index)
	{
		vkGetDeviceQueue(m_device, m_family_index, m_index, &m_queue);
	}
	Queue::~Queue()
	{
		
	}
}