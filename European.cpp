#include <iostream>
#include <cstdio>
#include <cmath>
#include<vector>
#include "European.hpp"

European:: double getValue(){
	for (int i = 0; i <= n; i++){
		tree[n][i].value = (tree[n][i].payoff/(1+r)^n)
	}
	for (int i = n-1; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			tree[i][j].value = (pUp*tree[i+1][j+1].value + pDown*tree[i+1][j].value)/((1+r)^i) ;
		}
	}
	return tree[0][0].value;
}
