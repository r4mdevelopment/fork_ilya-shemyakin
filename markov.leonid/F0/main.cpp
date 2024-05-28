#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "Dictionary.h"
#include "utilities.h"

int main()
{
  setlocale(LC_ALL, "");

  Dictionary dictionary;

  std::cout << "---ENG-RUS DICTIONARY---" << std::endl;
  std::cout << "Use HELP for information" << std::endl;

  while (!std::cin.eof())
  {
    std::cout << "\n$";
    std::string cmd = "";
    std::cin >> cmd;
    try
    {
      if (cmd == "INPUT")
      {
        std::string filename;
        std::cin >> filename;
        std::ifstream file(filename);
        if (!file.is_open())
        {
          std::cerr << "<FSTREAM ERROR>" << std::endl;
          continue;
        }

        std::string line = "", word = "", translationsStr = "";
        while (std::getline(file, line))
        {
          std::istringstream iss(line);
          if (!(std::getline(iss, word, '-') && std::getline(iss, translationsStr)))
          {
            std::cerr << "<READ ERROR>" << std::endl;
            continue;
          }
          mrkv::readTranslations(dictionary, word, translationsStr);
        }
        file.close();
      }
      else if (cmd == "PRINT")
      {
        dictionary.print(std::cout);
      }
      else if (cmd == "HELP")
      {
        mrkv::help(std::cout);
      }
      else if (cmd == "STAT")
      {
        std::cout << "Number of words: " << dictionary.size() << std::endl;
      }
      else if (cmd == "ADD")
      {
        std::string word = "";
        std::getline(std::cin, word);

        std::string translation = "";
        std::cout << "Enter the translation: ";
        std::getline(std::cin, translation);
        if (!dictionary.add(word, translation))
        {
          std::cout << "<INPUT ERROR>" << std::endl;
        }
      }
      else if (cmd == "DELETE")
      {
        std::string word = "";
        std::getline(std::cin, word);
        if (!dictionary.deleteWord(word))
        {
          std::cout << "<WORD DOESN'T EXIST>" << std::endl;
        }
      }
      else if (cmd == "FIND")
      {
        std::string word = "";
        std::getline(std::cin, word);
        if (!dictionary.printByKey(std::cout, word))
        {
          std::cout << "<WORD DOESN'T EXIST>" << std::endl;
        }
      }
      else if (cmd == "OUTPUT")
      {
        std::string filename;
        std::cin >> filename;
        std::ofstream file(filename);
        dictionary.print(file);
        file.close();
      }
      else if (cmd != "")
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << e.what() << std::endl;
      std::cin.clear();
      std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
  }
  return 0;
}
