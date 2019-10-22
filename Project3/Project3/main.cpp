/*#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Map m1;
	assert(m1.insert("Fred", 123));
	assert(m1.insert("Ethel", 456));
	assert(m1.size() == 2);   
	m1.insert("Lucy", 789);
	assert(m1.size() == 3);    //test insert and size
	Map m2;
	m2 = m1;  //test = for more than 1 nodes
	assert(m2.size() == 3);
	ValueType v = 42;  
	ValueType v1;
	assert(!m1.get("Luke", v) && v == 42);  
	assert(m1.get("Fred", v) && v == 123);  //test get function
	Map m3;
	assert(!m3.get("Lucy", v) && v == 123);   //test get function for an empty list
	assert(m1.size() == 3);
	m2 = m3;   //test = operator for empty lists
	assert(m2.size() == 0);
	assert(m2.insert("Fred", 123)); 
	m3 = m2;                   //test = for 1 node
	assert(m3.size() == 1);
	Map m4(m1);         //test copy constructor for more than 1 nodes
	assert(m4.size() == 3);
	Map m5;
	Map m6(m5);  
	assert(m5.size() == 0 && m6.size() == 0); //test copy constructor for empty list
	m1 = m1;  //test copy constructor for two same Maps
    assert(m1.size() == 3);
	KeyType k = "Luke";
	assert(!m1.get(-1, k, v)&& k == "Luke" && v == 123); //invalid i for get(3-arg)
	assert(m1.get(0, k, v) && k == "Fred" && v == 123); //test get(3-arg) 
	assert(!m5.get(0, k, v) && k == "Fred" && v == 123); //test get(3-arg) for empty list
	assert(m3.get(0, k, v) && k == "Fred" && v == 123); //test get(3-arg) for on-node list
	assert(!m5.update(k, v)); //test update for empty nodes
	assert(m1.update(k, 1234) && m1.get(k,v1) && v1 == 1234); //test update for list with more than 1 nodes
	assert(m3.update(k, 12345) && m3.get(k, v1) && v1 == 12345); //test update for list with 1 node
	assert(m1.insertOrUpdate(k, 123) && m1.get(k, v1) && v1 == 123); //test insertorupdate for list with more than 1 nodes;
	assert(m5.insertOrUpdate(k, 123) && m5.get(k, v1) && v1 == 123);//test insertorupdate for an empty list
	assert(m3.insertOrUpdate("Lucy", 1234) && m3.get("Lucy", v1) && v1 == 1234 &&m3.size()==2);//test insertorupdate for a list with 1 node
	Map m7;
	assert(!m7.erase(k)); //test erase for an empty list
	assert(m5.erase(k) && m5.size() == 0); //test erase for 1-node list
	m2 = m1;
	assert(m2.erase(k)&& m2.get("Ethel", v1)&& m2.get("Lucy", v1)); //test erase for 1st node
	m2 = m1;
	assert(m2.erase("Ethel")&& m2.get("Fred", v1)&& m2.get("Lucy", v1));//test erase for 2st node
	m2 = m1;
	assert(m2.erase("Lucy")&& m2.get("Fred", v1)&& m2.get("Ethel", v1));//test erase for last node
	m2 = m1;
	assert(!m2.erase("Luke")&& m2.size() == 3); //test erase for non-existing node
	assert(!m7.contains(k)); 
	assert(m1.contains("Lucy"));
	assert(!m1.contains("Luke"));//test contains
	m7.swap(m1);
	assert( m7.size() == 3 && m1.size() == 0);
	m7.swap(m1);
	assert(m7.size() == 0 && m1.size() == 3); //test swap between empty and non-empty lists
	m1.swap(m1);
	assert(m1.size() == 3 && m1.get(2, k, v) && k == "Lucy"); //test swap for the same list
	m3.swap(m1);
	assert(m3.size() == 3 && m1.size() == 2);
	m3.swap(m1);
	m2 = m1;
	combine(m1, m2, m7);
	assert(m7.size() == 3); //test combine for two same lists
	m2.update("Fred", 1234);
	m2.insert("Luke", 123);

	assert(!combine(m1, m2, m7)); //test combine for false output

	Map m8,m9;
	assert(combine(m8, m9, m7) && m7.size() == 0); //test combine for two empty lists;
	assert(!combine(m2, m1, m7));
	Map m10;
	m10.insert("RUA", 123);
	assert(combine(m10, m1, m7));
	assert(combine(m1, m10, m7)); //see sequence of output
	Map m11;
	assert(combine(m11, m1, m7));
	assert(combine(m1, m11, m7)); //combine 1 empty with 1 with nodes

	subtract(m2, m1, m7);
	assert(m7.size() == 1);
	
	subtract(m1, m2, m7);
	assert(m7.size() == 0); //test subtract
	subtract(m1, m11, m7);
	assert(m7.size() == 3);
	subtract(m11, m1, m7);
	assert(m7.size() == 0);//test subtract with empty lists
	m3 = m1;
	subtract(m1, m3, m7);
	assert(m7.size() == 0);//test subtract with same lists

}



#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Map m;
	assert(m.insert("Fred", 123));
	assert(m.insert("Ethel", 456));
	assert(m.size() == 2);
	ValueType v = 42;
	assert(!m.get("Lucy", v) && v == 42);
	assert(m.get("Fred", v) && v == 123);
	v = 42;
	KeyType x = "Lucy";
	assert(m.get(0, x, v) &&
		((x == "Fred"  &&  v == 123) || (x == "Ethel"  &&  v == 456)));
	KeyType x2 = "Ricky";
	assert(m.get(1, x2, v) &&
		((x2 == "Fred"  &&  v == 123) || (x2 == "Ethel"  &&  v == 456)) &&
		x != x2);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Map m;  // maps strings to doubles
	assert(m.empty());
	ValueType v = -1234.5;
	assert(!m.get("abc", v) && v == -1234.5); // v unchanged by get failure
	m.insert("xyz", 9876.5);
	assert(m.size() == 1);
	KeyType k = "hello";
	assert(m.get(0, k, v) && k == "xyz"  &&  v == 9876.5);
	Map a, b;
	a.insert("abc", 1);
	a.insert("dce", 2);
	b.insert("fgh", 3);
	a.swap(b);
	assert((a.size() == 1) && (b.size() == 2));
	ValueType v1;
	KeyType k1;
	assert(b.get(1, k1, v1) && k1 == "dce" && v1 == 2);
	assert(!b.get(2, k1, v1));
	assert(!b.get(-1, k1, v1));
	cout << "Passed all tests" << endl;
}

#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Map m;
	assert(m.insert(10, "diez"));
	assert(m.insert(20, "veinte"));
	assert(m.size() == 2);
	ValueType v = "cuarenta y dos";
	assert(!m.get(30, v) && v == "cuarenta y dos");
	assert(m.get(10, v) && v == "diez");
	v = "cuarenta y dos";
	KeyType x = 30;
	assert(m.get(0, x, v) &&
		((x == 10 && v == "diez") || (x == 20 && v == "veinte")));
	KeyType x2 = 40;
	assert(m.get(1, x2, v) &&
		((x2 == 10 && v == "diez") || (x2 == 20 && v == "veinte")) &&
		x != x2);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}
#include "Map.h"
#include <type_traits>
#include<iostream>

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
	"Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
	"Map must be copy-constructible.");

void ThisFunctionWillNeverBeCalled()
{
	CHECKTYPE(&Map::operator=, Map& (Map::*)(const Map&));
	CHECKTYPE(&Map::empty, bool (Map::*)() const);
	CHECKTYPE(&Map::size, int  (Map::*)() const);
	CHECKTYPE(&Map::insert, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::update, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::erase, bool (Map::*)(const KeyType&));
	CHECKTYPE(&Map::contains, bool (Map::*)(const KeyType&) const);
	CHECKTYPE(&Map::get, bool (Map::*)(const KeyType&, ValueType&) const);
	CHECKTYPE(&Map::get, bool (Map::*)(int, KeyType&, ValueType&) const);
	CHECKTYPE(&Map::swap, void (Map::*)(Map&));

	CHECKTYPE(combine, bool(*)(const Map&, const Map&, Map&));
	CHECKTYPE(subtract, void(*)(const Map&, const Map&, Map&));
}

int main()
{
	cout << "hi";
}*/

#include "Map.h"
#include <cassert>
#include<iostream>
using namespace std;
int main() {
	Map m;
	assert(m.empty()); //checking empty function
	assert(m.insert("A", 1)); //checking insert function
	assert(!m.empty());
	assert(!m.insert("A", 1)); //checking insert with a duplicate key
	assert(m.insert("B", 2));
	assert(m.insert("C", 3));
	assert(m.size() == 3); //checking size
	assert(m.contains("A")); //checking contains
	assert(!m.contains("D"));
	assert(m.update("B", 4)); //checking update
	assert(m.insertOrUpdate("D", 4));//checking insert or update 
	assert(m.insertOrUpdate("D", 5));
	assert(!m.erase("E")); //checking erase
	assert(m.erase("A"));

	assert(m.erase("C"));

	assert(m.erase("D"));
	assert(m.insert("E", 5));// checking insert works after erase
	assert(m.insert("F", 6));
	double v = 0;
	string k = "Z";
	assert(!m.get("A", v) && v == 0); //checking the first get
	assert(m.get("F", v) && v == 6);
	assert(m.size() == 3);
	assert(!m.get(3, k, v) && v == 6 && k == "Z"); //checking the second get
	assert(m.get(0, k, v) && v == 4 && k == "B");
	assert(m.get(1, k, v) && v == 5 && k == "E");
	assert(m.get(2, k, v) && v == 6 && k == "F");

	Map m2(m); //copy constructor works
	assert(m2.insert("G", 7)); //making sure that the new map is new and doesnt just point to the old one
	m = m2; //equal operator works
	assert(m2.erase("B")); //making sure the new map is new and doesnt just point to the old one

	Map m3;
	assert(m3.insert("X", 10));
	assert(m3.insert("Y", 15));
	assert(m3.insert("H", 17));
	assert(m3.insert("Z", 20));

	assert(combine(m, m2, m3));  //checking combine

	assert(m2.update("G", 9));
	assert(!combine(m, m2, m3)); //checking combine
	assert(m2.erase("E"));
	assert(m2.insert("X", 9));

	subtract(m, m2, m3); //checking subtract

	m.swap(m2); //checking swap

	cout << "hi";
}