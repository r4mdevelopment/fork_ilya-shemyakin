#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <map>
#include <set>

class Dictionary
{
  std::map<std::string, std::set<std::string>> dict_;
public:
  using iterator = std::map<std::string, std::set<std::string>>::iterator;
  using const_iterator = std::map<std::string, std::set<std::string>>::const_iterator;

  Dictionary() = default;

  bool add(std::string& key, std::string& translation);
  bool deleteWord(std::string& key);
  const_iterator search(std::string& key) const;

  size_t size() const;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
};
#endif
