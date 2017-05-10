#pragma once
#include "Option.h"
class American :
public Option
{
public:
    American(double price, double strike, double up, double down, double rate, double probUp, double probDown, double numberSteps, std::string oType, double delta)
    : Option(price, strike, up, down, rate, probUp, probDown, numberSteps, oType, delta)
    {
    }
    double getValue();
};
