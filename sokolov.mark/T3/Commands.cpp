#include "Commands.h"

using namespace sokolov;
using namespace std::placeholders;

const std::string I_C = "<INVALID COMMAND>";

//Преобразование строки в число
int commands::convertToNumber(const std::string& str)
{
  char* end;
  //строку в число (10 - система счисления,
  //end - указатель на первый символ, который не был преобразован
  int convertedResult = strtol(str.c_str(), &end, 10);
  if (*end != 0)
  {
    return -1;
  }
  return convertedResult;
}

//Получение общей площади фигур в зависимости от аргумента
void commands::getFullArea(const std::vector<sokolov::Polygon>& polygons)
{
  std::string argument;
  std::cin >> argument;
  int number = convertToNumber(argument);
  auto accumulatePolygonsArea = //прибавление площади полигона к общей по нужным правилам
    [&polygons, &number](double accumulatedArea, const sokolov::Polygon& current, const std::string method)
    {
      double result = accumulatedArea;
      if (method == "EVEN" && current.points.size() % 2 == 0)
      {
        result += current.getArea();
      }
      else if (method == "ODD" && current.points.size() % 2 != 0)
      {
        result += current.getArea();
      }
      else if (method == "MEAN")
      {
        result += current.getArea();
      }
      else if (method == "SPECIAL" && current.points.size() == static_cast<size_t>(number))
      {
        result += current.getArea();
      }
      return result;
    };
  if (number == -1)
  {
    if (argument == "EVEN" || argument == "ODD")
    {
      std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0, //сложение площадей всех полигонов
        std::bind(accumulatePolygonsArea, _1, _2, argument)) << std::endl;
    }
    else if (argument == "MEAN" && polygons.size() != 0)
    {
      std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(accumulatePolygonsArea, _1, _2, argument)) / polygons.size() << std::endl;
    }
    else
    {
      throw I_C;
    }
  }
  else if (number > 2) //если аргумент цифра
  {
    std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
      std::bind(accumulatePolygonsArea, _1, _2, "SPECIAL")) << std::endl;
  }
  else
  {
    throw I_C;
  }
}

//вычисление минимальной площади/размера
void commands::getMin(const std::vector<sokolov::Polygon>& data)
{
  std::string arg;

  std::cin >> arg;

  if (data.size() == 0)
    throw I_C;

  std::vector<size_t> sizeVec(data.size());

  std::transform(data.begin(), data.end(), sizeVec.begin(),
    [](const Polygon& poly) { return poly.points.size(); }); //кол-во точек в полигоне
  auto poly = std::min_element(data.begin(), data.end());
  auto minSize = std::min_element(sizeVec.begin(), sizeVec.end()); //минимум точек у полигона

  if (arg == "AREA")
    std::cout << poly->getArea() << std::endl;
  else if (arg == "VERTEXES")
    std::cout << *minSize << std::endl;
  else
    throw I_C;
}

//вычисление максимальной площади/размера
void commands::getMax(const std::vector<sokolov::Polygon>& data)
{
  std::string arg;

  std::cin >> arg;

  if (data.size() == 0)
    throw I_C;

  std::vector<size_t> sizeVec(data.size());

  std::transform(data.begin(), data.end(), sizeVec.begin(),
    [](const Polygon& poly) { return poly.points.size(); }); //кол-во точек в полигоне
  auto poly = std::max_element(data.begin(), data.end());
  auto maxSize = std::max_element(sizeVec.begin(), sizeVec.end()); //максимум точек у полигона

  if (arg == "AREA")
    std::cout << poly->getArea() << std::endl;
  else if (arg == "VERTEXES")
    std::cout << *maxSize << std::endl;
  else
    throw I_C;
}

//вычисление количества фигур в зависимости от аргумента
void commands::countFigures(const std::vector<sokolov::Polygon>& polygons)
{
  std::string argument;
  std::cin >> argument;
  int number = convertToNumber(argument);

  //проходимся по полигонам и увеличиваем счетчик, если их размер подходит под условие
  auto count = [&number](const sokolov::Polygon& poly, const std::string& method)
    {
      if (method == "EVEN")
      {
        return poly.points.size() % 2 == 0;
      }
      else if (method == "ODD")
      {
        return poly.points.size() % 2 != 0;
      }
      else if (method == "SPECIAL")
      {
        return poly.points.size() == static_cast<size_t>(number);
      }
      return false;
    };

  if (number == -1)
  {
    if (argument == "EVEN" || argument == "ODD")
    {
      std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(count, _1, argument)) << std::endl;
    }
    else
    {
      throw I_C;
    }
  }
  else if (number > 2)
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(count, _1, "SPECIAL")) << std::endl;
  }
  else
  {
    throw I_C;
  }
}

//кол-во полигонов с площадью меньше, чем у полигона в параметре
void commands::lessarea(std::vector<sokolov::Polygon>& value)
{
  if (value.empty())
  {
    throw I_C;
  }

  sokolov::Polygon mainEl, otherEl;
  std::cin >> mainEl; //основной полигон
  int prov = std::cin.get(); //считать один символ
  for (;;) //while(true)
  {
    if (prov == int('\n') || prov == std::iostream::traits_type::eof()) //int('\n') -> \n в int
    {
      break;
    }
    if (!isspace(prov)) //проверка на пробельный символ
    {
      std::cin.setstate(std::ios_base::failbit);
      break;
    }
    prov = std::cin.get();
  }

  if (std::cin.fail())
  {
    std::cin.clear();
    throw I_C;
  }

  auto calcConcur = [&](const sokolov::Polygon tPolygon)
    {
      otherEl = tPolygon;
      bool rez = mainEl.getArea() > otherEl.getArea(); //подсчёт полигонов
      return rez;
    };
  std::cout << std::count_if(value.begin(), value.end(), calcConcur) << "\n";
}

//кол-во полигонов, с которыми пересекается
void commands::intersections(const std::vector<sokolov::Polygon>& data)
{
  Polygon trg;

  std::cin >> trg;

  int ch = std::cin.get();

  while (ch != int('\n') && ch != EOF)
  {
    if (!isspace(ch)) //
    {
      std::cin.setstate(std::istream::failbit);
      break;
    }
    ch = std::cin.get();
  }

  if (!std::cin)
  {
    std::cin.clear();
    throw I_C;
  }

  auto cntFunc = [&trg]
  (const Polygon& poly) //подсчёт, сколько полигонов пересекаются с заданным
    {
      return poly.isIntersect(trg);
    };

  std::cout << std::count_if(data.begin(), data.end(), cntFunc) << std::endl;
}
