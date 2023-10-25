#include "include/math/transform.h"

namespace ToolEngine
{
	const Transform Transform::Identity = { glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f) };

	glm::mat4x4 Transform::getTranslationMatrix()
	{
		glm::mat4x4 matrix =
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0 ,1, 0,
			position.x, position.y, position.z, 1
		};
		return matrix;
	}
	
	glm::mat4x4 Transform::getScaleMatrix()
	{
		glm::mat4x4 matrix =
		{
			scale.x, 0, 0, 0,
			0, scale.y, 0, 0,
			0, 0, scale.z, 0,
			0, 0, 0, 1
		};
		return matrix;
	}

	glm::mat4x4 Transform::getRotationXMatrix()
	{
		glm::mat4x4 matrix =
		{
			1, 0, 0, 0,
			0, cos(rotation.x), sin(rotation.x), 0,
			0, -sin(rotation.x), cos(rotation.x), 0,
			0, 0, 0, 1
		};
		return matrix;
	}

	glm::mat4x4 Transform::getRotationYMatrix()
	{
		glm::mat4x4 matrix =
		{
			cos(rotation.y), 0, -sin(rotation.y), 0,
			0, 1, 0, 0,
			sin(rotation.y), 0, cos(rotation.y), 0,
			0, 0, 0, 1
		};
		return matrix;
	}

	glm::mat4x4 Transform::getRotationZMatrix()
	{
		glm::mat4x4 matrix =
		{
			cos(rotation.z), sin(rotation.z), 0, 0,
			-sin(rotation.z), cos(rotation.z), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1

		};
		return matrix;
	}

	glm::mat4x4 Transform::getRotationMatrix()
	{
		glm::mat4x4 matrix = getRotationYMatrix() * getRotationXMatrix() * getRotationZMatrix();
		return matrix;
	}

	glm::vec3 Transform::getForward()
	{
		glm::vec3 forward = 
		{
			sin(rotation.y),
			sin(rotation.x) * cos(rotation.z),
			cos(rotation.y)
		};
		return forward;
	}

	glm::vec3 Transform::getRight()
	{
		glm::vec3 forward = getForward();
		glm::vec3 right =
		{
			forward.z, forward.y, -forward.x
		};
		return right;
	}

	glm::vec3 Transform::getUp()
	{
		glm::vec3 up =
		{
			0, 1, 0
		};
		return up;
	}
}