#pragma once
#include "Option.h"

class AmericanAsian :
	public Option
{
public:
	AmericanAsian(double price, double strike, double up, double down, double rate, double probUp, double probDown, int numberSteps, std::string oType, double delta)
		: Option(price, strike, up, down, rate, probUp, probDown, numberSteps, oType, delta)
	{
	}
	double getValue();
};


