#include "VRP.h"
#include "Chrom.h"

#include <algorithm>
#include <fstream>

using namespace std;

VRP::VRP()
{
	cNode = 0;
	cCar = 0;
	k1 = k2 = k3 = 1.0;
}

void VRP::readDataFromFile(const std::string& filename)
{
	//打开文件
	ifstream fin(filename);
	if (!fin)
	{
		throw string("Open file failed!") + filename;
	}

	nodeInfo.clear();
	carInfo.clear();

	//读入配送点数
	fin >> cNode;

	//读入原点
	double x0, y0;
	fin >> x0 >> y0;
	nodeInfo.push_back(Node(0, x0, y0, 0.0));

	//读入所有配送点
	for (int i = 0; i < cNode; ++i)
	{
		double x, y, d;
		fin >> x >> y >> d;
		nodeInfo.push_back(Node(i + 1, x, y, d));
	}

	//读入车辆数
	fin >> cCar;

	//读入所有车辆
	for (int i = 0; i < cCar; ++i)
	{
		double w, d;
		fin >> w >> d;
		carInfo.push_back(Car(i, w, d));
	}
}

void VRP::addNode(double x, double y, double demand)
{
	nodeInfo.push_back(Node(cNode, x, y, demand));
	cNode++;
}

void VRP::addCar(double capacity, double disLimit)
{
	carInfo.push_back(Car(cCar, capacity, disLimit));
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

void VRP::solve(Result& res)
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
	best.decode(res);
	res.numGeneration = numGeneration;
}
