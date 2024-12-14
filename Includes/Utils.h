#pragma once
#include "includes.h"

class Utils
{
public:
	static std::size_t CalculatePadding(const std::size_t currentAdress, const std::size_t alignment)
	{
		std::size_t numOfAlignments = (currentAdress / alignment) + 1;
		return (numOfAlignments * alignment) - currentAdress;
	}
};


