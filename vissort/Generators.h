#pragma once
#include <map>
#include <string>
#include <memory>
#include "IGenerateAlgorithm.h"

class Generators
{
public:
	Generators();
	std::map<std::string, std::unique_ptr<IGenerateAlgorithm>> generators;
};
