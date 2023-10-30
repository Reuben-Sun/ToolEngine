#pragma once

#include <vector>

import Model;

import RenderCamera;

namespace ToolEngine
{
	struct RenderScene
	{
		std::vector<Model> models;
		RenderCamera render_camera;
	};
}