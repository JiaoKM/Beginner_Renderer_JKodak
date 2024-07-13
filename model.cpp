#include "model.h"

Model::Model(QString modelPath)
{
    QFile modelFile(modelPath);
    QString modelContent;
    if (modelFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&modelFile);
        modelContent = in.readAll();
        modelFile.close();
    }
    else {
        load_flag = false;
        return;
    }

    QStringList lines = modelContent.split("\n");
    for (int i = 0; i < lines.size(); i++) {
        QString line = lines[i];
        QStringList lineSplit = line.split(" ");
        if (lineSplit[0] == "v") {
            Vec3f v;
            for (int j = 0; j < 3; j++) {
                double tmp = lineSplit[j + 1].toDouble();
                v[j] = static_cast<float>(tmp);
            }
            this->verts_.push_back(v);
        }
        else if (lineSplit[0] == "f") {
            std::vector<int> f;
            for (int j = 0; j < 3; j++) {
                f.push_back(lineSplit[j + 1].split("/")[0].toInt() - 1);
            }
            this->faces_.push_back(f);
        }
    }

    load_flag = true;
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
