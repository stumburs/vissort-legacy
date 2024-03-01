#include "GenDescending.h"

void GenDescending::Generate(std::vector<Element>& data)
{
	std::size_t size = data.size();
	data.clear();
	for (size_t i = 1; i <= size; i++)
	{
		Element elem{};
		elem.value = size - i + 1;
		elem.color = ColorFromHSV((float)i / size * 360.0f, 0.3f, 1.0f);
		data.push_back(elem);
	}
}