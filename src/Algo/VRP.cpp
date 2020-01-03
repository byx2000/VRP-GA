#include "VRP.h"

using namespace std;

VRP::VRP()
{
	cNode = 0;
	cCar = 0;
	nodeInfo.push_back(Node(0.0, 0.0, 0.0));
}

void VRP::setDeparture(double x, double y)
{
	nodeInfo[0] = Node(x, y, 0.0);
}

void VRP::addNode(double x, double y, double demand)
{
	nodeInfo.push_back(Node(x, y, demand));
	cNode++;
}

void VRP::addCar(double capacity)
{
	carInfo.push_back(Car(capacity));
	cCar++;
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
		Chrom c(nodeInfo, carInfo, dis);
		if (c.valid)
		{
			chroms.push_back(c);
		}
	}

	//遗传算法
	int cnt = 0;
	int c = 0;
	Chrom best(nodeInfo, carInfo, dis);
	while (1)
	{
		c++;
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

	cout << "进化代数：" << c << endl;

	//返回结果
	return best.decode();
}
