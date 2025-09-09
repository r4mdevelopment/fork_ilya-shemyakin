#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include "commands.h"
#include "figures.h"

int main(int argc, char* argv[]) {
  using namespace yakovlev;

  if (argc != 2) {
    std::cerr << "ERROR! You need to use ./lab filename.txt" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cerr << "Error! Opening file process was ruined " << filename << std::endl;
    return 1;
  }

  std::vector<Polygon> figures;
  figures = inPolygons(fin);

  std::cout << std::setprecision(1) << std::fixed;

  try {
    while (!std::cin.eof()) {
      std::string cmd = "";
      std::cin >> cmd;
      try {
        if (cmd == "AREA") {
          std::string arg = "";
          std::cin >> arg;
          std::cout << area(figures, arg) << std::endl;
        }
        else if (cmd == "MAX" && figures.size() >= 1) {
          std::string arg = "";
          std::cin >> arg;
          if (arg == "AREA") {
            std::cout << maxArea(figures) << std::endl;
          }
          else if (arg == "VERTEXES") {
            std::cout << maxVertexes(figures) << std::endl;
          }
          else {
            throw std::invalid_argument("<INVALID COMMAND>");
          }
        }
        else if (cmd == "MIN" && figures.size() >= 1) {
          std::string arg = "";
          std::cin >> arg;
          if (arg == "AREA") {
            std::cout << minArea(figures) << std::endl;
          }
          else if (arg == "VERTEXES") {
            std::cout << minVertexes(figures) << std::endl;
          }
          else {
            throw std::invalid_argument("<INVALID COMMAND>");
          }
        }
        else if (cmd == "COUNT") {
          std::string arg = "";
          std::cin >> arg;
          std::cout << count(figures, arg) << std::endl;
        }
        else if (cmd == "RECTS") {
          std::cout << rects(figures) << std::endl;
        }
        else if (cmd == "SAME") {
          Polygon target;
          std::cin >> target;
          if (!std::cin) {
            throw std::invalid_argument("<INVALID COMMAND>");
          }
          std::cout << same(figures, target) << std::endl;
        }
        else if (cmd != "") {
          throw std::invalid_argument("<INVALID COMMAND>");
        }
      }
      catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    return 0;
  }
  catch (...) {
    std::cerr << "Unexpected error.." << std::endl;
    return 1;
  }
}
