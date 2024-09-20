#include "renderer.h"

renderer::renderer(int width, int height)
{
    this->width = width;
    this->height = height;
    this->zBuffer = new float[width * height];
    this->reset_zBuffer();
    this->camera = new Camera();
}

renderer::~renderer()
{
    delete this->camera;
}

void renderer::reset_zBuffer()
{
    for (int i = width * height; i--; zBuffer[i] = -std::numeric_limits<float>::max());
}

Matrix renderer::lookAt(Vec3f up)
{
    Vec3f z = this->camera->get_dir();
    Vec3f x = (up ^ z).normalize();
    Vec3f y = (z ^ x).normalize();
    Matrix res = Matrix::identity(4);
    for (int i = 0; i < 3; i++) {
        res[0][i] = x[i];
        res[1][i] = y[i];
        res[2][i] = z[i];
        res[i][3] = -this->camera->get_center()[i];
    }
    return res;
}

Matrix renderer::viewport(int x, int y, int w, int h)
{
    Matrix m = Matrix::identity(4);
    m[0][3] = x + w / 2.f;
    m[1][3] = y + h / 2.f;
    m[2][3] = 255 / 2.f;
    m[0][0] = w / 4.f;
    m[1][1] = h / 4.f;
    m[2][2] = 255 / 4.f;
    return m;
}

Vec3f renderer::baryCentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P)
{
    Vec3f s[2];
        for (int i = 2; i--; ) {
            s[i][0] = C[i] - A[i];
            s[i][1] = B[i] - A[i];
            s[i][2] = A[i] - P[i];
        }
        Vec3f u = s[0] ^ s[1];
        if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
            return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
        return Vec3f(-1, 1, 1);
}

void renderer::triangle(Vec3i t0, Vec3i t1, Vec3i t2, Vec2i uv0, Vec2i uv1, Vec2i uv2, ShowPicLabel *showLabel, Model *model, float *intensity)
{
    if (t0.y==t1.y && t0.y==t2.y) return;
    if (t0.y>t1.y) { std::swap(t0, t1); std::swap(uv0, uv1); }
    if (t0.y>t2.y) { std::swap(t0, t2); std::swap(uv0, uv2); }
    if (t1.y>t2.y) { std::swap(t1, t2); std::swap(uv1, uv2); }

        int total_height = t2.y-t0.y;
        for (int i=0; i < total_height; i++) {
            bool second_half = i>t1.y-t0.y || t1.y==t0.y;
            int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
            float alpha = (float)i/total_height;
            float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height;
            Vec3i A   =               t0  + Vec3f(t2 - t0  ) * alpha;
            Vec3i B   = second_half ? t1  + Vec3f(t2 - t1  ) * beta : t0  + Vec3f(t1 - t0) * beta;
            Vec2i uvA =               uv0 +      (uv2 - uv0) * alpha;
            Vec2i uvB = second_half ? uv1 +      (uv2 - uv1) * beta : uv0 +      (uv1 - uv0) * beta;
            if (A.x>B.x) { std::swap(A, B); std::swap(uvA, uvB); }
            for (int j=A.x; j<=B.x; j++) {
                float phi = B.x==A.x ? 1. : (float)(j-A.x)/(float)(B.x-A.x);
                Vec3i   P = Vec3f(A) + Vec3f(B-A)*phi;
                if (P.x > width - 1 || P.x < 0 || P.y > height - 1 || P.y < 0) continue;
                Vec2i uvP =     uvA +   (uvB-uvA)*phi;
                int idx = P.x+P.y*width;
                if (this->zBuffer[idx]<P.z) {
                    this->zBuffer[idx] = P.z;
                    QColor color = model->diffuse(uvP);
                    if (intensity[0] <= 0) color.setRed(0);
                    if (intensity[1] <= 0) color.setGreen(0);
                    if (intensity[2] <= 0) color.setBlue(0);
                    QRgb textureColor = qRgba(color.red() * intensity[0], color.green() * intensity[1], color.blue() * intensity[2], 255);
                    showLabel->SetPixel(P.x, P.y, textureColor);
                }
            }
        }
}

bool renderer::render(ShowPicLabel *showLabel, Model *model)
{
    Vec3f light_dir = Vec3f(1, -1, 1).normalize();
    Matrix Projection = Matrix::identity(4);
    Projection[3][2] = -1.f / (this->camera->get_pos() - this->camera->get_center()).norm();
    Matrix ViewPort = viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4);
    Matrix ModelView = lookAt(Vec3f(0, 1 ,0));

    for (int i = 0; i < model->nFaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3i screen_coords[3];
        Vec3f world_coords[3];
        Vec2i uv[3];
        float intensity[3];
        for (int j = 0; j < 3; j++) {
            Vec3f v = model->vert(face[j]);
            screen_coords[j] = Vec3f(ViewPort * Projection * ModelView * Matrix(v));
            world_coords[j] = v;
            intensity[j] = model->norm(i, j) * light_dir;
            uv[j] = model->uv(i, j);
        }
        triangle(screen_coords[0], screen_coords[1], screen_coords[2], uv[0], uv[1], uv[2], showLabel, model, intensity);
    }

    return true;
}

void renderer::set_light_pos(Vec3f pos)
{
    this->light_pos = pos;
}
