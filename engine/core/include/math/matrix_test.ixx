export module student;

import <string>;
import <iostream>;

namespace ToolEngine
{
	export class Student
	{
	public:
		Student();
		~Student();
		void display();
	private:
		std::string name;
	};
}