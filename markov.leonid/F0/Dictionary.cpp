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
  if (search(key))
  {
	dic_.find(key)->second.insert(translation);
  }
  else
  {
	std::set<std::string> translationsSet;
	translationsSet.insert(translation);
	dic_.insert({ key, translationsSet });
  }
  return true;
}

bool Dictionary::deleteWord(std::string& key)
{
  mrkv::makeNormal(key);
  if (!search(key))
  {
	return false;
  }
  dic_.erase(key);
  return true;
}

bool Dictionary::search(std::string& key) const
{
  return (dic_.find(key) != dic_.end());
}

void Dictionary::print(std::ostream& out) const
{
  for (const auto& i : dic_)
  {
	out << i.first << " -";
	int k = 0;
	for (const auto& j : i.second)
	{
	  if (i.second.size() - 1 == k)
	  {
		out << " " << j;
	  }
	  else
	  {
		out << " " << j << ",";
	  }
	  ++k;
	}
	out << "\n";
  }
}

bool Dictionary::printByKey(std::ostream& out, std::string& key) const
{
  mrkv::makeNormal(key);
  if (search(key))
  {
	out << key << " -";
	int k = 0;
	for(const auto& i : dic_.find(key)->second)
	{
	  if (dic_.find(key)->second.size() - 1 == k)
	  {
		out << " " << i;
	  }
	  else
	  {
		out << " " << i << ",";
	  }
	  ++k;
	}
	out << "\n";
	return true;
  }
  else
  {
	return false;
  }
}

size_t Dictionary::size() const
{
  return dic_.size();
}
