#include "include/common/macro.h"

export module Sampler;
import PhysicalDevice;
import Device;

namespace ToolEngine
{
	export class Sampler
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