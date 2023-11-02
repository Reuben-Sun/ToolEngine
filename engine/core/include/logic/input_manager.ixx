export module InputManager;
import <queue>;
import <string>;
import <iostream>;

namespace ToolEngine
{
    export enum class CommandType
    {
        NONE = 0,
        MOVE = 1,
        CLICK = 2
    };
	export struct InputCommand
	{
        CommandType type;
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
		InputCommand pop();
	private:
		std::queue<InputCommand> m_input_command_buffer;
	};
}