#pragma once

void Solve(int numNode, double* x, double* y, double* demand, int numCar, double* capacity, double* disLimit, double k1, double k2, double k3, void(*Callback)(int numCar, int** path, int* pathLen, double* load, double* mileage));