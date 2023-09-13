#pragma once
#include <vector>
#include "Element.h"

class DataGenerator
{
public:
	DataGenerator();
	void Initialize(std::vector<Element>& data, std::size_t size);
	void Randomize(std::vector<Element>& data);
	void Sin(std::vector<Element>& data);
	void Fuzzy(std::vector<Element>& data);
	void Reverse(std::vector<Element>& data);
};
