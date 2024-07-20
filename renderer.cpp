#include "renderer.h"

renderer::renderer(int width, int height)
{
    this->width = width;
    this->height = height;
    this->zBuffer = new float[width * height];
    for (int i = width * height; i--; zBuffer[i] = -std::numeric_limits<float>::max());
}

renderer::~renderer()
{

}

Vec3f renderer::world2screen(Vec3f v)
{
    return Vec3f(int((v.x + 1.0) * this->width / 2.0 + 0.5), int((v.y + 1.0) * this->height / 2.0 + 0.5), v.z);
}

Vec3f renderer::baryCentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P)
{
    Vec3f s[2];
        for (int i = 2; i--; ) {
            s[i][0] = C[i] - A[i];
            s[i][1] = B[i] - A[i];
            s[i][2] = A[i] - P[i];
        }
        Vec3f u = cross(s[0], s[1]);
        if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
            return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
        return Vec3f(-1, 1, 1);
}

void renderer::triangle(Vec3f *pts, Vec2i *uv, ShowPicLabel *showLabel, Model *model, float intensity)
{
    Vec2f bboxmin(std::numeric_limits<float>::max(),  std::numeric_limits<float>::max());
    Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
    Vec2f clamp(this->width - 1, this->height - 1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            bboxmin[j] = std::max(0.f, std::min(bboxmin[j], pts[i][j]));
            bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
        }
    }
    Vec3f P;
    Vec2i uvP;
    for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
        for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
            Vec3f bc_screen = this->baryCentric(pts[0], pts[1], pts[2], P);
            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
            P.z = 0;
            uvP.x = 0;
            uvP.y = 0;
            for (int i = 0; i < 3; i++) {
                P.z += pts[i][2] * bc_screen[i];
                uvP.x += uv[i].x * bc_screen[i];
                uvP.y += uv[i].y * bc_screen[i];
            }
            if (this->zBuffer[int(P.x + P.y * this->width)] < P.z) {
                this->zBuffer[int(P.x + P.y * this->width)] = P.z;
                QColor color = model->diffuse(uvP);
                QRgb textureColor = qRgba(color.red() * intensity, color.green() * intensity, color.blue() * intensity, 255);
                showLabel->SetPixel(P.x, P.y, textureColor);
            }
        }
    }
}

bool renderer::render(ShowPicLabel *showLabel, Model *model)
{
    Vec3f light_dir(0, 0, -1);
    for (int i = 0; i < model->nFaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3f pts[3];
        for (int j = 0; j < 3; j++) pts[j] = model->vert(face[j]);
        Vec3f n = cross(pts[2] - pts[0], pts[1] - pts[0]);
        n.normalize();
        float intensity = n * light_dir;
        for (int j = 0; j < 3; j++) pts[j] = this->world2screen(pts[j]);

        if (intensity > 0) {
            Vec2i uv[3];
            for (int k = 0; k < 3; k++) uv[k] = model->uv(i, k);
            this->triangle(pts, uv, showLabel, model, intensity);
        }
    }
    showLabel->UpdatePic();

    return true;
}
