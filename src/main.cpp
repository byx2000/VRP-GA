#include <iostream>
#include <fstream>
//#include "Algo/VRP.h"
#include "Export/Export.h"

using namespace std;

void Callback(int numCar, int** path, int* pathLen, double* load, double* mileage)
{
	for (int i = 0; i < numCar; ++i)
	{
		if (pathLen[i] > 0)
		{
			cout << "Car " << i << ":\t";
			for (int j = 0; j < pathLen[i]; ++j)
			{
				cout << path[i][j] << " ";
			}
			cout << "load: " << load[i] << " mileage: " << mileage[i];
			cout << endl;
		}
	}
}

int main()
{
	/*VRP vrp;
	vrp.readDataFromFile("in.txt");
	cout << vrp.toString() << endl;

	vrp.setWeights(100, 1, 1);
	Result res;
	vrp.solve(res);
	cout << res.toString() << endl;*/

	ifstream fin("in.txt");

	int cNode;
	fin >> cNode;
	double* x = new double[cNode + 1];
	double* y = new double[cNode + 1];
	double* demand = new double[cNode + 1];

	fin >> x[0] >> y[0];
	demand[0] = 0.0;
	for (int i = 0; i < cNode; ++i)
	{
		fin >> x[i + 1] >> y[i + 1] >> demand[i + 1];
	}

	int cCar;
	fin >> cCar;
	double* capacity = new double[cCar];
	double* disLimit = new double[cCar];

	for (int i = 0; i < cCar; ++i)
	{
		fin >> capacity[i] >> disLimit[i];
	}

	Solve(cNode + 1, x, y, demand, cCar, capacity, disLimit, 100, 1, 1, Callback);

	return 0;
}