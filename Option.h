#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>


//Create Node Structure
struct Node {
    double price;
    double payoff;
    double value;
    double average;
};

//Option Class
class Option
{
protected:
    double n;
    double S0;
    double K;
    double upfactor;
    double downfactor;
    double r;
    double pUp;
    double pDown;
    double deltaT;
    std::vector<std::vector<Node>> tree;
    std::string optionType;
    double(*optionPayoff)(double, double);
public:
    Option(double price, double strike, double up, double down, double rate, double probUp, double probDown, int numberSteps, std::string oType, double delta);
};
