#include "stdafx.h"
#include "Asian.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include<vector>

//Calculates Current Value of a European Style Asian Option
double Asian::getValue(){
	//Calculate Maximum and Minimum Average Stock Price Values for Each Level
	std::vector<double> maximums(n+1);
	maximums[0] = tree[0][0].price;
	maximums[1] = (tree[1][1].price + maximums[0])/2;
	for (int i = 2; i <= n; i++){
		maximums[i] = ((i-1)*maximums[i-1] + tree[i][i].price)/i;
	}
	std::vector<double> minimums(n+1);
	minimums[0] = tree[0][0].price;
	minimums[1] = (tree[1][0].price + minimums[0])/2;
	for (int i = 2; i <= n; i++){
		minimums[i] = ((i - 1)*minimums[i - 1] + tree[i][0].price) / i;
	}
	//Assign Price Averages to Final Level
	tree[n][n].average = maximums[n];
	tree[n][0].average = minimums[n];
	//Calculate End Point Average Values Using Previously Calculated Max/Min and Linear Interpolation
	//Also Calculate End Point Option Values
	for (int i = 1; i < n; i++){
		tree[n][i].average = tree[n][0].average + i*(tree[n][n].average - tree[n][0].average) / n;
		tree[n][i].value = optionPayoff(tree[n][i].average, K);
	}
	tree[n][n].value = optionPayoff(tree[n][n].average, K);
	tree[n][0].value = optionPayoff(tree[n][0].average, K);
	//Calculate Value for Each Node of Tree
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			tree[i][j].value = (pUp*tree[i + 1][j + 1].value + pDown*tree[i + 1][j].value) * exp(-r*deltaT);
		}
	}
	std::cout << "STEP 4 DONE";
	//Return the Value of the Option at t = 0
	return tree[0][0].value;
}
