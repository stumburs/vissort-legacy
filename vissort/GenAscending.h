#pragma once
#include "IGenerateAlgorithm.h"

class GenAscending : public IGenerateAlgorithm
{
public:
	void Generate(std::vector<Element>& data) override;
};
