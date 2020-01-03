#pragma once

#include "../Data/Node.h"
#include "../Data/Car.h"
#include "../Data/Result.h"

class VRP
{
	friend class Chrom;
public:
	VRP();
	void addNode(double x, double y, double demand);
	void addCar(double capacity);
	void setWeights(double k1, double k2, double k3);
	std::string toString() const;
	Result solve();

private:
	int cNode, cCar;
	std::vector<Node> nodeInfo;
	std::vector<Car> carInfo;
	std::vector<std::vector<double>> dis;
	double k1, k2, k3;
};