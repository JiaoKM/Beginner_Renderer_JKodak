#ifndef RENDERER_H
#define RENDERER_H

#include <limits>
#include <QColor>
#include <QtMath>
#include "showpiclabel.h"
#include "geometry.h"
#include "camera.h"
#include "model.h"

class renderer
{
public:
    renderer(int width, int height);
    ~renderer();
    bool render(ShowPicLabel *showLabel, Model *model);
    void reset_zBuffer();
    void set_light_pos(Vec3f pos);
    Camera *camera;
private:
    int width;
    int height;
    float *zBuffer;
    Vec3f light_pos;

    void triangle(Vec3i t0, Vec3i t1, Vec3i t2, Vec2i uv0, Vec2i uv1, Vec2i uv2, ShowPicLabel *showLabel, Model *model, float *intensity);
    Vec3f baryCentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P);
    Matrix lookAt(Vec3f up);
    Matrix viewport(int x, int y, int w, int h);
    QColor phongShading(Model *model, Vec3f light_dir);
};

#endif // RENDERER_H
