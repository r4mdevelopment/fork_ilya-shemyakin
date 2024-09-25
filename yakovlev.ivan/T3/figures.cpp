#include <numeric>
#include <algorithm>
#include <cmath>
#include <iterator>
#include "figures.h"

namespace yakovlev{
  bool Point::operator==(const Point& other) {
    return this->x == other.x && this->y == other.y;
  }

  bool Point::operator!=(const Point& other){
    return (this->x != other.x) || (this->y != other.y);
  }

  bool Polygon::operator==(const Polygon& other){
    if (this->points.size() != other.points.size()){
      return false;
    }

    for (size_t i = 0; i < this->points.size(); ++i){
      if (this->points[i] != other.points[i]){
        return false;
      }
    }
    return true;
  }

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest){
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char symbol = '0';
    in >> symbol;
    if (in && (symbol != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Point& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' } >> dest.y >> DelimiterIO{ ')' };
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    Polygon input;
    {
      int size = 0;
      in >> size;
      if (!in || size < 3)
      {
        in.setstate(std::ios::failbit);
        return in;
      }

      int PointsCount = 0;
      while (PointsCount < size)
      {
        if (!in)
        {
          in.setstate(std::ios::failbit);
        }
        if (in.peek() == '\n')
        {
          break;
        }
        Point point;
        in >> point;
        input.points.push_back(point);
        ++PointsCount;
      }
      if (PointsCount != size || (in.peek() != '\n' && !in.eof()))
      {
        in.setstate(std::ios::failbit);
      }
    }
    if (in)
    {
      polygon = input;
    }
    return in;
  }

  std::vector<Polygon> inPolygons(std::istream& in)
  {
    std::vector<Polygon> polygons;
    while (!in.eof())
    {
      if (!in)
      {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      std::copy(
        std::istream_iterator<Polygon>(in),
        std::istream_iterator<Polygon>(),
        std::back_inserter(polygons)
      );
    }
    return polygons;
  }

  double calculateTriangleArea(const Point& p1, const Point& p2, const Point& p3){
    double a = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    double b = sqrt((p2.x - p3.x) * (p2.x - p3.x) + (p2.y - p3.y) * (p2.y - p3.y));
    double c = sqrt((p3.x - p1.x) * (p3.x - p1.x) + (p3.y - p1.y) * (p3.y - p1.y));
    double p = (a + b + c) / 2;

    return sqrt(p * (p - a) * (p - b) * (p - c));
  }

  double calculatePolygonArea(const Polygon& polygon){
    const Point p0 = polygon.points[0];
    Point prev = polygon.points[1];

    auto lambda = [&p0, &prev](double acc, const Point& cur){
        acc += calculateTriangleArea(p0, prev, cur);
        prev = cur;
        return acc;
      };
    return std::accumulate(polygon.points.begin() + 2, polygon.points.end(), 0.0, lambda);
  }

  double accumulateArea(double acc, const Polygon& poly, int div, int rem){
    double res = acc;
    if (int(poly.points.size()) % div == rem || rem == -1)
    {
      res += calculatePolygonArea(poly);
    }
    return res;
  }

  double accumulateAreaByVertexes(double acc, const Polygon& poly, int numOfVertexes){
    double res = acc;
    if (int(poly.points.size()) == numOfVertexes){
      res += calculatePolygonArea(poly);
    }
    return res;
  }

  bool compareArea(const Polygon& a, const Polygon& b){
    return calculatePolygonArea(a) < calculatePolygonArea(b);
  }

  bool compareVertexes(const Polygon& a, const Polygon& b){
    return a.points.size() < b.points.size();
  }

  bool checkCountCondition(const Polygon& poly, int div, int rem) {
    return (int(poly.points.size()) % div == rem);
  }

  bool checkCountConditionVertexes(const Polygon& poly, int numOfVertexes) {
    return (int(poly.points.size()) == numOfVertexes);
  }

  bool checkPolygonOverlap(const Polygon& a, const Polygon& b) {
    // ѕровер€ем количество вершин
    if (a.points.size() != b.points.size()) {
      return false;
    }

    // Ќаходим крайнюю верхнюю правую точку в каждой фигуре
    auto maxElementComp = [](const Point& p1, const Point& p2) {
      return (p1.y < p2.y) || (p1.y == p2.y && p1.x < p2.x);
      };
    Point aTopRight = *std::max_element(a.points.begin(), a.points.end(), maxElementComp);
    Point bTopRight = *std::max_element(b.points.begin(), b.points.end(), maxElementComp);

    // ќпредел€ем смещение дл€ каждой фигуры
    int offsetX = bTopRight.x - aTopRight.x;
    int offsetY = bTopRight.y - aTopRight.y;

    //  опируем и смещаем точки второй фигуры
    std::vector<Point> bShifted(b.points.size());
    std::transform(b.points.begin(), b.points.end(), bShifted.begin(),
      [offsetX, offsetY](const Point& p) {
        return Point{ p.x - offsetX, p.y - offsetY };
      });

    // ѕровер€ем, совпадают ли все точки после смещени€
    return std::all_of(a.points.begin(), a.points.end(),
      [&bShifted](const Point& p1) {
        return std::any_of(bShifted.begin(), bShifted.end(),
        [&p1](const Point& p2) {
            return (p1.x == p2.x) && (p1.y == p2.y);
          });
      });
  }

  bool isEqualSides(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    double dist1 = std::hypot(p1.x - p2.x, p1.y - p2.y);
    double dist2 = std::hypot(p3.x - p4.x, p3.y - p4.y);
    return std::abs(dist1 - dist2) < 1e-6; // ѕровер€ем, что разница между длинами сторон не превышает некоторой малой величины
  }

  IOFormatGuard::IOFormatGuard(std::basic_ios<char>& s) :
    stream_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    formatFlags_(s.flags())
  {}

  IOFormatGuard::~IOFormatGuard()
  {
    stream_.fill(fill_);
    stream_.precision(precision_);
    stream_.flags(formatFlags_);
  }
}
