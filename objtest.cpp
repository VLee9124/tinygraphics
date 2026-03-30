#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "./model.cpp"

int main() {
  Model obj;

  obj.loadObj("./obj/diablo3_pose/diablo3_pose.obj");

  std::cout << obj.vertices.size() << std::endl;
  std::cout << obj.triangles.size() << std::endl;

  obj.headVertices();
  obj.headFaces();

  return 0;
}