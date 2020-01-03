#include "Chrom.h"
#include "../Util/Random.h"

#include <algorithm>
#include <iostream>

using namespace std;

Chrom::Chrom(const std::vector<Node>& nodeInfo, const std::vector<Car>& carInfo, const std::vector<std::vector<double>>& dis)
	: nodeInfo(nodeInfo), carInfo(carInfo), dis(dis)
{
	int cNode = nodeInfo.size() - 1;
	int cCar = carInfo.size();
	
	d.resize(cCar, 0.0);
	w.resize(cCar, 0.0);
	
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

	update();

	print();*/
}

void Chrom::update()
{
	for (int i = 0; i < (int)d.size(); ++i)
	{
		d[i] = w[i] = 0.0;
	}

	int iCar = 0;
	int last = 0;
	for (int i = 0; i < (int)gene.size(); ++i)
	{
		if (gene[i] == 0)
		{
			d[iCar] += dis[last][0];
			iCar++;
			last = 0;
		}
		else
		{
			d[iCar] += dis[last][gene[i]];
			w[iCar] += nodeInfo[gene[i]].demand;
			last = gene[i];
			if (w[iCar] > carInfo[iCar].capacity)
			{
				valid = false;
				return;
			}
		}
	}
	d[iCar] += dis[last][0];

	time = 0.0;
	length = 0.0;
	cnt = 0;
	for (int i = 0; i < (int)d.size(); ++i)
	{
		time = max(time, d[i]);
		length += d[i];
		if (fabs(d[i] - 0.0) > 1e-6)
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

double Chrom::fitness(double k1, double k2, double k3) const
{
	if (!valid)
		return 1e8;
	else
		return k1 * time + k2 * length + k3 * cnt;
}

bool Chrom::operator<(const Chrom& c) const
{
	double k1 = 100.0, k2 = 1.0, k3 = 1.0;
	return fitness(k1, k2, k3) < c.fitness(k1, k2, k3);
}

Chrom& Chrom::operator=(const Chrom& c)
{
	gene = c.gene;
	d = c.d;
	w = c.w;
	time = c.time;
	length = c.length;
	cnt = c.cnt;
	valid = c.valid;
	return *this;
}

Result Chrom::decode() const
{
	Result res;
	res.path.resize(carInfo.size());
	res.load = w;
	res.mileage = d;

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

	return res;
}

void Chrom::print() const
{
	int iCar = 0;
	cout << iCar + 1 << "号车：";
	for (int i = 0; i < (int)gene.size(); ++i)
	{
		if (gene[i] == 0)
		{
			cout << "\t载重量：" << w[iCar] << "\t核载：" << carInfo[iCar].capacity << "\t路程：" << d[iCar] << endl;
			iCar++;
			cout << iCar + 1 << "号车：";
		}
		else
		{
			cout << gene[i] << " ";
		}
	}
	cout << "\t载重量：" << w[iCar] << "\t核载：" << carInfo[iCar].capacity << "\t路程：" << d[iCar] << endl;

	if (valid)
	{
		cout << "时间：" << time << "\t";
		cout << "里程：" << length << "\t";
		cout << "车辆数：" << cnt << "\t";
	}
	else
	{
		cout << "不合法";
	}
	cout << endl << endl;
}