#include "stdafx.h"
#include "American.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include<vector>

//Calculate Value of American Option
double American:: getValue(){
	//Calculate Option Payoff at Each Node
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			tree[i][j].payoff = optionPayoff(tree[i][j].price, K);
		}
	}
	//Assign Option Value at End Nodes to Payoff
	for (int i = 0; i <= n; i++){
		tree[n][i].value = (tree[n][i].payoff);
	}
	//Calculate Option Value at Each Node
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			tree[i][j].value = (pUp*tree[i + 1][j + 1].value + pDown*tree[i + 1][j].value) * exp(-r*deltaT);
			if (tree[i][j].value < tree[i][j].payoff){
				tree[i][j].value = tree[i][j].payoff;
			}
		}
	}
	//Return Option Value at t = 0
	return tree[0][0].value;
}

