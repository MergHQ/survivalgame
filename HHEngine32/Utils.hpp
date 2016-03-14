#include <string>
#include <sstream>
#include <glm\common.hpp>
#include <glm\vec3.hpp>
#include <vector>

namespace StringTools
{
	std::vector<std::string> sOperation(const std::string &s, char delim, std::vector<std::string> &elems)
	{
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

	static std::vector<std::string> SplitString(const std::string &s, char delim)
	{
		std::vector<std::string> elems;
		sOperation(s, delim, elems);
		return elems;
	}
}
