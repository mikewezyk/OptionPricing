#include "stdafx.h"
#include "European.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

//Calculates Current Value of European Option
double European:: getValue(){
	//Calculate Option Payoff at End Nodes
	for (int i = 0; i <= n; i++){
		tree[n][i].value = optionPayoff(tree[n][i].price,K);
	}
	//Calculate Option Value at Each Node
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			tree[i][j].value = (pUp*tree[i + 1][j + 1].value + pDown*tree[i + 1][j].value) * exp(-r*deltaT);;
		}
	}
	//Return Option Value at t = 0
	return tree[0][0].value;
}
