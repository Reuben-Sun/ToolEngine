#include "include/common/macro.h"

export module Index;

namespace ToolEngine
{
	/// <summary>
	/// The indices are arranged in a triangle list
	/// </summary>
	export struct Index
	{
		uint16_t index;
	};
}