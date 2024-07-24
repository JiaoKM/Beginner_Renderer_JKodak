#include "camera.h"

Camera::Camera()
{
    this->position = Vec3f(0, 0, 3);
}

Camera::~Camera()
{

}

Vec3f Camera::get_pos()
{
    return this->position;
}

Vec3f Camera::get_dir()
{
    return (this->position - Vec3f(0.0, 0.0, 0.0)).normalize();
}

void Camera::set_pos(Vec3f pos)

{
    this->position = pos;
}
