// Binomial Asset Pricing Project.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<iostream>
#include <string>
#include "Option.h"
#include "European.h"
#include "American.h"
#include "Asian.h"
#include "AmericanAsian.h"
#include <RInside.h>

std::string getInput(std::string message){
	std::string result;
	std::cout << message;
	std::cout << "\nInput: ";
	std::getline(std::cin, result);
	std::cout << "---------------------------------------------------------------------------\n";
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string ticker = getInput("Enter a valid ticker symbol:");

	//Get OptionType1
	std::string optionT1;
	while (true){
		optionT1 = getInput("Choose an option type from the following list: \n Put \n Call");
		if (optionT1 == "Put" || optionT1 == "Call"){
			break;
		} 
		else {
			std::cout << "ERROR: Invalid Option Type \n";
		}
	}

	//Get Option Type2
	std::string optionT2;
	while (true){
		optionT2 = getInput("Choose an option type from the following list: \n American \n European \n European Asian \n American Asian");
		if (optionT2 == "American" || optionT2 == "European" || optionT2 == "European Asian" || optionT2 == "American Asian"){
			break;
		}
		else {
			std::cout << "ERROR: Invalid Option Type \n";
		}
	}

	//Get Expiration Date
	std::string expiration;
	while (true){
		expiration = getInput("Please select the length for your option from the following list: \n 1mo \n 3mo \n 1yr");
		if (expiration == "1mo" || expiration == "3mo" || expiration == "1yr"){
			break;
		}
		else {
			std::cout << "ERROR: Please enter date in given format. \n";
		}
	}
	//Set Number of Periods
	int periods;
	if (expiration == "1yr"){
		periods = 252;
	}
	if (expiration == "3mo"){
		periods = 63;
	}
	else {
		periods = 21;
	}

	//Get Strike Price
	double strike;
	std::cout << "Please enter a strike price (double) for your option: \n ";
	std::cin >> strike;

	RInside R(argc, argv);              // create an embedded R instance

	R["symbol"] = ticker;      // assign a char* (string) to 'txt'


	std::string part1 =
		"require(quantmod); start <- Sys.Date() - 365; start <- start - 1; data <- getSymbols(symbol, src = 'yahoo', from = start, to = Sys.Date(), auto.assign = FALSE); returns <- diff(log(data[,6]))[-1]";
	R.parseEvalQ(part1);

	std::string part2 =
		"vol <- sd(returns) * sqrt(252)";
	double volatility = R.parseEval(part2);
	std::cout << "Volatility: " << volatility << std::endl;

	std::string part3 =
		"getSymbols('DGS3MO', src = 'FRED'); rf <- tail(DGS3MO,n=1)/100";
	double r = R.parseEval(part3);
	std::cout << "Risk Free Rate: " << r << std::endl;


	std::string part4 =
		"price <- tail(data[,6],n=1)";
	R.parseEval(part4);

	std::string part5 =
		"price <- as.double(price[1,1])";
	double S0 = R.parseEval(part5);
	std::cout << "Price: " << S0 << std::endl;

	//Calculate Needed for Option Calculations
	double delta = 1 / 252;
	double UP = exp(volatility*sqrt(delta));
	double DOWN = exp(-volatility*sqrt(delta));
	double pUp = (1.0 + exp(r*delta) - UP) / (UP - DOWN);
	double pDown = 1.0 - pUp;
	
	//Create Option and get present value 
	if (optionT2 == "American"){
		American O = American(S0, strike, UP, DOWN, r, pUp, pDown, periods, optionT1, delta);
		std::cout << "\nThe value of the option is: $" << O.getValue() << "\n";
		std::cout << "Press ENTER to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (optionT2 == "European"){
		European O = European(S0, strike, UP, DOWN, r, pUp, pDown, periods, optionT1, delta);
		std::cout << "\nThe value of the option is: $" << O.getValue() << "\n";
		std::cout << "Press ENTER to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (optionT2 == "European Asian"){
		Asian O = Asian(S0, strike, UP, DOWN, r, pUp, pDown, periods, optionT1, delta);
		std::cout << "\nThe value of the option is: $" << O.getValue() << "\n";
		std::cout << "Press ENTER to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (optionT2 == "American Asian"){
		AmericanAsian O = AmericanAsian(S0, strike, UP, DOWN, r, pUp, pDown, periods, optionT1, delta);
		std::cout << "\nThe value of the option is: $" << O.getValue() << "\n";
		std::cout << "Press ENTER to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else {
		std::cout << "ERROR: Invalid Option Type Parameters";
		return 0;
	}
	return 0;
	*/

}