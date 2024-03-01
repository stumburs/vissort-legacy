#include "GenRandom.h"

void GenRandom::Generate(std::vector<Element>& data)
{
	std::size_t size = data.size();
	data.clear();
	for (size_t i = 1; i < size + 1; i++)
	{
		Element elem{};
		elem.value = rand() % size;
		elem.color = ColorFromHSV((float)i / size * 360.0f, 0.3f, 1.0f);
		data.push_back(elem);
	}
}
