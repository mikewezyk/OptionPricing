#pragma once
#include<vector>

class Data
{
protected:
	void readCSV(std::istream &input, std::vector< std::vector<std::string> > &output);
public:
	int n;
	double S0;
	double volatility;
	double upfactor;
	double downfactor;
	double r;
	double pUp;
	double pDown;
	double deltaT;
	std::string ticker;
	std::string expDate;
	Data(std::string tick, std::string expiration);
};

