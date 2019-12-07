#include <random>
#include <vector>

class Random
{
public:
	Random()
	{
		rnd.seed(std::random_device()());
	}

	int uniformIntDist(int a, int b)
	{
		std::uniform_int_distribution<> dist(a, b);
		return dist(rnd);
	}

	double uniformDoubleDist(double a, double b)
	{
		std::uniform_real_distribution<> dist(a, b);
		return dist(rnd);
	}

	void shuffle(std::vector<int>::iterator iBegin, std::vector<int>::iterator iEnd)
	{
		std::shuffle(iBegin, iEnd, rnd);
	}

private:
	std::mt19937 rnd;
};