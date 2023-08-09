#pragma once

#include <vulkan/vulkan.h>
#include "device.h"

namespace ToolEngine
{
	class Queue
	{
	public:
		Queue(VkDevice& device, uint32_t family_index, VkBool32 can_present, uint32_t index);
		Queue(const Queue&) = default;
		~Queue();
		
		VkQueue getHandle() const { return m_queue; }

		// submit

		// is presentable

		// present

		// wait idle
		
	private:
		VkQueue m_queue{ VK_NULL_HANDLE };
		VkDevice& m_device;

		uint32_t m_family_index{ 0 };
		uint32_t m_index{ 0 };
		VkBool32 m_can_present{ VK_FALSE };
		//VkQueueFamilyProperties m_properties{};
		
	};
}