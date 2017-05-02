// Binomial Asset Pricing Project.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<iostream>
#include <string>
#include "Option.h"
#include "European.h"
#include "American.h"


int _tmain(int argc, _TCHAR* argv[])
{
	std::string optionType;
	bool RUN = true;
	while (RUN == true){
		std::cout << "Choose an option type from the following list: \n Put \n Call \n ";
		std::getline(std::cin, optionType);
		if (optionType == "Put" || optionType == "Call"){
			RUN = false;
		} 
		else {
			std::cout << "ERROR: Invalid Option Type \n";
		}
	}
	std::string optionType2;
	RUN = true;
	while (RUN == true){
		std::cout << "Choose an option type from the following list: \n American \n European \n ";
		std::getline(std::cin, optionType2);
		if (optionType2 == "American" || optionType2 == "European"){
			RUN = false;
		}
		else {
			std::cout << "ERROR: Invalid Option Type \n";
		}
	}
	double P = 4.0;
	double K = 5.0;
	double UP = 2.0;
	double DOWN = 0.5;
	double r = 0.25;
	double pUp = 0.5;
	double pDown = 0.5;
	int periods = 3;
	if (optionType2 == "American"){
		American O = American(P, K, UP, DOWN, r, pUp, pDown, periods, optionType);
		std::cout << "\nThe value of the option is: $" << O.getValue() << "\n";
		std::cout << "Press ENTER to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (optionType2 == "European"){
		European O = European(P, K, UP, DOWN, r, pUp, pDown, periods, optionType);
		std::cout << "\nThe value of the option is: $" << O.getValue() << "\n";
		std::cout << "Press ENTER to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else {
		std::cout << "ERROR: Invalid Option Type Parameters";
		return 0;
	}
	return 0;
}