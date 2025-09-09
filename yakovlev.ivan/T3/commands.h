#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include "figures.h"

namespace yakovlev
{
  int isArgANumber(const std::string& str);

  /// <summary>
  ///  ������ ����� ������� ����� � �������� ����������� ������ � � ������.
  /// </summary>
  /// <param name="figures - ������ �����"></param>
  /// <param name="arg - �������� EVEN/ODD/MEAN"></param>
  /// <returns></returns>
  double area(std::vector<Polygon>& figures, const std::string& arg);

  /// <summary>
  /// ������ ������������� �������� �������
  /// </summary>
  /// <param name="figures - ������ �����"></param>
  /// <returns></returns>
  double maxArea(std::vector<Polygon>& figures);

  /// <summary>
  /// ������ ������������� ���������� ������
  /// </summary>
  /// <param name="figures - ������ �����"></param>
  /// <returns></returns>
  int maxVertexes(std::vector<Polygon>& figures);

  /// <summary>
  /// ������ ������������ �������� �������
  /// </summary>
  /// <param name="figures - ������ �����"></param>
  /// <returns></returns>
  double minArea(std::vector<Polygon>& figures);

  /// <summary>
  /// ������ ������������ ���������� ������
  /// </summary>
  /// <param name="figures - ������ �����"></param>
  /// <returns></returns>
  int minVertexes(std::vector<Polygon>& figures);

  /// <summary>
  /// ������� ������������ ���������� �����, ����������� ����������(��� ���������) � ��������� � ����������
  /// </summary>
  /// <param name="figures - ������ ����� "></param>
  /// <param name="arg - �������� EVEN/ODD"></param>
  /// <returns></returns>
  int count(std::vector<Polygon>& figures, const std::string& arg);

  /// <summary>
  /// ������� ������������ ���������� ��������������� � ��������� �����
  /// </summary>
  /// <param name="figures - ������ �����"></param>
  /// <returns></returns>
  int rects(std::vector<Polygon>& figures);

  /// <summary>
  /// ������� ������������ ���������� �����, ����������� ����������(��� ���������) � ��������� � ����������
  /// </summary>
  /// <param name="polygons - ������ �����"></param>
  /// <param name="target - ������, � ������� ������ ����� ���������� ���������"></param>
  /// <returns></returns>
  int same(const std::vector<Polygon>& polygons, const Polygon& target);
}

#endif
