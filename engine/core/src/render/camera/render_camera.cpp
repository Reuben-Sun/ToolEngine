#include "include/render/camera/render_camera.h"

namespace ToolEngine
{
    glm::mat4x4 RenderCamera::getProjectionMatrix()
    {
        float y = 1.0f / tan(fov * 0.5);
        float x = y / aspect;
        float z = left_handed ? far_plane / (near_plane - far_plane) : far_plane / (far_plane - near_plane);
        float z2 = left_handed ? 1 : -1;
        float w = left_handed ? (z * -near_plane) : (z * near_plane);
        glm::mat4x4 projection_matrix =
        {
            x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, z2,
            0, 0, w, 0  
        };
        return projection_matrix;
    }
    glm::mat4x4 RenderCamera::getViewMatrix()
    {
        Transform temp_transform = transform;
        temp_transform.rotation = {-transform.rotation.x, transform.rotation.y, 0};
        glm::mat4x4 translation_matrix = transform.getTranslationMatrix();
        glm::mat4x4 rotation_matrix = temp_transform.getRotationMatrix();
        glm::mat4x4 view_matrix = glm::inverse(translation_matrix * rotation_matrix);
        return view_matrix;
    }
}