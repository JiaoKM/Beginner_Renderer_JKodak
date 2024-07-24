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
    Camera *camera;
private:
    int width;
    int height;
    float *zBuffer;

    void triangle(Vec3i t0, Vec3i t1, Vec3i t2, Vec2i uv0, Vec2i uv1, Vec2i uv2, ShowPicLabel *showLabel, Model *model, float *intensity);
    Vec3f baryCentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P);
    Matrix lookAt(Vec3f up);
    Matrix viewport(int x, int y, int w, int h);
};

#endif // RENDERER_H
