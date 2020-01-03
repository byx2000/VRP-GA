#include "Car.h"

using namespace std;

Car::Car(int id, double capacity) : id(id), capacity(capacity)
{

}

std::string Car::toString() const
{
	string s = "Car ";
	s += to_string(id);
	s += ":  \tcapacity: ";
	s += to_string(capacity);
	return s;
}
