#ifndef __OPTIONCLASS_HPP__
#define __OPTIONCLASS_HPP__

#include <iostream>
#include <cstdio>
#include <cmath>
#include<vector>

//Create Node Structure 
struct Node {
	double price;
	double time;
	double payoff;
	double value;
};

//Option Class
class Option{
	protected: 
		int n;
		double S0;
		double K;
		double upfactor;
		double downfactor;
		double r;
		double pUp;
		double pDown;
		vector<vector<Node>> tree;
		string optionType;
		double(*optionPayoff)(double, double);
	public:
		Option(double price, double strike, double up, double down, double rate, double probUp, double probDown, int numberSteps, string oType);
		void print();
};

#endif 