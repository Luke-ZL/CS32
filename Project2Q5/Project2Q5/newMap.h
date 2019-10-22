#ifndef NEWMAP_H
#define NEWMAP_H

#include<string>
using namespace std;

const int DEFAULT_MAX_ITEMS = 250;

using KeyType = string;
using ValueType = double;


class Map
{
public:
	Map();
	Map(const Map& Mapp);
	Map(int Max);
	bool empty() const
	{
		return (count == 0);
	}
	int size() const
	{
		return count;
	}
	bool insert(const KeyType& key, const ValueType& value);
	bool update(const KeyType& key, const ValueType& value);
	bool insertOrUpdate(const KeyType& key, const ValueType& value);
	bool erase(const KeyType& key);
	bool contains(const KeyType& key) const;
	bool get(const KeyType& key, ValueType& value) const;
	bool get(int i, KeyType& key, ValueType& value) const;
	void swap(Map& other);
	~Map();
private:
	struct pair
	{
		KeyType Key;
		ValueType Value;
	};
	pair *pairs;
	int count,max;
};

#endif 
