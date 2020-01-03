#include "RandomUtil.h"

#include <random>
#include <ctime>

using namespace std;

mt19937 rnd((unsigned)time(0));

int Random::UniformInt(int a, int b)
{
	uniform_int_distribution<> dist(a, b);
	return dist(rnd);
}

double Random::UniformDouble(double a, double b)
{
	uniform_real_distribution<> dist(a, b);
	return dist(rnd);
}

void Random::Shuffle(std::vector<int>& v)
{
	shuffle(v.begin(), v.end(), rnd);
}
