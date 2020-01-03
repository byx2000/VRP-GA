#pragma once

#include "../Util/Random.h"
#include "Node.h"

#include <iostream>
#include <algorithm>

class VRP
{
public:
	VRP()
	{
		cNode = 0;
		cCar = 0;
		nodeInfo.push_back(Node(0.0, 0.0, 0.0));
	}

	void setDeparture(double x, double y)
	{
		nodeInfo[0] = Node(x, y, 0.0);
	}

	void addNode(double x, double y, double demand)
	{
		nodeInfo.push_back(Node(x, y, demand));
		cNode++;
	}

	void addCar(double capacity)
	{
		carInfo.push_back(Car(capacity));
		cCar++;
	}

	struct Result
	{
		std::vector<std::vector<int>> path;
		std::vector<double> load;
		std::vector<double> mileage;
	};

	Result solve()
	{
		using namespace std;

		//预处理所有点对的距离
		dis = vector<vector<double>>(cNode + 1, vector<double>(cNode + 1, 0.0));
		for (int i = 0; i <= cNode; ++i)
		{
			for (int j = 0; j <= cNode; ++j)
			{
				dis[i][j] =
					sqrt((nodeInfo[i].x - nodeInfo[j].x) * (nodeInfo[i].x - nodeInfo[j].x)
						+ (nodeInfo[i].y - nodeInfo[j].y) * (nodeInfo[i].y - nodeInfo[j].y));
			}
		}

		//初始化种群
		vector<Chrom> chroms;
		while (chroms.size() < 1000)
		{
			Chrom c(this);
			if (c.valid)
			{
				chroms.push_back(c);
			}
		}

		//遗传算法
		int cnt = 0;
		int c = 0;
		Chrom best(this);
		while (1)
		{
			c++;
			sort(chroms.begin(), chroms.end());
			if (chroms[0] < best)
			{
				best = chroms[0];
				cnt = 0;
			}
			else
			{
				cnt++;
			}

			if (cnt >= 1000)
			{
				break;
			}

			int cnt = chroms.size() / 2;
			for (int i = cnt; i < (int)chroms.size(); ++i)
			{
				chroms[i] = chroms[i - cnt];
				chroms[i].mutation();
			}
		}

		cout << "进化代数：" << c << endl;

		//返回结果
		return best.decode();
	}

private:
	struct Car
	{
		double capacity;
		Car(double capacity = 0.0)
			: capacity(capacity) {}
	};

	struct Chrom
	{
		VRP* pVRP;
		std::vector<int> gene;
		std::vector<double> d, w;
		double time, length;
		int cnt;
		bool valid;

		Chrom(VRP* pVRP)
		{
			this->pVRP = pVRP;

			d.resize(pVRP->cCar, 0.0);
			w.resize(pVRP->cCar, 0.0);

			for (int i = 0; i < pVRP->cNode; ++i)
			{
				gene.push_back(i + 1);
			}
			//Random::Shuffle(gene.begin(), gene.end());
			Random::Shuffle(gene);

			int index = 0;
			for (int i = 0; i < pVRP->cCar - 1; ++i)
			{
				double sum = 0.0;
				while (1)
				{
					if (index >= (int)gene.size())
					{
						break;
					}
					sum += pVRP->nodeInfo[gene[index]].demand;
					if (sum > pVRP->carInfo[i].capacity)
					{
						break;
					}
					index++;
				}

				gene.insert(gene.begin() + index, 0);
			}

			update();
		}

		void update()
		{
			using namespace std;

			for (int i = 0; i < (int)d.size(); ++i)
			{
				d[i] = w[i] = 0.0;
			}

			int iCar = 0;
			int last = 0;
			for (int i = 0; i < (int)gene.size(); ++i)
			{
				if (gene[i] == 0)
				{
					d[iCar] += pVRP->dis[last][0];
					iCar++;
					last = 0;
				}
				else
				{
					d[iCar] += pVRP->dis[last][gene[i]];
					w[iCar] += pVRP->nodeInfo[gene[i]].demand;
					last = gene[i];
					if (w[iCar] > pVRP->carInfo[iCar].capacity)
					{
						valid = false;
						return;
					}
				}
			}
			d[iCar] += pVRP->dis[last][0];

			time = 0.0;
			length = 0.0;
			cnt = 0;
			for (int i = 0; i < (int)d.size(); ++i)
			{
				time = max(time, d[i]);
				length += d[i];
				if (fabs(d[i] - 0.0) > 1e-6)
				{
					cnt++;
				}
			}

			valid = true;
		}

		void mutation()
		{
			using namespace std;

			int i = Random::UniformInt(0, gene.size() - 1);
			int j = Random::UniformInt(0, gene.size() - 1);
			swap(gene[i], gene[j]);
			double t_time = time;
			double t_length = length;
			int t_cnt = cnt;
			update();
			if (!valid)
			{
				swap(gene[i], gene[j]);
				time = t_time;
				length = t_length;
				cnt = t_cnt;
				valid = true;
			}
		}

		double fitness(double k1, double k2, double k3) const
		{
			if (!valid)
				return 1e8;
			else
				return k1 * time + k2 * length + k3 * cnt;
		}

		bool operator<(const Chrom& c) const
		{
			double k1 = 100.0, k2 = 1.0, k3 = 1.0;
			return fitness(k1, k2, k3) < c.fitness(k1, k2, k3);
		}

		Result decode() const
		{
			Result res;
			res.path.resize(pVRP->cCar);
			res.load = w;
			res.mileage = d;

			int iCar = 0;
			for (int i = 0; i < (int)gene.size(); ++i)
			{
				if (gene[i] == 0)
				{
					iCar++;
				}
				else
				{
					res.path[iCar].push_back(gene[i]);
				}
			}

			return res;
		}

		void print() const
		{
			using namespace std;

			int iCar = 0;
			cout << iCar + 1 << "号车：";
			for (int i = 0; i < (int)gene.size(); ++i)
			{
				if (gene[i] == 0)
				{
					cout << "\t载重量：" << w[iCar] << "\t核载：" << pVRP->carInfo[iCar].capacity << "\t路程：" << d[iCar] << endl;
					iCar++;
					cout << iCar + 1 << "号车：";
				}
				else
				{
					cout << gene[i] << " ";
				}
			}
			cout << "\t载重量：" << w[iCar] << "\t核载：" << pVRP->carInfo[iCar].capacity << "\t路程：" << d[iCar] << endl;

			if (valid)
			{
				cout << "时间：" << time << "\t";
				cout << "里程：" << length << "\t";
				cout << "车辆数：" << cnt << "\t";
			}
			else
			{
				cout << "不合法";
			}
			cout << endl << endl;
		}
	};

	int cNode, cCar;
	std::vector<Node> nodeInfo;
	std::vector<Car> carInfo;
	std::vector<std::vector<double>> dis;
};