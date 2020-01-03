#pragma once

#include "../Data/Node.h"
#include "../Data/Car.h"
#include "../Data/Result.h"

class VRP
{
	friend class Chrom;
public:
	VRP();
	void readDataFromFile(const std::string& filename);
	void addNode(double x, double y, double demand);
	void addCar(double capacity, double disLimit);
	void setWeights(double k1, double k2, double k3);
	std::string toString() const;
	void solve(Result& res);

private:
	int cNode, cCar;
	std::vector<Node> nodeInfo;
	std::vector<Car> carInfo;
	std::vector<std::vector<double>> dis;
	double k1, k2, k3;
};