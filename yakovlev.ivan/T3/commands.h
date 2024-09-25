#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include "figures.h"

namespace yakovlev
{
  int isArgANumber(const std::string& str);

  /// <summary>
  ///  Расчёт суммы площади фигур с нечётным количеством вершин и с чётным.
  /// </summary>
  /// <param name="figures - вектор фигур"></param>
  /// <param name="arg - аргумент EVEN/ODD/MEAN"></param>
  /// <returns></returns>
  double area(std::vector<Polygon>& figures, const std::string& arg);

  /// <summary>
  /// Расчёт максимального значения площади
  /// </summary>
  /// <param name="figures - вектор фигур"></param>
  /// <returns></returns>
  double maxArea(std::vector<Polygon>& figures);

  /// <summary>
  /// Расчёт максимального количества вершин
  /// </summary>
  /// <param name="figures - вектор фигур"></param>
  /// <returns></returns>
  int maxVertexes(std::vector<Polygon>& figures);

  /// <summary>
  /// Расчёт минимального значения площади
  /// </summary>
  /// <param name="figures - вектор фигур"></param>
  /// <returns></returns>
  double minArea(std::vector<Polygon>& figures);

  /// <summary>
  /// Расчёт минимального количества вершин
  /// </summary>
  /// <param name="figures - вектор фигур"></param>
  /// <returns></returns>
  int minVertexes(std::vector<Polygon>& figures);

  /// <summary>
  /// Команда подсчитывает количество фигур, совместимых наложением(без поворотов) с указанной в параметрах
  /// </summary>
  /// <param name="figures - вектор фигур "></param>
  /// <param name="arg - аргумент EVEN/ODD"></param>
  /// <returns></returns>
  int count(std::vector<Polygon>& figures, const std::string& arg);

  /// <summary>
  /// Команда подсчитывает количество прямоугольников в коллекции фигур
  /// </summary>
  /// <param name="figures - вектор фигур"></param>
  /// <returns></returns>
  int rects(std::vector<Polygon>& figures);

  /// <summary>
  /// Команда подсчитывает количество фигур, совместимых наложением(без поворотов) с указанной в параметрах
  /// </summary>
  /// <param name="polygons - вектор фигур"></param>
  /// <param name="target - фигура, с которой должно бьыть совместимо наложение"></param>
  /// <returns></returns>
  int same(const std::vector<Polygon>& polygons, const Polygon& target);
}

#endif
