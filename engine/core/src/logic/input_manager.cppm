import InputManager;

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

    InputCommand InputManager::pop()
    {
        InputCommand current_command {
            CommandType::NONE,
            ""
        };
        if(!m_input_command_buffer.empty())
        {
            current_command = m_input_command_buffer.front();
            m_input_command_buffer.pop();
        }
        return current_command;
    }
}