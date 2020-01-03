#pragma once

#include <string>

struct Node
{
	int id;
	double x, y;
	double demand;
	Node(int id, double x, double y, double demand);
	std::string toString() const;
};