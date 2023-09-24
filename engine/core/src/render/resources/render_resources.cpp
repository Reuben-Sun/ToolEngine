#include "include/render/resources/render_resources.h"

namespace ToolEngine
{
	RenderResources::RenderResources(Device& device, PhysicalDevice& physical_device)
		: m_device(device), m_physical_device(physical_device)
	{
	}
	RenderResources::~RenderResources()
	{
	}
}
