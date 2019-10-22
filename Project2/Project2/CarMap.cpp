#include"CarMap.h"
#include<iostream>

bool CarMap::addCar(std::string license)
{
	return CM.insert(license, 0);
}
// If a car with the given license plate is not currently in the map, 
// and there is room in the map, add an entry for that car recording
// that it has 0 gallons of gas in it, and return true.  Otherwise,
// make no change to the map and return false.

double CarMap::gas(std::string license) const
{
	double vol;
	if (CM.get(license,vol)) return vol;
	else return -1;
}
// If a car with the given license plate is in the map, return the
// number of gallons of gas in its tank; otherwise, return -1.

bool CarMap::addGas(std::string license, double gallons)
{
	if (gallons < 0) return false;
	return CM.update(license, gallons + gas(license));
}
// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.

bool CarMap::useGas(std::string license, double gallons)
{
	if ((gallons > gas(license)) || (gallons < 0)) return false;
	return CM.update(license, gas(license) - gallons);
}
// If no car with the given license plate is in the map or if
// gallons is negative or if gallons > gas(), make no change to the
// map and return false.  Otherwise, decrease the number of gallons
// of gas in the indicated car by the gallons parameter and return
// true.

void CarMap::print() const
{
	std::string lis;
	double gas;
	for (int i = 0; i < fleetSize(); i++)
	{
		CM.get(i, lis, gas);
		cout << lis << " " << gas << endl;
	}
}
// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.

