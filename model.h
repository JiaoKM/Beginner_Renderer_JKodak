#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QTextStream>
#include <QString>
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
    Vec3f vert(int i);
    std::vector<int> face(int i);
private:
    bool load_flag = true;
    std::vector<Vec3f> verts_;
    std::vector<std::vector<int>> faces_;
};

#endif // MODEL_H
