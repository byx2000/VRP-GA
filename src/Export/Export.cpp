#include "Export.h"
#include "../Algo/VRP.h"

#include <iostream>

using namespace std;

void Solve(int numNode, double* x, double* y, double* demand, int numCar, double* capacity, double* disLimit, double k1, double k2, double k3, void(*Callback)(int numCar, int** path, int* pathLen, double* load, double* mileage))
{
	VRP vrp;

	//添加原点和配送点
	for (int i = 0; i < numNode; ++i)
	{
		vrp.addNode(x[i], y[i], demand[i]);
	}

	//添加车辆
	for (int i = 0; i < numCar; ++i)
	{
		vrp.addCar(capacity[i], disLimit[i]);
	}

	//设置权重
	vrp.setWeights(k1, k2, k3);

	//求解
	Result res;
	vrp.solve(res);

	cout << res.toString() << endl;

	//获取结果
	int** path = new int*[numCar];
	int* pathLen = new int[numCar];
	double* load = new double[numCar];
	double* mileage = new double[numCar];

	for (int i = 0; i < numCar; ++i)
	{
		int cNode = res.path[i].size();
		path[i] = new int[cNode];
		for (int j = 0; j < cNode; ++j)
		{
			path[i][j] = res.path[i][j];
		}
		pathLen[i] = cNode;
		load[i] = res.load[i];
		mileage[i] = res.mileage[i];
	}

	//回调函数
	Callback(numCar, path, pathLen, load, mileage);

	//释放资源
	for (int i = 0; i < numCar; ++i)
	{
		delete[] path[i];
	}
	delete[] path;
	delete[] pathLen;
	delete[] load;
	delete[] mileage;
}
