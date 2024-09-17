#include "Tree.h"
#include <algorithm>

bool Tree::add(const std::string& word, int lineNumber) {
  std::string key = word;
  std::transform(key.begin(), key.end(), key.begin(), ::tolower);
  auto it = tree_.find(key);
  if (it != tree_.end()) {
    it->second.insert(lineNumber);
  }
  else {
    tree_.insert({ key, {lineNumber} });
  }
  return true;
}

bool Tree::deleteWord(const std::string& word) {
  std::string key = word;
  std::transform(key.begin(), key.end(), key.begin(), ::tolower);
  return tree_.erase(key) != 0;
}

Tree::const_iterator Tree::search(const std::string& word) const {
  std::string key = word;
  std::transform(key.begin(), key.end(), key.begin(), ::tolower);
  return tree_.find(key);
}

size_t Tree::size() const {
  return tree_.size();
}

Tree::iterator Tree::begin() {
  return tree_.begin();
}

Tree::iterator Tree::end() {
  return tree_.end();
}

Tree::const_iterator Tree::cbegin() const {
  return tree_.cbegin();
}

Tree::const_iterator Tree::cend() const {
  return tree_.cend();
}
