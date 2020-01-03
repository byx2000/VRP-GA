#include "VRP.h"
#include "Chrom.h"

#include <algorithm>

using namespace std;

VRP::VRP()
{
	cNode = 0;
	cCar = 0;
	k1 = k2 = k3 = 1.0;
}

void VRP::addNode(double x, double y, double demand)
{
	nodeInfo.push_back(Node(cNode, x, y, demand));
	cNode++;
}

void VRP::addCar(double capacity)
{
	carInfo.push_back(Car(cCar, capacity));
	cCar++;
}

void VRP::setWeights(double k1, double k2, double k3)
{
	this->k1 = k1;
	this->k2 = k2;
	this->k3 = k3;
}

std::string VRP::toString() const
{
	string s = "Node info:\n";
	for (int i = 0; i < (int)nodeInfo.size(); ++i)
	{
		s += nodeInfo[i].toString();
		s += "\n";
	}

	s += "\nCar info:\n";
	for (int i = 0; i < (int)carInfo.size(); ++i)
	{
		s += carInfo[i].toString();
		s += "\n";
	}

	return s;
}

Result VRP::solve()
{
	//预处理所有点对的距离
	dis = vector<vector<double>>(cNode + 1, vector<double>(cNode + 1, 0.0));
	for (int i = 0; i <= cNode; ++i)
	{
		for (int j = 0; j <= cNode; ++j)
		{
			dis[i][j] =
				sqrt((nodeInfo[i].x - nodeInfo[j].x) * (nodeInfo[i].x - nodeInfo[j].x)
					+ (nodeInfo[i].y - nodeInfo[j].y) * (nodeInfo[i].y - nodeInfo[j].y));
		}
	}

	//初始化种群
	vector<Chrom> chroms;
	while (chroms.size() < 1000)
	{
		Chrom c(*this);
		if (c.valid)
		{
			chroms.push_back(c);
		}
	}

	//遗传算法
	int cnt = 0;
	int numGeneration = 0;
	Chrom best(*this);
	while (1)
	{
		numGeneration++;
		sort(chroms.begin(), chroms.end());
		if (chroms[0] < best)
		{
			best = chroms[0];
			cnt = 0;
		}
		else
		{
			cnt++;
		}

		if (cnt >= 1000)
		{
			break;
		}

		int cnt = chroms.size() / 2;
		for (int i = cnt; i < (int)chroms.size(); ++i)
		{
			chroms[i] = chroms[i - cnt];
			chroms[i].mutation();
		}
	}
	
	//对染色体进行解码
	Result res;
	best.decode(res);
	res.numGeneration = numGeneration;

	//返回结果
	return res;
}
