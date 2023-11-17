#include "include/common/macro.h"
export module BindingManager;

import Device;
import PhysicalDevice;
import DescriptorPool;
import RenderScene;
import Vertex;
import VertexBuffer;
import Index;
import IndexBuffer;
import <string>;
import <memory>;
import <unordered_map>;

namespace ToolEngine
{
	export class BindingManager
	{
	public:
		BindingManager(Device& device, PhysicalDevice& physical_device);
		~BindingManager();

		DescriptorPool& getDescriptorPool() 
		{
			return *m_descriptor_pool;
		}

		void preprocess(RenderScene& render_scene);
		VertexBuffer& getVertexBuffer(std::string model_name);
		IndexBuffer& getIndexBuffer(std::string model_name);
	private:
		Device& m_device;
		PhysicalDevice& m_physical_device;
		std::unique_ptr<DescriptorPool> m_descriptor_pool;
		std::unordered_map<std::string, std::unique_ptr<VertexBuffer>> model_name_to_vertex_buffer;
		std::unordered_map<std::string, std::unique_ptr<IndexBuffer>> model_name_to_index_buffer;
	};
	
}