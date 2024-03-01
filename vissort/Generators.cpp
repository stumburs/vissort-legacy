#include "Generators.h"

Generators::Generators()
{
    generators["Ascending"] = std::make_unique<GenAscending>();
    generators["Random"] = std::make_unique<GenRandom>();
}
