#pragma once

#include "../Data/Node.h"
#include "../Data/Car.h"
#include "../Data/Result.h"

class Chrom
{
	friend class VRP;
public:
	Chrom(const VRP& vrp);
	void update();
	void mutation();
	double fitness() const;
	bool operator<(const Chrom& c) const;
	Chrom& operator=(const Chrom& c);
	void decode(Result& res) const;
	std::string toString() const;

private:
	const std::vector<Node>& nodeInfo;
	const std::vector<Car>& carInfo;
	const std::vector<std::vector<double>>& dis;
	double k1, k2, k3;

	std::vector<int> gene;
	std::vector<double> mileage, load;
	double time, length;
	int cnt;
	bool valid;
};