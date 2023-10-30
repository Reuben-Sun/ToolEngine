#pragma once

#include <vector>
#include "include/render/model/model.h"

import RenderCamera;

namespace ToolEngine
{
	struct RenderScene
	{
		std::vector<Model> models;
		RenderCamera render_camera;
	};
}