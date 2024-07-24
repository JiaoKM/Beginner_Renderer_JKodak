#include "camera.h"

Camera::Camera()
{
    this->position = Vec3f(3, 3, 3);
    this->center = Vec3f(0, 0, 0);
}

Camera::~Camera()
{

}

Vec3f Camera::get_pos()
{
    return this->position;
}

Vec3f Camera::get_center()
{
    return this->center;
}

Vec3f Camera::get_dir()
{
    return (this->position - this->center).normalize();
}

void Camera::set_pos(Vec3f pos)

{
    this->position = pos;
}
