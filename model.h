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
    bool load_flag = true;

    Vec3f vert(int i);
    std::vector<int> face(int i);
private:

    std::vector<Vec3f> verts_;
    std::vector<std::vector<int>> faces_;
};

#endif // MODEL_H
