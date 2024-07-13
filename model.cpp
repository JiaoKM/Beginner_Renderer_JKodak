#include "model.h"

Model::Model(QString modelPath)
{
    QFile modelFile(modelPath);
    QString modelContent;
    if (modelFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        load_flag = true;
        QTextStream in(&modelFile);
        modelContent = in.readAll();
        modelFile.close();
    }
    else {
        load_flag = false;
        return;
    }
}

Model::~Model()
{

}

int Model::nVerts()
{
    return (int)verts_.size();
}

int Model::nFaces()
{
    return (int)faces_.size();
}

Vec3f Model::vert(int i)
{
    return verts_[i];
}

std::vector<int> Model::face(int i)
{
    return faces_[i];
}
