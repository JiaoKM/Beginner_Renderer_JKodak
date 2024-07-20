#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QTextStream>
#include <QString>
#include <QColor>
#include <QImage>
#include <QFile>
#include "geometry.h"

class Model
{
public:
    Model(QString modelPath);
    ~Model();
    int nVerts();
    int nFaces();
    bool load_flag = true;

    Vec3f vert(int i);
    Vec2i uv(int iFace, int nVert);
    QColor diffuse(Vec2i uv);
    std::vector<int> face(int i);
private:
    std::vector<Vec3f> verts_;
    std::vector<std::vector<Vec3i>> faces_;
    std::vector<Vec3f> norms_;
    std::vector<Vec2f> uv_;
    QImage *diffuseMap;
    void load_texture(QString objFilename, QString suffix);
};

#endif // MODEL_H
