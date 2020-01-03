#include "Chrom.h"
#include "VRP.h"
#include "../Util/Random.h"

#include <algorithm>
#include <iostream>

using namespace std;

Chrom::Chrom(const VRP& vrp)
	: nodeInfo(vrp.nodeInfo), carInfo(vrp.carInfo), dis(vrp.dis)
{
	k1 = vrp.k1;
	k2 = vrp.k2;
	k3 = vrp.k3;

	int cNode = nodeInfo.size() - 1;
	int cCar = carInfo.size();
	
	mileage.resize(cCar, 0.0);
	load.resize(cCar, 0.0);
	
	for (int i = 0; i < cNode; ++i)
	{
		gene.push_back(i + 1);
	}
	
	Random::Shuffle(gene);

	int index = 0;
	for (int i = 0; i < cCar - 1; ++i)
	{
		double sum = 0.0;
		while (1)
		{
			if (index >= (int)gene.size())
			{
				break;
			}
			sum += nodeInfo[gene[index]].demand;
			if (sum > carInfo[i].capacity)
			{
				break;
			}
			index++;
		}

		gene.insert(gene.begin() + index, 0);
	}
	
	update();

	/*vector<int> p(cNode);
	for (int i = 0; i < cNode; ++i)
	{
		p[i] = i + 1;
	}
	Random::Shuffle(p);

	int iCar = 0, iNode = 0;
	double sum = 0.0;
	while (iCar < cCar - 1 && iNode < cNode)
	{
		if (sum > carInfo[iCar].capacity)
		{
			gene.push_back(0);
			iCar++;
			sum = 0.0;
		}
		else
		{
			gene.push_back(p[iNode]);
			sum += nodeInfo[p[iNode]].demand;
		}
		iNode++;
	}

	while (iCar < cCar - 1)
	{
		gene.push_back(0);
		iCar++;
	}

	update();*/
}

void Chrom::update()
{
	for (int i = 0; i < (int)mileage.size(); ++i)
	{
		mileage[i] = load[i] = 0.0;
	}

	int iCar = 0;
	int last = 0;
	for (int i = 0; i < (int)gene.size(); ++i)
	{
		if (gene[i] == 0)
		{
			mileage[iCar] += dis[last][0];
			iCar++;
			last = 0;
		}
		else
		{
			mileage[iCar] += dis[last][gene[i]];
			load[iCar] += nodeInfo[gene[i]].demand;
			last = gene[i];
			if (load[iCar] > carInfo[iCar].capacity)
			{
				valid = false;
				return;
			}
		}
	}
	mileage[iCar] += dis[last][0];

	time = 0.0;
	length = 0.0;
	cnt = 0;
	for (int i = 0; i < (int)mileage.size(); ++i)
	{
		time = max(time, mileage[i]);
		length += mileage[i];
		if (fabs(mileage[i] - 0.0) > 1e-6)
		{
			cnt++;
		}
	}

	valid = true;
}

void Chrom::mutation()
{
	int i = Random::UniformInt(0, gene.size() - 1);
	int j = Random::UniformInt(0, gene.size() - 1);
	swap(gene[i], gene[j]);
	double t_time = time;
	double t_length = length;
	int t_cnt = cnt;
	update();
	if (!valid)
	{
		swap(gene[i], gene[j]);
		time = t_time;
		length = t_length;
		cnt = t_cnt;
		valid = true;
	}
}

double Chrom::fitness() const
{
	if (!valid)
		return 1e8;
	else
		return k1 * time + k2 * length + k3 * cnt;
}

bool Chrom::operator<(const Chrom& c) const
{
	return fitness() < c.fitness();
}

Chrom& Chrom::operator=(const Chrom& c)
{
	gene = c.gene;
	mileage = c.mileage;
	load = c.load;
	time = c.time;
	length = c.length;
	cnt = c.cnt;
	valid = c.valid;
	return *this;
}

void Chrom::decode(Result& res) const
{
	res.path.resize(carInfo.size());
	res.load = load;
	res.mileage = mileage;

	int iCar = 0;
	for (int i = 0; i < (int)gene.size(); ++i)
	{
		if (gene[i] == 0)
		{
			iCar++;
		}
		else
		{
			res.path[iCar].push_back(gene[i]);
		}
	}
}

std::string Chrom::toString() const
{
	string s = "gene: ";
	for (int i = 0; i < (int)gene.size(); ++i)
	{
		s += to_string(gene[i]);
		s += " ";
	}
	return s;
}