#include "DataGenerator.h"
#include <ctime>

DataGenerator::DataGenerator()
{
	srand(time(NULL));
}

void DataGenerator::Randomize(std::vector<Element>& data)
{
	for (std::size_t i = 0; i < data.size(); i++)
		std::swap(data[i], data[rand() % data.size()]);
}
