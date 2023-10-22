#pragma once

#include <vector>
#include "include/render/model/model.h"
#include "include/render/camera/render_camera.h"

namespace ToolEngine
{
	struct RenderScene
	{
		std::vector<Model> models;
		RenderCamera render_camera;
	};
}