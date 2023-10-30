#pragma once

#include <string>
#include <vulkan/vulkan.h>
#include "device.h"

import Global_Context;

namespace ToolEngine
{
	class ShaderModule
	{
	public:
		ShaderModule(Device& device, std::string shader_path);
		~ShaderModule();

		VkShaderModule getHandle() const { return m_shader_module; }
	private:
		VkShaderModule m_shader_module;
		std::string m_shader_path;
		Device& m_device;

		// TODO: ShaderVariant
	};
}