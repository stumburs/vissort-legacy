#pragma once
#include <vector>
#include "Element.h"
#include "IGenerateAlgorithm.h"

class Randomize : public IGenerateAlgorithm
{
	void Generate(std::vector<Element>& data) override;
};

