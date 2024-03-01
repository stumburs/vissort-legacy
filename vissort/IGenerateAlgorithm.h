#pragma once
#include "Element.h"
#include <vector>

class IGenerateAlgorithm
{
public:
	virtual ~IGenerateAlgorithm() = default;
	virtual void Generate(std::vector<Element>& data) = 0;
};

