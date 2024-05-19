#include <numeric>
#include <algorithm>
#include <cmath>
#include <iterator>
#include "Polygon.h"

namespace mrkv
{
  bool Point::operator==(const Point& other)
  {
    return this->x == other.x && this->y == other.y;
  }

  bool Point::operator!=(const Point& other)
  {
    return (this->x != other.x) || (this->y != other.y);
  }

  bool Polygon::operator==(const Polygon& other)
  {
    if (this->points.size() != other.points.size())
    {
      return false;
    }

    for (size_t i = 0; i < this->points.size(); ++i)
    {
      if (this->points[i] != other.points[i])
      {
        return false;
      }
    }
    return true;
  }

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
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
      int pointsNumber = 0;
      in >> pointsNumber;
      if (!in || pointsNumber <= 2)
      {
        in.setstate(std::ios::failbit);
        return in;
      }

      int readPointsCount = 0;
      while (readPointsCount < pointsNumber)
      {
        if (!in)
        {
          in.setstate(std::ios::failbit);
        }
        char flagChar = in.get();
        if (flagChar == '\n')
        {
          in.putback(flagChar);
          break;
        }
        else
        {
          in.putback(flagChar);
        }
        Point point;
        in >> point;
        input.points.push_back(point);
        ++readPointsCount;
      }
      if (readPointsCount != pointsNumber)
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

  std::ostream& operator<<(std::ostream& out, const Point& point)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(" << point.x << ";" << point.y << ")";
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& polygon)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << polygon.points.size() << " ";
    std::copy(
      std::begin(polygon.points),
      std::end(polygon.points),
      std::ostream_iterator<Point>(std::cout, " ")
    );
    return out;
  }

  std::vector<Polygon> readPolygons(std::istream& in)
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

  double calculateTriangleArea(const Point& p1, const Point& p2, const Point& p3)
  {
    double a = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    double b = sqrt((p2.x - p3.x) * (p2.x - p3.x) + (p2.y - p3.y) * (p2.y - p3.y));
    double c = sqrt((p3.x - p1.x) * (p3.x - p1.x) + (p3.y - p1.y) * (p3.y - p1.y));

    double p = (a + b + c) / 2;

    return sqrt(p * (p - a) * (p - b) * (p - c));
  }

  double calculatePolygonArea(const Polygon& polygon)
  {
    const Point p0 = polygon.points[0];
    Point prev = polygon.points[1];

    auto lambda = [&p0, &prev](double acc, const Point& cur)
      {
        acc += calculateTriangleArea(p0, prev, cur);
        prev = cur;
        return acc;
      };
    return std::accumulate(polygon.points.begin() + 2, polygon.points.end(), 0.0, lambda);
  }

  double areaAccumulator(double acc, const Polygon& poly, int div, int rem)
  {
    double res = acc;
    if (poly.points.size() % div == rem || rem == -1)
    {
      res += calculatePolygonArea(poly);
    }
    return res;
  }
 
  bool areaComporator(const Polygon& a, const Polygon& b)
  {
    return calculatePolygonArea(a) < calculatePolygonArea(b);
  }

  bool vertexesComporator(const Polygon& a, const Polygon& b)
  {
    return a.points.size() < b.points.size();
  }

  bool countCondition(const Polygon& poly, int div, int rem)
  {
    return (poly.points.size() % div == rem) ? true : false;
  }

  int getLeftB(Polygon& poly)
  {
    return std::min_element(poly.points.begin(), poly.points.end(),
      [](Point& cur, Point& smallest) { return cur.x < smallest.x; })->x;
  }
  
  int getRightB(Polygon& poly)
  {
    return std::max_element(poly.points.begin(), poly.points.end(),
      [](Point& cur, Point& biggest) { return cur.x < biggest.x; })->x;
  }

  int getDownB(Polygon& poly)
  {
    return std::min_element(poly.points.begin(), poly.points.end(),
      [](Point& cur, Point& smallest) { return cur.y < smallest.y; })->y;
  }

  int getUpB(Polygon& poly)
  {
    return std::max_element(poly.points.begin(), poly.points.end(),
      [](Point& cur, Point& biggest) { return cur.y < biggest.y; })->y;
  }

  int getLeftFiguresB(std::vector<Polygon>& figures)
  {
    return getLeftB(*std::min_element(figures.begin(), figures.end(),
      [](Polygon& cur, Polygon& smallestByX) { return getLeftB(cur) < getLeftB(smallestByX); })
    );
  }

  int getRightFiguresB(std::vector<Polygon>& figures)
  {
    return getRightB(*std::max_element(figures.begin(), figures.end(),
      [](Polygon& cur, Polygon& biggestByX) { return getRightB(cur) < getRightB(biggestByX); })
    );
  }

  int getDownFiguresB(std::vector<Polygon>& figures)
  {
    return getDownB(*std::min_element(figures.begin(), figures.end(),
      [](Polygon& cur, Polygon& smallestByY) { return getDownB(cur) < getDownB(smallestByY); })
    );
  }

  int getUpFiguresB(std::vector<Polygon>& figures)
  {
    return getUpB(*std::max_element(figures.begin(), figures.end(),
      [](Polygon& cur, Polygon& biggestByY) { return getUpB(cur) < getUpB(biggestByY); })
    );
  }
}
