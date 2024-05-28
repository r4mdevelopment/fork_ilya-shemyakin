#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <map>
#include <string>
#include <set>

class Dictionary
{
  std::map<std::string, std::set<std::string>> dic_;
public:
  Dictionary() = default;
  Dictionary(const Dictionary& other) = default;
  Dictionary(Dictionary&& other) noexcept = delete;
  ~Dictionary() = default;
  Dictionary& operator=(const Dictionary& other) = default;
  Dictionary& operator=(Dictionary&& other) noexcept = delete;

  bool add(std::string& key, std::string& translation);
  bool deleteWord(std::string& key);
  bool search(std::string& key) const;
  void print(std::ostream& out) const;
  bool printByKey(std::ostream& out, std::string& key) const;
  size_t size() const;
};
#endif
