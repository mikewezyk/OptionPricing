
#include "Option.h"
#include <iostream>
#include <algorithm>
//#include <minmax.h>

//Option Payoff Function Declarations
double Put(double S, double K){
    return std::max(0.0, K - S);
}
double Call(double S, double K){
    return std::max(0.0, S - K);
}

Option::Option(double price, double strike, double up, double down, double rate, double probUp, double probDown, int numberSteps, std::string oType, double delta)
{
    n = numberSteps;
    upfactor = up;
    downfactor = down;
    S0 = price;
    K = strike;
    r = rate;
    pUp = probUp;
    pDown = probDown;
    deltaT = delta;
	//Assign Appropriate Option Payoff Function
	if (oType == "Put"){
		optionPayoff = &Put;
	}
	if (oType == "Call"){
		optionPayoff = &Call;
	}
    //Create Binomial Tree by Assingning a Stock Price to Each Node
    std::vector<std::vector<Node>> stockTree(n + 1, std::vector<Node>(n + 1));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            stockTree[i][j].price = S0*pow(upfactor, j)*pow(downfactor, i - j);
        }
    }
    tree = stockTree;
}
