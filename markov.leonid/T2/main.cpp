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

  std::string line = "";

  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    DataStruct tmp;
    if (iss >> tmp)
    {
      data.push_back(tmp);
    }
  }

  std::sort(data.begin(), data.end(), compareDataStruct);

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );

  return 0;
}
