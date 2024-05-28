#ifndef COMMANDS_H
#define COMMANDS_H

#include "local.h"
#include "Shape.h"

namespace commands
{
  int convertToNumber(const std::string& str);
  void getFullArea(const std::vector<sokolov::Polygon>& polygons);
  void getMin(const std::vector<sokolov::Polygon>& data);
  void getMax(const std::vector<sokolov::Polygon>& data);
  void countFigures(const std::vector<sokolov::Polygon>& polygons);
  sokolov::FrameRectangle getFrameRectangle(const std::vector<sokolov::Polygon>& polygons);
  void checkStream();
  void lessarea(std::vector<sokolov::Polygon>& value);
  void intersections(const std::vector<sokolov::Polygon>& data);
}

#endif
