#pragma once

#include "../Data/Node.h"
#include "../Data/Car.h"
#include "../Data/Result.h"

struct Chrom
{
	const std::vector<Node>& nodeInfo;
	const std::vector<Car>& carInfo;
	const std::vector<std::vector<double>>& dis;

	std::vector<int> gene;
	std::vector<double> d, w;
	double time, length;
	int cnt;
	bool valid;

	Chrom(const std::vector<Node>& nodeInfo, const std::vector<Car>& carInfo, const std::vector<std::vector<double>>& dis);
	void update();
	void mutation();
	double fitness(double k1, double k2, double k3) const;
	bool operator<(const Chrom& c) const;
	Chrom& operator=(const Chrom& c);
	void decode(Result& res) const;
	void print() const;
};