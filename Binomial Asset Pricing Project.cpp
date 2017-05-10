// Binomial Asset Pricing Project.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<iostream>
#include <string>
#include "Option.h"
#include "European.h"
#include "American.h"
#include "Data.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//Get Ticker 
	std::string ticker;
	std::cout << "Please input a valid ticker symbol for the option you wish to analyze: \n ";
	std::getline(std::cin,ticker);

	//Get OptionType1
	std::string optionType;
	while (true){
		std::cout << "Choose an option type from the following list: \n Put \n Call \n ";
		std::getline(std::cin, optionType);
		if (optionType == "Put" || optionType == "Call"){
			break;
		} 
		else {
			std::cout << "ERROR: Invalid Option Type \n";
		}
	}

	//Get Option Type2
	std::string optionType2;
	while (true){
		std::cout << "Choose an option type from the following list: \n American \n European \n ";
		std::getline(std::cin, optionType2);
		if (optionType2 == "American" || optionType2 == "European"){
			break;
		}
		else {
			std::cout << "ERROR: Invalid Option Type \n";
		}
	}

	//Get Strike Price
	double strike;
	std::cout << "Please enter a strike price for your option in the following format: \n ";
	std::cin >> strike;

	//Get Expiration Date
	std::string expiration;
	while (true){
		std::cout << "Please enter an expiration date for your option in the following format: \n YYYY-MM-DD ";
		std::getline(std::cin,expiration);
		if (expiration.length() == 10){
			break;
		}
		else {
			std::cout << "ERROR: Please enter date in given format. \n";
		}
	}

	//Retrieve data by creating an instance of the data class
	Data DATA = Data(ticker,expiration);

	//Set Parameters Needed for Option Calculations
	double delta = 1 / 252;
	int periods = 3;
	double S0 = DATA.S0;
	double K = strike;
	double UP = DATA.upfactor;
	double DOWN = DATA.downfactor;
	double r = DATA.r;
	double pUp = DATA.pUp;
	double pDown = DATA.pDown;
	
	//Create Option and get present value 
	if (optionType2 == "American"){
		American O = American(S0, K, UP, DOWN, r, pUp, pDown, periods, optionType, delta);
		std::cout << "\nThe value of the option is: $" << O.getValue() << "\n";
		std::cout << "Press ENTER to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (optionType2 == "European"){
		European O = European(S0, K, UP, DOWN, r, pUp, pDown, periods, optionType, delta);
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