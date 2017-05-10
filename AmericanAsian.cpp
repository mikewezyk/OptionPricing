#include "stdafx.h"
#include "AmericanAsian.h"

//Calculates Current Value of a European Style Asian Option
double AmericanAsian::getValue(){
	//Calculate Maximum and Minimum Average Stock Price Values for Each Level
	std::vector<double> maximums(n+1);
	maximums[0] = tree[0][0].price;
	maximums[1] = (tree[1][1].price + maximums[0]) / 2.0;
	for (int i = 2; i <= n; i++){
		maximums[i] = ((i - 1)*maximums[i - 1] + tree[i][i].price) / i;
	}
	std::vector<double> minimums(n+1);
	minimums[0] = tree[0][0].price;
	minimums[1] = (tree[1][0].price + minimums[0]) / 2.0;
	for (int i = 2; i <= n; i++){
		minimums[i] = ((i - 1)*minimums[i - 1] + tree[i][0].price) / i;
	}
	//Assign Price Min/Max Averages to Each Level
	for (int i = 0; i <= n; i++){
		tree[i][0].average = minimums[i];
		tree[i][i].average = maximums[i];
	}
	//Calculate Average Values for Each Node Using Previously Calculated Max/Min and Linear Interpolation 
	for (int i = n; i > 0; i--){
		for (int j = 1; j < i; j++){
			tree[i][j].average = tree[i][0].average + j*(tree[i][i].average - tree[i][0].average) / i;
		}
	}
	//Calculate Option Payoff for Each Node
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			tree[i][j].payoff = optionPayoff(tree[i][j].average, K);
		}
	}
	//Assign Option Value at End Nodes to Payoff
	for (int i = 0; i <= n; i++){
		tree[n][i].value = (tree[n][i].payoff);
	}
	//Calculate Option Value at Each Non-End Node
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			tree[i][j].value = (pUp*tree[i + 1][j + 1].value + pDown*tree[i + 1][j].value) * exp(-r*deltaT);
			if (tree[i][j].value < tree[i][j].payoff){
				tree[i][j].value = tree[i][j].payoff;
			}
		}
	}
	//Return the Value of the Option at t = 0
	return tree[0][0].value;
}