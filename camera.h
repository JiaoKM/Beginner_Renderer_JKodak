#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include <QtMath>


class Camera
{
public:
    Camera();
    ~Camera();
    Vec3f get_pos();
    Vec3f get_dir();
    Vec3f get_center();
    void set_pos(Vec3f pos);
private:
    Vec3f position;
    Vec3f center;
    Vec3f direction;
};

#endif // CAMERA_H
