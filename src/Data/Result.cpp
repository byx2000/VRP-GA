#include "Result.h"

#include <algorithm>

using namespace std;

std::string Result::toString() const
{
	string s;
	s += "Generation count: ";
	s += to_string(numGeneration);
	s += "\n";

	for (int i = 0; i < (int)path.size(); ++i)
	{
		s += "Car ";
		s += to_string(i);

		if (path[i].size() == 0)
		{
			s += ": unuse\n";
			continue;
		}

		s += ": 0->";
		for (int j = 0; j < (int)path[i].size(); ++j)
		{
			s += to_string(path[i][j]);
			s += "->";
		}
		s += "0 ";
		s += "load: ";
		s += to_string(load[i]);
		s += " mileage: ";
		s += to_string(mileage[i]);
		s += "\n";
	}

	s += "\ntotal time: ";
	s += to_string(totalTime());
	s += " total mileage: ";
	s += to_string(totalMileage());
	s += " car use: ";
	s += to_string(totalCarUse());
	s += "\n";

	return s;
}

double Result::totalTime() const
{
	return *max_element(mileage.begin(), mileage.end());
}

double Result::totalMileage() const
{
	double sum = 0.0;
	for (int i = 0; i < (int)mileage.size(); ++i)
	{
		sum += mileage[i];
	}
	return sum;
}

int Result::totalCarUse() const
{
	int cnt = 0;
	for (int i = 0; i < (int)path.size(); ++i)
	{
		if (path[i].size() > 0)
		{
			cnt++;
		}
	}
	return cnt;
}
