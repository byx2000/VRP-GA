#include "Car.h"

using namespace std;

Car::Car(int id, double capacity, double disLimit) : id(id), capacity(capacity), disLimit(disLimit)
{

}

std::string Car::toString() const
{
	string s = "Car ";
	s += to_string(id);
	s += ":  \tcapacity: ";
	s += to_string(capacity);
	s += "\tdistance limit: ";
	s += to_string(disLimit);
	return s;
}
