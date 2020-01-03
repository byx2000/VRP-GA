#pragma once

#include "../Data/Node.h"
#include "../Data/Car.h"
#include "../Data/Result.h"

class VRP
{
public:
	VRP();
	void addNode(double x, double y, double demand);
	void addCar(double capacity);
	std::string toString() const;
	Result solve();

private:
	int cNode, cCar;
	std::vector<Node> nodeInfo;
	std::vector<Car> carInfo;
	std::vector<std::vector<double>> dis;
};