#pragma once

#include <glm/glm.hpp>

namespace ToolEngine
{
	struct RenderCamera
	{
		float aspect;
		float view_size;
		float near_plane;
		float far_plane;
		float fov;
		glm::mat4x4 projection_matrix;
		glm::mat4x4 view_matrix;
	};
}