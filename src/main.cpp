#include <iostream>
#include <fstream>
#include "Algo/VRP.h"

using namespace std;

int main()
{
	VRP vrp;
	vrp.readDataFromFile("in.txt");
	cout << vrp.toString() << endl;

	vrp.setWeights(100, 1, 1);
	Result res;
	vrp.solve(res);
	cout << res.toString() << endl;

	return 0;
}