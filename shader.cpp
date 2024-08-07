#include "shader.h"

Shader::Shader(Model *m)
{
    this->shader_model = m;
}

Shader::~Shader()
{
    delete this->shader_model;
}

QRgb Shader::sample2D(const QImage &img, Vec2f uvf)
{
    return img.pixel(uvf[0] * img.width(), uvf[1] * img.height());
}

PhongShader::~PhongShader()
{
    delete this->shader_model;
}
