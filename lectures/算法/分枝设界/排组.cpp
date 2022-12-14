#include "排组.h"

int min(int m, int n)
{
	return (m < n ? m : n);
}

namespace cs245
{

	std::vector<int> &组合数(int n)
	{
		std::vector<int> *贰 = new std::vector<int>(n+1, 0);
		int 旧, 新;
		for (int i = 0; i <= n; i++)
		{
			旧 = 新 = (*贰)[0];
			for (int j = 0; j <= min(i, n); j++)
			{
				if (j == 0 || j == i)
				{
					(*贰)[j] = 1;
				}
				else
				{
					新 = (*贰)[j];
					(*贰)[j] = 旧 + (*贰)[j];
					旧 = 新;
				}
			}
		}
		return *贰;
	}

	void 印列(const std::vector<int> &列)
	{
		std::cout << "[";
		for (int i = 0; i < 列.size(); i++)
		{
			std::cout << 列[i] << (i == 列.size() - 1 ? "]" : ",");
		}
		std::cout << std::endl;
	}

	void 印列(int 号, int 列[], int 长度)
	{
		std::cout << std::setw(4) << 号 << ':';

		std::cout << "(";
		int i = 0;
		for (i = 0; i < 长度 - 1; i++)
		{
			std::cout << 列[i] << ',';
		}
		std::cout << 列[i];
		std::cout << ")" << std::endl;
	}

	int 造排(int n)
	{
		int i, j; // 排列元号
		int k;	  // 循环计数

		int *d = new int[n]; //

		for (k = 0; k < n; ++k)
		{
			d[k] = k+1;
		}

		印列(0, d, n);

		int 排列总数 = 1;
		for (k = 0; k < n; ++k)
		{
			排列总数 *= k + 1;
		}

		for (k = 1; k < 排列总数; ++k)
		{
			// 从右至左寻找第一个下坡
			i = n - 2;
			j = n - 1;

			while (d[i] > d[j]) // 上坡
			{
				--i;
				--j;
			}
			// 至下坡 d[i]<d[j]
			// 从i之右至左寻找第一个比d[i]大的数，因上坡，此数自然是i之右比d[i]大的数中之最小
			j = n - 1;
			while (d[i] > d[j])
			{
				--j;
			}
			// 此处d[j]>d[i]

			// 交换d[i],d[j]
			std::swap(d[i], d[j]);

			// 将i之右的数反位
			++i;
			j = n - 1;
			while (i < j)
			{
				std::swap(d[i], d[j]);
				++i;
				--j;
			}

			印列(k, d, n);
		}

		//delete[] d;

		return 0;
	}

	int 造组(int n, int r)
	{
		// 以字典序造所有{1,2,...,n}选r之组合
		int i, j; //组合元号
		int k;	  //循环计数

		int 丄; //单元最大允许值

		int *d = new int[r];

		for (k = 0; k < r; k++)
		{
			d[k] = k+1;
		}
		if (r == 0)
			d[0] = 0;
		印列(0, d, r);

		int 组合总数 = 1, 分子 = 1, 分母 = 1;
		for (k = 0; k < r; k++)
		{
			分子 *= n - k;
			分母 *= k + 1;
		}
		组合总数 = 分子 / 分母;

		for (k = 1; k < 组合总数; k++)
		{
			丄 = n - 1;
			i = r - 1;

			while (d[i] == 丄)
			{
				--i;
				--丄;
			}
			// 此时d[i]<丄, 对d[i]增一
			++d[i];

			// 重置i右侧数
			for (j = i + 1; j < r; j++)
			{
				d[j] = d[j - 1] + 1;
			}

			印列(k, d, r);
		}

		//delete[] d;

		return 0;
	}
}