#include "include/common/macro.h"
export module RenderScene;

import Model;
import RenderCamera;

namespace ToolEngine
{
	export struct RenderScene
	{
		std::vector<Model> models;
		RenderCamera render_camera;
	};
}