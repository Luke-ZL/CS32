#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;
int main()
{
	CarMap c;  // maps ints to strings
	assert(c.fleetSize() == 0);
	c.addCar("RUA");
	c.addCar("");
	c.addCar("R");
	c.addCar("RU");
	assert(c.fleetSize() == 4 && c.gas("RUA") == 0 && c.gas("") == 0);
	c.addGas("RUA", -10);
	assert(c.gas("RUA") == 0);
	c.addGas("RUA", 10);
	c.addGas("", 10);
	assert(c.gas("RUA") == 10 && c.gas("") == 10);
	c.useGas("", 20);
	c.useGas("RUA", 10);
	assert(c.gas("RUA") == 0 && c.gas("") == 10);
	c.useGas("", -5);
	c.addGas("RUA", 100);
	c.useGas("RUA", 5);
	assert(c.gas("RUA") == 95 && c.gas("") == 10);
	c.print();
}