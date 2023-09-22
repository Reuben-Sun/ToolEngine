#include "include/rhi/shader_module.h"

namespace ToolEngine
{
	ShaderModule::ShaderModule(Device& device, std::string shader_path): m_device(device), m_shader_path(shader_path)
	{
		std::string final_shader_path = FileUtils::getInstance().getShaderPath() + shader_path;
		auto shader_code = FileUtils::getInstance().readFile(final_shader_path);

		VkShaderModuleCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		create_info.codeSize = shader_code.size();
		create_info.pCode = reinterpret_cast<const uint32_t*>(shader_code.data());

		if (vkCreateShaderModule(m_device.getHandle(), &create_info, nullptr, &m_shader_module) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create shader module!");
		}
	}

	ShaderModule::~ShaderModule()
	{
		if (m_shader_module != VK_NULL_HANDLE)
		{
			vkDestroyShaderModule(m_device.getHandle(), m_shader_module, nullptr);
		}
	}
}