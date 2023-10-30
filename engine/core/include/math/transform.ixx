#include <glm/glm.hpp>

export module Transform;

namespace ToolEngine
{
	/// <summary>
	///	Y axis is up, Z axis is forward.
	/// Calculate rotation matrix by order: Y -> X -> Z.
	/// Calculate position translate in order of: scale -> rotation -> position.
	/// </summary>
	export struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;		// radian
		glm::vec3 scale;

		static const Transform Identity;

		glm::mat4x4 getTranslationMatrix();
		glm::mat4x4 getScaleMatrix();
		glm::mat4x4 getRotationXMatrix();
		glm::mat4x4 getRotationYMatrix();
		glm::mat4x4 getRotationZMatrix();
		glm::mat4x4 getRotationMatrix();

		glm::vec3 getForward();
		glm::vec3 getRight();
		glm::vec3 getUp();
	};
}