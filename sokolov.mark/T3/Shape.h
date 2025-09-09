#ifndef SHAPE_H
#define SHAPE_H

#include "local.h"

namespace sokolov
{

  struct Point
  {
    int x, y;
    double getDistance(const Point& point) const;
    bool operator !=(const Point& other) const;
  };

  double getTriangleArea(const Point& pointFirst, const Point& pointSecond, const Point& pointThird);

  struct Segment
  {
    Point begin, end;

    bool isIntersect(const Segment& other, std::pair<double, double>* intr) const;
  };

  struct DelimeterIO
  {
    char exp;
  };

  struct Polygon
  {
    std::vector< Point > points;
    bool operator <(const Polygon& other) const;
    bool operator==(const Polygon& other) const;
    double getArea() const;
    bool contains(const Point& pnt) const;
    std::vector<Segment> createSegmentPool(void) const;
    bool isIntersect(const Polygon& other) const;
  };

  std::istream& operator >> (std::istream& in, sokolov::DelimeterIO&& del);
  std::istream& operator >> (std::istream& in, sokolov::Point& point);
  std::istream& operator >> (std::istream& in, sokolov::Polygon& poly);
  std::ostream& operator << (std::ostream& out, const sokolov::Point& point);
  std::ostream& operator << (std::ostream& out, const sokolov::Polygon& poly);
}

#endif
