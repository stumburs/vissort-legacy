#pragma once
#include <map>
#include <string>
#include <memory>
#include "IGenerateAlgorithm.h"
#include "GenAscending.h"
#include "GenRandom.h"

class Generators
{
public:
	Generators();
	std::map<std::string, std::unique_ptr<IGenerateAlgorithm>> generators;
};
