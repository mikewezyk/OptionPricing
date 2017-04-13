#ifndef __OPTIONCLASS_HPP__
#define __OPTIONCLASS_HPP__

#include <iostream>
#include <cstdio>
#include <cmath>
#include<vector>
using namespace std;

//Create Node Structure 
struct Node {
	double price;
	double time;
	double payoff;
};

//Option Class
class Option{
	private: 
		int n;
		double S0;
		double K;
		double upfactor;
		double downfactor;
		vector<vector<Node>> tree;
		string optionType;
		double(*optionPayoff)(double, double);
	public:
		Option(double price, double strike, double up, double down, int numberSteps, string oType);
		void print();
		friend class European;
		friend class American;
};

#endif 