#pragma once
#include "IGenerateAlgorithm.h"

class GenSin : public IGenerateAlgorithm
{
	void Generate(std::vector<Element>& data) override;
};
