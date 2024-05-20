#include "datastruct_hismatulin.h"

using hismatulin::DataStruct;

int main()
{
  // ULL LIT CMP LSP
  try
  {
    std::string input = "";
    std::vector<DataStruct> data;

    while (!std::cin.eof())
    {
      std::copy(
        std::istream_iterator<DataStruct>(std::cin), // итератор начала потока
        std::istream_iterator<DataStruct>(), // итератор конца потока (без параметров т.к. обозначается конец потока)
        std::back_inserter(data) // создает итератор, который добавляет значение в конец контейнера с помощью push_back
      );
      if (std::cin.fail() && !std::cin.eof()) // если произошла ошибка ввода или конец файла
      {
        std::cin.clear(); // чистим ошибки, из-за некорректного ввода
      }
    }
    
    std::sort(std::begin(data), std::end(data), hismatulin::compareDataStruct);

    std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator<DataStruct>(std::cout, "\n")
    );
  }
  catch (std::exception& ex)
  {
    std::cerr << ex.what();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
