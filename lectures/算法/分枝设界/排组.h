#ifndef _排组_H_
#define _排组_H_

#include <utility>
#include <iostream>
#include <iomanip>
#include <vector>

namespace cs245 {
	int 造排(int n);
	int 造组(int n, int r);
	std::vector<int> &组合数(int n);
	void 印列(const std::vector<int> &列);
}

#endif // !_排组_H_