#pragma once
#include <string>
#include <map>
#include <vector>

namespace Sound {
	void Init();

	extern std::map<int, int> scale;
	extern std::map<std::string, int> se;
}