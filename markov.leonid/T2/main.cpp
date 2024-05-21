#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.h"

int main()
{
  using mrkv::DataStruct;
  using mrkv::compareDataStruct;
  std::vector<DataStruct> data;

  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::copy(
      std::istream_iterator<DataStruct>(std::cin),
      std::istream_iterator<DataStruct>(),
      std::back_inserter(data)
    );
  }

  std::sort(data.begin(), data.end(), compareDataStruct);

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );

  return 0;
}
