#include <vector>

class Random
{
public:
	static int UniformInt(int a, int b);
	static double UniformDouble(double a, double b);
	static void Shuffle(std::vector<int>& v);
};