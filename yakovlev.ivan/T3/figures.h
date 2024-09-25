#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <vector>
#include <cmath>

namespace yakovlev
{
  struct Point
  {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Point& other);
    bool operator!=(const Point& other);

  };

  struct Polygon
  {
    std::vector<Point> points;

    bool operator==(const Polygon& other);
  };

  struct DelimiterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::vector<Polygon> inPolygons(std::istream& in);

  //функция считает площадь треугольника
  double calculateTriangleArea(const Point& p1, const Point& p2, const Point& p3);
  //функция считает площадь полигона
  double calculatePolygonArea(const Polygon& polygon);

  double accumulateArea(double acc, const Polygon& poly, int div, int rem);

  double accumulateAreaByVertexes(double acc, const Polygon& poly, int numOfVertexes);

  //функция сравнивает площади
  bool compareArea(const Polygon& a, const Polygon& b);
  //функция сравнивает вершины
  bool compareVertexes(const Polygon& a, const Polygon& b);

  bool checkCountCondition(const Polygon& poly, int div, int rem);

  bool checkCountConditionVertexes(const Polygon& poly, int numOfVertexes);

  //функция проверят накладываются ли два полигона
  bool checkPolygonOverlap(const Polygon& a, const Polygon& b);
  //функция проверят равны ли стороны
  bool isEqualSides(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

  class IOFormatGuard
  {
  public:
    IOFormatGuard(std::basic_ios<char>& s);
    ~IOFormatGuard();
  private:
    std::basic_ios<char>& stream_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags formatFlags_;
  };

}
#endif
