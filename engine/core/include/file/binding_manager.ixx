#include <vulkan/vulkan.h>
export module BindingManager;

import Device;
import DescriptorPool;
import <string>;
import <memory>;

namespace ToolEngine
{
	export class BindingManager
	{
	public:
		BindingManager(Device& device);
		~BindingManager();

		DescriptorPool& getDescriptorPool() 
		{
			return *m_descriptor_pool;
		}
	private:
		Device& m_device;
		std::unique_ptr<DescriptorPool> m_descriptor_pool;
	};
	
}