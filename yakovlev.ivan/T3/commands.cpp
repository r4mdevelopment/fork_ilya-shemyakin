#include <iostream>
#include <numeric>
#include <algorithm>
#include <functional>
#include "commands.h"
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std::placeholders;

namespace yakovlev
{
  int isArgANumber(const std::string& str)
  {
    char* end;
    int num = strtol(str.c_str(), &end, 10);
    if (*end != 0)
    {
      return -1;
    }
    return num;
  }

  double area(std::vector<Polygon>& figures, const std::string& arg){
    int num = isArgANumber(arg);

    if (num == -1){
      if (arg == "EVEN") {
        return std::accumulate(figures.begin(), figures.end(), 0.0, std::bind(accumulateArea, _1, _2, 2, 0));
      }
      else if (arg == "ODD"){
        return std::accumulate(figures.begin(), figures.end(), 0.0, std::bind(accumulateArea, _1, _2, 2, 1));
      }
      else if (arg == "MEAN" && figures.size() >= 1){
        return std::accumulate(figures.begin(), figures.end(), 0.0, std::bind(accumulateArea, _1, _2, 2, -1)) / figures.size();
      }
      else{
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
    else if (num > 2){
      return std::accumulate(figures.begin(), figures.end(), 0.0, std::bind(accumulateAreaByVertexes, _1, _2, num));
    }
    else{
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  double maxArea(std::vector<Polygon>& figures)
  {
    if (figures.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    return calculatePolygonArea(*std::max_element(figures.begin(), figures.end(), compareArea));
  }

  int maxVertexes(std::vector<Polygon>& figures)
  {
    if (figures.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    return std::max_element(figures.begin(), figures.end(), compareVertexes)->points.size();
  }

  double minArea(std::vector<Polygon>& figures)
  {
    if (figures.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    return calculatePolygonArea(*std::min_element(figures.begin(), figures.end(), compareArea));
  }

  int minVertexes(std::vector<Polygon>& figures)
  {
    if (figures.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    return std::min_element(figures.begin(), figures.end(), compareVertexes)->points.size();
  }

  int count(std::vector<Polygon>& figures, const std::string& arg)
  {
    int num = isArgANumber(arg);

    if (num == -1)
    {
      if (arg == "EVEN")
      {
        return std::count_if(figures.begin(), figures.end(), std::bind(checkCountCondition, _1, 2, 0));
      }
      else if (arg == "ODD")
      {
        return std::count_if(figures.begin(), figures.end(), std::bind(checkCountCondition, _1, 2, 1));
      }
      else
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
    else if (num > 2)
    {
      return std::count_if(figures.begin(), figures.end(), std::bind(checkCountConditionVertexes, _1, num));
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  int rects(std::vector<Polygon>& figures) {
    return std::count_if(figures.begin(), figures.end(), [](Polygon& p) {
      if (p.points.size() != 4) {
        return false; // Если количество вершин не равно 4, это не прямоугольник
      }
      // Проверяем, что противоположные стороны равны
      return isEqualSides(p.points[0], p.points[1], p.points[2], p.points[3]) &&
        isEqualSides(p.points[1], p.points[2], p.points[3], p.points[0]);
      });
  }

  int same(const std::vector<Polygon>& polygons, const Polygon& target) {
    return std::count_if(polygons.begin(), polygons.end(),
      [&target](const Polygon& poly)
      {
        return checkPolygonOverlap(poly, target);
      });
  }
}
