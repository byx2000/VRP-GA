#include <iostream>
#include <fstream>
#include "VRP.h"

using namespace std;

int main()
{
	VRP vrp;

	ifstream fin("in.txt");

	int cNode;
	fin >> cNode;

	double x0, y0;
	fin >> x0 >> y0;
	vrp.setDeparture(x0, y0);

	for (int i = 0; i < cNode; ++i)
	{
		double x, y, d;
		fin >> x >> y >> d;
		vrp.addNode(x, y, d);
	}

	double cCar;
	fin >> cCar;

	for (int i = 0; i < cCar; ++i)
	{
		double w;
		fin >> w;
		vrp.addCar(w);
	}

	VRP::Result res = vrp.solve();

	double time = 0.0;
	double sum = 0.0;
	int cnt = 0;
	for (int i = 0; i < (int)res.path.size(); ++i)
	{
		cout << i + 1 << "�ų���";
		if (res.path[i].size() > 0)
		{
			cnt++;
			for (int j = 0; j < (int)res.path[i].size(); ++j)
			{
				cout << res.path[i][j] << " ";
			}
			cout << "��̣�" << res.mileage[i] << " ";
			cout << "���أ�" << res.load[i] << endl;
			time = max(time, res.mileage[i]);
			sum += res.mileage[i];
		}
		else
		{
			cout << "δʹ��" << endl;
		}
	}
	cout << "ʱ�䣺" << time << " ����̣�" << sum << " ��������" << cnt << endl;

	return 0;
}