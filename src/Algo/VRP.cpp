#include "VRP.h"

using namespace std;

VRP::VRP()
{
	cNode = 0;
	cCar = 0;
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
	//Ԥ�������е�Եľ���
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

	//��ʼ����Ⱥ
	vector<Chrom> chroms;
	while (chroms.size() < 1000)
	{
		Chrom c(nodeInfo, carInfo, dis);
		if (c.valid)
		{
			chroms.push_back(c);
		}
	}

	//�Ŵ��㷨
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
	
	Result res = best.decode();
	res.numGeneration = c;

	//���ؽ��
	return res;
}
