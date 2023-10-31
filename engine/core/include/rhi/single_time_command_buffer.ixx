#include <vulkan/vulkan.h>
#include "device.h"

export module SingleTimeCommandBuffer;

namespace ToolEngine
{
	/// <summary>
	/// A buffer to execute a one-time command, such as submit texture.
	/// This buffer is design for std::unique_ptr, needn't free or submit
	/// </summary>
	export class SingleTimeCommandBuffer
	{
	public:
		SingleTimeCommandBuffer(Device& device);
		~SingleTimeCommandBuffer();

		VkCommandBuffer getHandle() const { return m_command_buffer; }

	private:
		Device& m_device;
		VkCommandBuffer m_command_buffer;
	};
}