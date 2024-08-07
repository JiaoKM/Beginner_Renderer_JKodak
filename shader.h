#ifndef SHADER_H
#define SHADER_H

#include <QImage>
#include <QColor>
#include "geometry.h"
#include "model.h"


class Shader
{
public:
    Shader(Model *m);
    virtual ~Shader();
    QRgb sample2D(const QImage &img, Vec2f uvf);
    virtual Vec3f vertexShader(int iFace, int iVert) = 0;
    virtual QRgb fragmentShader(Vec3f pos) = 0;

    Model *shader_model;
};

class PhongShader: public Shader
{
public:
    using Shader::Shader;
    ~PhongShader();
    Vec3f vertexShader(int iFace, int iVert);
    QRgb fragmentShader(Vec3f pos);
};

#endif // SHADER_H
