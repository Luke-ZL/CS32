/*#include "Map.h"
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
}



#include "Map.h"
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
}



#include "Map.h"
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

#include "Map.h"
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

#include "Map.h"
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

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Map m;
	m.insert("A", 10);
	m.insert("B", 44);
	m.insert("C", 10);
	string all;
	double total = 0;
	for (int n = 0; n < m.size(); n++)
	{
		string k;
		double v;
		m.get(n, k, v);
		all += k;
		total += v;
	}
	cout << all << total;
}*/
#include "Map.h"
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

/*#include "Map.h"
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
}*/