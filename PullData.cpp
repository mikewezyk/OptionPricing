#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main( int argc, char* argv[] )
{
	std::string ticker;
	std::string optionExp;
	//std::string end;
	int volatility;
	int up;
	int down;

	std::cout << "Enter a ticker: ";
	std::cin >> ticker;

	std::cout << "Enter an option expiration date (YYYY-MM-DD): ";
	std::cin >> optionExp;

	//std::cout << "Enter an end date (YYYY-MM-DD): ";
	//std::cin >> end;


	std::fstream myfile;
	myfile.open ("writeOut.csv");
	myfile << ticker << std::endl;
	myfile << optionExp << std::endl;
	myfile <<  "" << std::endl;
	//myfile << end << std::endl;
	myfile.close();

	system("Rscript historicData.R");


	std::fstream myfile2;
	myfile2.open ("readIn.csv");

	myfile2 >> volatility;
	myfile2 >> up;
	myfile2 >> down;


	myfile.close();

	std::cout << "Ticker: " << ticker << std::endl;
	std::cout << "optionExp: " << optionExp << std::endl;
	std::cout << "Volatility: " << volatility << std::endl;
	std::cout << "Up: " << up << std::endl;
	std::cout << "Down: " << down << std::endl;

	return 0;
}