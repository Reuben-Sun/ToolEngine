#include "include/logic/input_manager.h"

namespace ToolEngine
{
	InputManager::InputManager()
	{
	}
	InputManager::~InputManager()
	{
		while (!m_input_command_buffer.empty())
		{
			m_input_command_buffer.pop();
		}
	}

	void InputManager::push(InputCommand input_command)
	{
		m_input_command_buffer.push(input_command);
	}
	void InputManager::tick()
	{
		if (!m_input_command_buffer.empty())
		{
			InputCommand current_command = m_input_command_buffer.front();
			m_input_command_buffer.pop();
		}
	}
}