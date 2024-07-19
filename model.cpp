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
        else if (lineSplit[0] == "vn") {
            Vec3f n;
            for (int j = 0; j < 3; j++) {
                double tmp = lineSplit[j + 1].toDouble();
                n[j] = static_cast<float>(tmp);
            }
            this->norms_.push_back(n);
        }
        else if (lineSplit[0] == "vt") {
            Vec2f uv;
            for (int j = 0; j < 2; j++) {
                double tmp = lineSplit[j + 1].toDouble();
                uv[j] = static_cast<float>(tmp);
            }
            this->uv_.push_back(uv);
        }
        else if (lineSplit[0] == "f") {
            std::vector<Vec3i> f;
            Vec3i tmp;
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    tmp[k] = lineSplit[j + 1].split("/")[k].toInt() - 1;
                }
                f.push_back(tmp);
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
    std::vector<int> face;
    for (int j = 0; j < (int)faces_[i].size(); j++)
        face.push_back(faces_[i][j][0]);
    return face;
}
