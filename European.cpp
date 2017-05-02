#include "stdafx.h"
#include "European.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include<vector>

//Calculates Current Value of European Option
double European:: getValue(){
	for (int i = 0; i <= n; i++){
		tree[n][i].value = (tree[n][i].payoff);
		std::cout << tree[n][i].value << "\n";
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			tree[i][j].value = (pUp*tree[i + 1][j + 1].value + pDown*tree[i + 1][j].value) / ((1 + r));
			std::cout << tree[i][j].value << "\n";
		}
	}
	return tree[0][0].value;
}

