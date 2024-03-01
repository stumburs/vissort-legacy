#pragma once
#include "IGenerateAlgorithm.h"

class GenDescending : public IGenerateAlgorithm
{
	void Generate(std::vector<Element>& data) override;
};

