#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "Shape.h"
#include "Commands.h"

//ERRORS

int main(int argc,char* argv[])
{
  if (argc != 2)
  {
	//error
	return EXIT_FAILURE;
  }

  //std::vector<*shape*> shapes;

  std::string filename = argv[1];
  std::ifstream fin(filename); //open file

  if (!fin.is_open())
  {
	//error
	return EXIT_FAILURE;
  }

  while (!fin.eof())
  {
	//считывание фигур
	//запись в вектор
  }

  std::cout << std::fixed;
  std::cout << std::setprecision(1);

  try
  {
	while (!std::cin.eof())
	{
	  std::string command;
	  std::cin >> command;

	  try
	  {
		//executing commands
	  }
	  catch (const std::string& err)
	  {
		std::cerr << err << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	  }
	}

	return EXIT_SUCCESS;
  }
  catch (...)
  {
	std::cerr << "ERROR!" << std::endl;
	return EXIT_FAILURE;
  }
}
