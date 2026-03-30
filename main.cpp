#include "tgaimage.h"
#include "model.cpp"

constexpr int width  = 800;
constexpr int height = 800;

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

void line(int ax, int ay, int bx, int by, TGAImage &frameBuffer, TGAColor color) {
    bool steep = std::abs(ax - bx) < std::abs(ay - by);
    if (steep) {
        std::swap(ax, ay);
        std::swap(bx, by);
    }

    if (ax > bx) {
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    
    for (int x = ax; x <= bx; x++) {
        float t = (x - ax) / static_cast<float>(bx - ax);
        int y = std::round(ay + t * (by - ay));
        steep ? frameBuffer.set(y, x, color) : frameBuffer.set(x, y, color);
    }
}

std::tuple<int, int> project(Vertex v){
    return 
    {
        (v.x + 1.) * width/2,
        (v.y + 1.) * height/2,
    };
}

int main(int argc, char** argv) {
    TGAImage framebuffer(width, height, TGAImage::RGB);

    Model objModel;
    objModel.loadObj("obj/diablo3_pose/diablo3_pose.obj");

    for (int i = 0; i < objModel.triangles.size(); i++) {
        Triangle faceVertex = objModel.triangles.at(i); // i-th face containing 3 vertex indices
        auto [ax, ay] = project(objModel.vertices.at(faceVertex.v1));
        auto [bx, by] = project(objModel.vertices.at(faceVertex.v2));
        auto [cx, cy] = project(objModel.vertices.at(faceVertex.v3));

        line(ax, ay, bx, by, framebuffer, red);
        line(cx, cy, bx, by, framebuffer, red);
        line(cx, cy, ax, ay, framebuffer, red);
        line(ax, ay, cx, cy, framebuffer, red);
    }

    for (int i = 0; i < objModel.vertices.size(); i++) {
        auto [x, y] = project(objModel.vertices.at(i));
        framebuffer.set(x, y, white);
    }

    framebuffer.write_tga_file("wireframe.tga");
    return 0;
}