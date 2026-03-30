#include "model.h"

void Model::loadObj(const std::string &path) {
  std::ifstream objFile(path);
  if (!objFile.is_open()) {
    std::cerr << "Error opening file: " << path << std::endl;
  }

  std::string line;
  while (std::getline(objFile, line)) {
    std::istringstream ss(line);
    std::string prefix;
    ss >> prefix;

    if (prefix == "v") {
      Vertex v;
      ss >> v.x >> v.y >> v.z;
      vertices.push_back(v);
    }
    else if (prefix == "f") {
      Triangle t; 
      std::string v1_str, v2_str, v3_str;
      ss >> v1_str >> v2_str >> v3_str;

      t.v1 = std::stoi(v1_str.substr(0, v1_str.find('/')));
      t.v2 = std::stoi(v2_str.substr(0, v2_str.find('/')));
      t.v3 = std::stoi(v3_str.substr(0, v3_str.find('/')));

      t.v1--; t.v2--; t.v3--;
      triangles.push_back(t);
    }
  }
}