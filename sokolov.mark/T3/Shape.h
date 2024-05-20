#ifndef SHAPE_H
#define SHAPE_H

namespace sokolov
{

  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

}

#endif
