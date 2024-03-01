#pragma once
#include <vector>
#include "Element.h"
#include "IGenerateAlgorithm.h"

class GenRandom : public IGenerateAlgorithm
{
public:
	void Generate(std::vector<Element>& data) override;
};
