#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <stdexcept>
#include "Tree.h"

std::string removePunctuation(const std::string& word) {
  std::string cleanWord;
  std::remove_copy_if(word.begin(), word.end(), std::back_inserter(cleanWord), [](char ch) {
    return std::ispunct(static_cast<unsigned char>(ch));
    });
  return cleanWord;
}

void processLine(Tree& tree, const std::string& line, int lineNumber) {
  std::istringstream iss(line);
  std::string word;
  while (iss >> word) {
    word = removePunctuation(word);
    if (!word.empty()) {
      tree.add(word, lineNumber);
    }
  }
}

bool readFile(Tree& tree, const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    return false;
  }

  std::string line;
  int lineNumber = 1;
  while (std::getline(file, line)) {
    processLine(tree, line, lineNumber);
    lineNumber++;
  }
  file.close();
  return true;
}

void printTree(const Tree& tree) {
  if (tree.size() == 0) {
    std::cout << "<ÄÅÐÅÂÎ ÏÓÑÒÎ>" << std::endl;
    return;
  }

  for (auto it = tree.cbegin(); it != tree.cend(); ++it) {
    std::cout << it->first << ": ";
    for (int line : it->second) {
      std::cout << line << " ";
    }
    std::cout << std::endl;
  }
}

void help() {
  std::cout << "Äîñòóïíûå êîìàíäû:\n";
  std::cout << "  INPUT - Çàãðóçèòü ôàéë\n";
  std::cout << "  PRINT - Ïîêàçàòü äåðåâî\n";
  std::cout << "  ADD - Äîáàâèòü ñëîâî\n";
  std::cout << "  DELETE - Óäàëèòü ñëîâî\n";
  std::cout << "  SEARCH - Íàéòè ñëîâî\n";
  std::cout << "  HELP - Ïîêàçàòü ïîìîùü\n";
}

int main() {
  std::system("chcp 1251 > nul");
  setlocale(LC_ALL, "");
  Tree tree;
  std::cout << "Ïðîãðàììà: AVL ÄÅÐÅÂÎ ÑËÎÂ" << std::endl;
  std::cout << "Ââåäèòå HELP äëÿ èíôîðìàöèè î êîìàíäàõ." << std::endl;
  std::string cmd;
  while (!std::cin.eof()) {
    std::cout << "\n|> ";
    std::getline(std::cin, cmd);
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd == "input") {
      std::string filename;
      std::cout << "Ââåäèòå èìÿ ôàéëà: ";
      std::getline(std::cin, filename);
      if (!readFile(tree, filename)) {
        std::cerr << "<ÎØÈÁÊÀ ×ÒÅÍÈß ÔÀÉËÀ>" << std::endl;
      }
    }
    else if (cmd == "print") {
      printTree(tree);
    }
    else if (cmd == "add") {
      std::string word;
      std::string lineInput;
      std::cout << "Ââåäèòå ñëîâî: ";
      std::getline(std::cin, word);
      word = removePunctuation(word);
      if (word.empty()) {
        std::cerr << "<ÍÅÂÅÐÍÛÉ ÂÂÎÄ ÑËÎÂÀ>" << std::endl;
        continue;
      }
      std::cout << "Ââåäèòå íîìåð ñòðîêè: ";
      std::getline(std::cin, lineInput);
      try {
        int lineNumber = std::stoi(lineInput);
        tree.add(word, lineNumber);
      }
      catch (const std::invalid_argument&) {
        std::cerr << "<ÍÅÂÅÐÍÛÉ ÂÂÎÄ: ÎÆÈÄÀËÎÑÜ ×ÈÑËÎ>" << std::endl;
      }
      catch (const std::out_of_range&) {
        std::cerr << "<ÂÂÅÄÅÍÍÎÅ ×ÈÑËÎ ÂÛÕÎÄÈÒ ÇÀ ÏÐÅÄÅËÛ ÄÎÏÓÑÒÈÌÎÃÎ ÄÈÀÏÀÇÎÍÀ>" << std::endl;
      }
    }
    else if (cmd == "delete") {
      if (tree.size() == 0) {
        std::cout << "<ÄÅÐÅÂÎ ÏÓÑÒÎ>" << std::endl;
        continue;
      }
      std::string word;
      std::cout << "Ââåäèòå ñëîâî äëÿ óäàëåíèÿ: ";
      std::getline(std::cin, word);
      word = removePunctuation(word);
      if (!tree.deleteWord(word)) {
        std::cerr << "<ÑËÎÂÎ ÍÅ ÍÀÉÄÅÍÎ>" << std::endl;
      }
    }
    else if (cmd == "search") {
      if (tree.size() == 0) {
        std::cout << "<ÄÅÐÅÂÎ ÏÓÑÒÎ>" << std::endl;
        continue;
      }
      std::string word;
      std::cout << "Ââåäèòå ñëîâî äëÿ ïîèñêà: ";
      std::getline(std::cin, word);
      word = removePunctuation(word);
      auto it = tree.search(word);
      if (it != tree.cend()) {
        std::cout << it->first << ": ";
        for (int line : it->second) {
          std::cout << line << " ";
        }
        std::cout << std::endl;
      }
      else {
        std::cout << "<ÑËÎÂÎ ÍÅ ÍÀÉÄÅÍÎ>" << std::endl;
      }
    }
    else if (cmd == "help") {
      help();
    }
    else if (cmd != "" || cmd == "") {
      if (std::cin.eof()) {
        std::cout << "<ÇÀÂÅÐØÅÍÈÅ ÏÐÎÃÐÀÌÌÛ>" << std::endl;
      }
      else {
        std::cerr << "<ÍÅÈÇÂÅÑÒÍÀß ÊÎÌÀÍÄÀ>" << std::endl;
      }
    }
  }
  return 0;
}
