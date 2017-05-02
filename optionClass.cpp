#include "optionClass.hpp"

#include <iostream>

//Option Payoff Function Declarations
double Put(double S, double K){
	return max(0.0,K - S);
}
double Call(double S, double K){
	return max(0.0,S - K);
}

//Option Constructor
Option::Option(double price, double strike, double up, double down, double rate, double probUp, double probDown, int numberSteps, string oType){
	n = numberSteps;
	upfactor = up;
	downfactor = down;
	S0 = price;
	K = strike;
	r = rate;
	pUp = probUp;
	pDown = probDown;
	//Assign Appropriate Option Payoff Function
	if (oType == "Put"){
		optionPayoff = &Put;
	}
	if (oType == "Call"){
		optionPayoff = &Call;
	}
	//Create binomial tree
	vector<vector<Node>> stockTree(n + 1, vector<Node>(n + 1));
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			stockTree[i][j].price = S0*pow(upfactor, j)*pow(downfactor,i - j);
			stockTree[i][j].time = i+1;
			stockTree[i][j].payoff = optionPayoff(stockTree[i][j].price,K);
		}
	}
	tree = stockTree;
}



