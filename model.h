#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Vertex {
  float x, y, z = 0.0;
};

struct Triangle {
  int v1, v2, v3 = 0;
};

class Model {
  public:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;

    void loadObj(const std::string &path);

    // ** DEBUG 
    void headVertices() {
      for (int i = 0; i < 5; i++) {
        std::cout << vertices.at(i).x << " " 
                  << vertices.at(i).y << " " 
                  << vertices.at(i).z << std::endl;
      }
    }

    void headFaces() {
      for (int i = 0; i < 5; i++) {
        std::cout << triangles.at(i).v1 << " "
                  << triangles.at(i).v2 << " "
                  << triangles.at(i).v3 << std::endl;
      }
    }
};