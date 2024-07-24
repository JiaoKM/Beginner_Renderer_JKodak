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
        this->load_flag = false;
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

    this->load_flag = true;
    this->load_texture(modelPath, "_diffuse.jpg");
}

Model::~Model()
{
    delete this->diffuseMap;
}

int Model::nVerts()
{
    return (int)this->verts_.size();
}

int Model::nFaces()
{
    return (int)this->faces_.size();
}

Vec3f Model::vert(int i)
{
    return this->verts_[i];
}

std::vector<int> Model::face(int i)
{
    std::vector<int> face;
    for (int j = 0; j < (int)this->faces_[i].size(); j++)
        face.push_back(this->faces_[i][j][0]);
    return face;
}

Vec2i Model::uv(int iFace, int nVert)
{
    int idx = this->faces_[iFace][nVert][1];
    return Vec2i(this->uv_[idx].x * diffuseMap->width(), this->uv_[idx].y * diffuseMap->height());
}

Vec3f Model::norm(int iFace, int nVert)
{
    int idx = this->faces_[iFace][nVert][2];
    return norms_[idx].normalize();
}

void Model::load_texture(QString objFilename, QString suffix)
{
    QString title = objFilename.split(".")[0];
    QString textureFilename = title + suffix;
    this->diffuseMap = new QImage(textureFilename);
}

QColor Model::diffuse(Vec2i uv)
{
    return QColor(this->diffuseMap->pixel(uv.x, uv.y));
}
