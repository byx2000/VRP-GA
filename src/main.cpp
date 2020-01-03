#include <iostream>
#include <fstream>
#include "Algo/VRP.h"

using namespace std;

int main()
{
	VRP vrp;

	ifstream fin("in.txt");

	int cNode;
	fin >> cNode;

	double x0, y0;
	fin >> x0 >> y0;
	vrp.addNode(x0, y0, 0.0);

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

	cout << vrp.toString() << endl;

	Result res = vrp.solve();

	cout << res.toString() << endl;

	return 0;
}