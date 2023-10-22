#include "include/render/camera/render_camera.h"

namespace ToolEngine
{
    glm::mat4 RenderCamera::getProjectionMatrix()
    {
        glm::mat4 projection_matrix = glm::perspective(fov, aspect, near_plane, far_plane);
        projection_matrix[1][1] *= -1;
        return projection_matrix;
    }
    glm::mat4x4 RenderCamera::getViewMatrix()
    {
        /*Transform temp_transform = transform;
        temp_transform.rotation = {-transform.rotation.x, transform.rotation.y, 0};*/
        glm::mat4x4 translation_matrix = transform.getTranslationMatrix();
        glm::mat4x4 rotation_matrix = transform.getRotationMatrix();
        glm::mat4x4 view_matrix = glm::inverse(translation_matrix * rotation_matrix);
        return view_matrix;
    }
}