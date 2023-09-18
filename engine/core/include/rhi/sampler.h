#pragma once

#include <vulkan/vulkan.h>
#include "device.h"
#include "physical_device.h"

namespace ToolEngine
{
	class Sampler
	{
	public:
		Sampler(Device& device, PhysicalDevice& physical_device);
		~Sampler();

		VkSampler getHandle() const { return m_sampler; }
	private:
		VkSampler m_sampler;
		Device& m_device;
		PhysicalDevice& m_physical_device;
	};
}