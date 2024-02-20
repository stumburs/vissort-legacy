#pragma once
#include <vector>
#include "Element.h"
#include <string>

class DataGenerator
{
public:
	DataGenerator();
	void Initialize(std::vector<Element>& data, std::size_t size);
	void Randomize(std::vector<Element>& data);
	void Ascending(std::vector<Element>& data);
	void Descending(std::vector<Element>& data);
	void Sin(std::vector<Element>& data);
	void FuzzyAscending(std::vector<Element>& data);
	void FuzzyDescending(std::vector<Element>& data);
	void Random(std::vector<Element>& data);

	enum class ShufflingTypes
	{
		Ascending = 0,
		Descending,
		Sin,
		FuzzyAscending,
		FuzzyDescending,
		Random,
		END
	};

	void Shuffle(std::vector<Element>& data);
	void SetActiveShuffle(ShufflingTypes type);
	std::string ShufflingTypesToString(ShufflingTypes type);
	ShufflingTypes active_shuffle = ShufflingTypes::Ascending;
};
