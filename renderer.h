#ifndef RENDERER_H
#define RENDERER_H

#include <limits>
#include <QColor>
#include "showpiclabel.h"
#include "geometry.h"
#include "model.h"

class renderer
{
public:
    renderer(int width, int height);
    ~renderer();
    bool render(ShowPicLabel *showLabel, Model *model);
private:
    int width;
    int height;

    float *zBuffer;
    void triangle(Vec3f *pts, Vec2i *uv, ShowPicLabel *showLabel, Model *model, float intensity);
    Vec3f baryCentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P);
    Vec3f world2screen(Vec3f v);
};

#endif // RENDERER_H
