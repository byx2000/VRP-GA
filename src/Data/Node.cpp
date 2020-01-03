#include "Node.h"

using namespace std;

Node::Node(int id, double x, double y, double demand) : id(id), x(x), y(y), demand(demand)
{

}

std::string Node::toString() const
{
	string s = "";
	if (id == 0)
	{
		s += "Center";
	}
	else
	{
		s += "Node ";
		s += to_string(id);
	}
	s += ": \t position: (";
	s += to_string(x);
	s += ", ";
	s += to_string(y);
	s += ") \t";

	if (id != 0)
	{
		s += "demand: ";
		s += to_string(demand);
	}
	
	return s;
}
