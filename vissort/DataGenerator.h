#pragma once
#include <vector>
#include "Element.h"

class DataGenerator
{
public:
	DataGenerator();
	void Randomize(std::vector<Element>& data);
};
