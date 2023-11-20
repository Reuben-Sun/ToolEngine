#include "include/common/macro.h"
import BindingManager;
import Device;
import DescriptorPool;
import RenderScene;
import Model;
import PhysicalDevice;
import UniformBuffer;

namespace ToolEngine
{
	BindingManager::BindingManager(Device& device, PhysicalDevice& physical_device)
		: m_device(device), m_physical_device(physical_device)
	{
		m_descriptor_pool = std::make_unique<DescriptorPool>(m_device);
	}

	BindingManager::~BindingManager()
	{
		model_name_to_index_buffer.clear();
		model_name_to_vertex_buffer.clear();
	}

	void BindingManager::preprocess(RenderScene& render_scene)
	{
		for (auto& model : render_scene.models)
		{
			if (model_name_to_index_buffer.find(model.name) == model_name_to_index_buffer.end())
			{
				model_name_to_index_buffer.emplace(model.name, std::make_unique<IndexBuffer>(m_device, m_physical_device, model.indices));
				model_name_to_vertex_buffer.emplace(model.name, std::make_unique<VertexBuffer>(m_device, m_physical_device, model.vertices));
			}
		}
	}

	VertexBuffer& BindingManager::getVertexBuffer(std::string model_name)
	{
		auto it = model_name_to_vertex_buffer.find(model_name);
		VertexBuffer& vertex_buffer_ref = *(it->second.get());
		return vertex_buffer_ref;
	}

	IndexBuffer& BindingManager::getIndexBuffer(std::string model_name)
	{
		auto it = model_name_to_index_buffer.find(model_name);
		IndexBuffer& index_buffer_ref = *(it->second.get());
		return index_buffer_ref;
	}

}