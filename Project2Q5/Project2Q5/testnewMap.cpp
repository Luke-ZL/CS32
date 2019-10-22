#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
Map a(1000);   // a can hold at most 1000 key/value pairs
Map b(5);      // b can hold at most 5 key/value pairs
Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
KeyType k[6] = {"aa", "bb", "cc", "dd", "ee", "ff" };
ValueType v = 10;
KeyType k1;
ValueType v1;

// No failures inserting pairs with 5 distinct keys into b
for (int n = 0; n < 5; n++)
	assert(b.insert(k[n], v));

// Failure if we try to insert a pair with a sixth distinct key into b
assert(!b.insert(k[5], v));

// When two Maps' contents are swapped, their capacities are swapped
// as well:
a.swap(b);
assert(!a.insert(k[5], v) && b.insert(k[5], v));
a.erase(k[3]);
assert(a.size() == 4);
a.insertOrUpdate(k[4], 15);
assert(a.size() == 4 && a.get(3, k1, v1) && v1 == 15 && k1 == "ee");
a.insertOrUpdate(k[3], 15);
assert(a.size() == 5 && a.get(4, k1, v1) && v1 == 15 && k1 == "dd");
assert(!a.get("", v1));
assert(a.get(k[0], v1) && v1 == 10);
cout << "Passed all tests" << endl;
}



/*#include "newMap.h"
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


#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
Map m;  // maps ints to strings
assert(m.empty());
ValueType v = "Ouch";
assert(!m.get(42, v) && v == "Ouch"); // v unchanged by get failure
m.insert(123456789, "Wow!");
assert(m.size() == 1);
KeyType k = 9876543;
assert(m.get(0, k, v) && k == 123456789 && v == "Wow!");
cout << "Passed all tests" << endl;
}*/




/*#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
Map gpas;
gpas.insert("Fred", 2.956);
gpas.insert("Ethel", 3.538);
double v;
string k1;
assert(gpas.get(1, k1, v) && (k1 == "Fred" || k1 == "Ethel"));
string k2;
assert(gpas.get(1, k2, v) && k2 == k1);
cout << "Passed all tests" << endl;
}




#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
Map gpas;
gpas.insert("Fred", 2.956);
assert(!gpas.contains(""));
gpas.insert("Ethel", 3.538);
gpas.insert("", 4.000);
gpas.insert("Lucy", 2.956);
assert(gpas.contains(""));
gpas.erase("Lucy");
assert(gpas.size() == 3 && gpas.contains("Fred") && gpas.contains("Ethel") &&
gpas.contains(""));
cout << "Passed all tests" << endl;
}


#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
Map m1;
m1.insert("Fred", 2.956);
Map m2;
m2.insert("Ethel", 3.538);
m2.insert("Lucy", 2.956);
m1.swap(m2);
assert(m1.size() == 2 && m1.contains("Ethel") && m1.contains("Lucy") &&
m2.size() == 1 && m2.contains("Fred"));
cout << "Passed all tests" << endl;
}
#include "newMap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Map m;
	assert(m.insert("Fred", 2.956));
	assert(m.insert("Ethel", 3.538));
	assert(m.size() == 2);
	ValueType v = 42;
	assert(!m.get("Lucy", v) && v == 42);
	assert(m.get("Fred", v) && v == 2.956);
	v = 42;
	KeyType x = "Lucy";
	assert(m.get(0, x, v) &&
		((x == "Fred"  &&  v == 2.956) || (x == "Ethel"  &&  v == 3.538)));
	KeyType x2 = "Ricky";
	assert(m.get(1, x2, v) &&
		((x2 == "Fred"  &&  v == 2.956) || (x2 == "Ethel"  &&  v == 3.538)) &&
		x != x2);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}


#include "newMap.h"
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

#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	cout << "hi" << endl;
	Map m(-1);
	cout << "hihi" << endl;
}*/