#pragma once
#include "Option.h"
class American :
	public Option
{
public:
	American(double price, double strike, double up, double down, double rate, double probUp, double probDown, int numberSteps, std::string oType)
		: Option(price, strike, up, down, rate, probUp, probDown, numberSteps, oType)
	{
	}
	double getValue();
};

