export module InputManager;
import <queue>;
import <string>;
import <iostream>;

namespace ToolEngine
{
	export struct InputCommand
	{
		int type;
		std::string detail;
	};
	/// <summary>
	/// There is a buffer to store input command.
	/// TODO: thread safe
	/// </summary>
	export class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void push(InputCommand input_command);
		void tick();
	private:
		std::queue<InputCommand> m_input_command_buffer;
	};
}