#include"Map.h"
using namespace std;

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (count >= DEFAULT_MAX_ITEMS) return false;
	for (int i = 0; i < count; i++)
		if (key == pairs[i].Key) return false;
	pairs[count].Key = key;
	pairs[count].Value = value;
	count++;
	return true;
}
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).

bool Map::update(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < count; i++)
		if (key == pairs[i].Key) 
		{
			pairs[i].Value = value;
			return true;
		}
	return false;	                     
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < count; i++)
		if (key == pairs[i].Key)
		{
			pairs[i].Value = value;
			return true;
		}
	if (count >= DEFAULT_MAX_ITEMS) return false;
	pairs[count].Key = key;
	pairs[count].Value = value;
	count++;
	return true;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).

bool Map::erase(const KeyType& key)
{
	for (int i = 0; i < count; i++)
		if (key == pairs[i].Key)
		{
			for (int j = i; j < count - 1; j++)
				pairs[j] = pairs[j + 1];
			count--;
			return true;
		}
	return false;
}
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.

bool Map::contains(const KeyType& key) const
{
	for (int i = 0; i < count; i++)
		if (key == pairs[i].Key) return true;
	return false;
}
// Return true if key is equal to a key currently in the map, otherwise
// false.

bool Map::get(const KeyType& key, ValueType& value) const
{
	for (int i = 0; i < count; i++)
		if (key == pairs[i].Key)
		{
			value = pairs[i].Value;
			return true;
		}
	return false;
}
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if ((0 > i) || (i >= count)) return false;
	key = pairs[i].Key;
	value = pairs[i].Value;
	return true;
}
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)

void Map::swap(Map& other)
{
	pair tmp;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		tmp = other.pairs[i];
		other.pairs[i] = pairs[i];
		pairs[i] = tmp;
	}
	int ctmp;
	ctmp = count;
	count = other.count;
	other.count = ctmp;
}
// Exchange the contents of this map with the other one.