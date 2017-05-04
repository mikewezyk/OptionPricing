// Binomial Asset Pricing Project.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "Option.h"
#include "European.h"
#include "American.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

//#include <RInside.h>



void readCSV(std::istream &input, std::vector< std::vector<std::string> > &output)
{
    std::string csvLine;
    while( std::getline(input, csvLine) )
    {
        std::istringstream csvStream(csvLine);
        std::vector<std::string> csvColumn;
        std::string csvElement;
        while( std::getline(csvStream, csvElement, ',') )
        {
            csvColumn.push_back(csvElement);
        }
        output.push_back(csvColumn);
    }
}

int main(int argc, char* argv[])
{
//	std::string optionType;
//	bool RUN = true;
//	while (RUN == true){
//		std::cout << "Choose an option type from the following list: \n Put \n Call \n ";
//		std::getline(std::cin, optionType);
//		if (optionType == "Put" || optionType == "Call"){
//			RUN = false;
//		} 
//		else {
//			std::cout << "ERROR: Invalid Option Type \n";
//		}
//	}
//	std::string optionType2;
//	RUN = true;
//	while (RUN == true){
//		std::cout << "Choose an option type from the following list: \n American \n European \n ";
//		std::getline(std::cin, optionType2);
//		if (optionType2 == "American" || optionType2 == "European"){
//			RUN = false;
//		}
//		else {
//			std::cout << "ERROR: Invalid Option Type \n";
//		}
//	}

    


	double price;
    double rf;
    double volat;
	double K;
	std::string ticker;
	std::string optionExp;

	std::cout << "Enter a ticker: ";
	std::cin >> ticker;

	std::cout << "Enter an option expiration date (YYYY-MM-DD): ";
	std::cin >> optionExp;

	std::cout << "Enter the strike price of the option: ";
	std::cin >> K;

	
	/*RUN = true;
	while (RUN == true){
		std::cout << "One period of the model will equate for: \n Day \n Week \n Month ";
		std::getline(std::cin, period);
		if (period == "Day" || period == "Week" || period == "Month"){
			std::cin >> period;
			RUN = false;
		}
		else {
			std::cout << "ERROR: Invalid Period Type \n";
		}
	}*/

	std::fstream myfile;
	myfile.open ("writeOut.csv");
	myfile << ticker << std::endl;
	myfile << optionExp << std::endl;
	myfile <<  "" << std::endl;
	myfile.close();

    
	system("Rscript CalculateParameters.r");


	std::fstream myfile2;
	myfile2.open ("readIn.csv");

    std::fstream file("readIn.csv", std::ios::in);
    if(!file.is_open())
    {
        std::cout << "File not found!\n";
        return 1;
    }
    typedef std::vector< std::vector<std::string> > csvVector;
    csvVector csvData;
    
    std::vector<std::string> myDataVector;
    
    readCSV(file, csvData);
    for(csvVector::iterator i = csvData.begin(); i != csvData.end(); ++i)
    {
        for(std::vector<std::string>::iterator j = i->begin(); j != i->end(); ++j)
        {
            //std::cout << *j << ", ";
            myDataVector.push_back(*j);
        }
        std::cout << "\n";
    }
    
    
    price = std::stof(myDataVector.at(1));
    volat = std::stof(myDataVector.at(2));
    rf    = std::stof(myDataVector.at(3));
    
    std::cout << "Price: " << price << std::endl;
    std::cout << "volat: " << volat << std::endl;
    std::cout << "rf: " << rf << std::endl;



//	if (optionType2 == "American"){
//		American O = American(P, K, UP, DOWN, r, pUp, pDown, periods, optionType);
//		std::cout << "\nThe value of the option is: $" << O.getValue() << "\n";
//		std::cout << "Press ENTER to continue...";
//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	}
//	if (optionType2 == "European"){
//		European O = European(P, K, UP, DOWN, r, pUp, pDown, periods, optionType);
//		std::cout << "\nThe value of the option is: $" << O.getValue() << "\n";
//		std::cout << "Press ENTER to continue...";
//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	}
//	else {
//		std::cout << "ERROR: Invalid Option Type Parameters";
//		return 0;
//	}
	return 0;
}
