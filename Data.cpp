#include "stdafx.h"
#include "Data.h"


Data::Data(std::string tick, std::string expiration)
{
	ticker = tick;
	expDate = expiration;
	
	//R SCRIPT GOES HERE CALLING TICK AND EXP
	system("Rscript Binomial Paramater.r");


	//VALUES FROM R WILL DEFINE PARAMETERS BELOW
	volatility = 0;
	n = 0;
	S0 = 0;
	r = 0;
	deltaT = 0;
	upfactor = exp(volatility*sqrt(deltaT));
	downfactor = exp(-volatility*sqrt(deltaT));
	pUp = (1.0 + exp(r*deltaT) -downfactor)/(upfactor - downfactor);
	pDown = 1.0 - pUp;
}