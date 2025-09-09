#include <iostream>
#include "Dictionary.h"
#include "utilities.h"

bool Dictionary::add(std::string& key, std::string& translation)
{
  mrkv::makeNormal(key);
  mrkv::makeNormal(translation);
  if (!mrkv::isCleanStr(key) || !mrkv::isCleanStr(translation) || key == "" || translation == "")
  {
    return false;
  }

  auto it = dict_.find(key);
  if (it != dict_.cend())
  {
    it->second.insert(translation);
  }
  else
  {
    std::set<std::string> translationsSet = { translation };
    dict_.insert({ key, translationsSet });
  }
  return true;
}

bool Dictionary::deleteWord(std::string& key)
{
  mrkv::makeNormal(key);
  return dict_.erase(key) != 0;
}

Dictionary::const_iterator Dictionary::search(std::string& key) const
{
  return dict_.find(key);
}

size_t Dictionary::size() const
{
  return dict_.size();
}

Dictionary::iterator Dictionary::begin()
{
  return dict_.begin();
}

Dictionary::iterator Dictionary::end()
{
  return dict_.end();
}

Dictionary::const_iterator Dictionary::cbegin() const
{
  return dict_.cbegin();
}

Dictionary::const_iterator Dictionary::cend() const
{
  return dict_.cend();
}
