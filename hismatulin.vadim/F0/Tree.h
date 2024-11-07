#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <limits>
#include <stdexcept>

class Tree {
  std::map<std::string, std::set<int>> tree_;

public:
  using iterator = std::map<std::string, std::set<int>>::iterator;
  using const_iterator = std::map<std::string, std::set<int>>::const_iterator;

  Tree() = default;

  bool add(const std::string& word, int lineNumber);
  bool deleteWord(const std::string& word);
  const_iterator search(const std::string& word) const;

  size_t size() const;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
};

#endif
