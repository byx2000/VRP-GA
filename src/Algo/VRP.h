#pragma once

#include "../Util/Random.h"
#include "../Data/Node.h"
#include "../Data/Car.h"
#include "../Data/Result.h"
#include "Chrom.h"

#include <iostream>
#include <algorithm>

class VRP
{
public:
	VRP();
	void setDeparture(double x, double y);
	void addNode(double x, double y, double demand);
	void addCar(double capacity);
	Result solve();

private:
	int cNode, cCar;
	std::vector<Node> nodeInfo;
	std::vector<Car> carInfo;
	std::vector<std::vector<double>> dis;
};