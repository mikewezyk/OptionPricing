#include "stdafx.h"
#include "Data.h"
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

void Data::readCSV(std::istream &input, std::vector< std::vector<std::string> > &output){
	std::string csvLine;
	while (std::getline(input, csvLine))
	{
		std::istringstream csvStream(csvLine);
		std::vector<std::string> csvColumn;
		std::string csvElement;
		while (std::getline(csvStream, csvElement, ','))
		{
			csvColumn.push_back(csvElement);
		}
		output.push_back(csvColumn);
	}
}

Data::Data(std::string tick, std::string expiration)
{
	ticker = tick;
	expDate = expiration;
	
	//R SCRIPT GOES HERE CALLING TICK AND EXP
	std::fstream myfile;
	myfile.open("writeOut.csv");
	myfile << ticker << std::endl;
	myfile << expiration << std::endl;
	myfile << "" << std::endl;
	myfile.close();

	std::cout << "RUN THE R SCRIPT NOW" << std::endl;
	std::cout << "Press ENTER to continue...";

	std::fstream myfile2;
	myfile2.open("readIn.csv");

	std::fstream file("readIn.csv", std::ios::in);
	if (!file.is_open())
	{
		std::cout << "File not found!\n";
	}
	typedef std::vector< std::vector<std::string> > csvVector;
	csvVector csvData;

	std::vector<std::string> myDataVector;

	readCSV(file, csvData);
	for (csvVector::iterator i = csvData.begin(); i != csvData.end(); ++i)
	{
		for (std::vector<std::string>::iterator j = i->begin(); j != i->end(); ++j)
		{
			//std::cout << *j << ", ";
			myDataVector.push_back(*j);
		}
		std::cout << "\n";
	}

	//VALUES FROM R WILL DEFINE PARAMETERS BELOW
	volatility = std::stof(myDataVector.at(2));
	n = std::stof(myDataVector.at(4));
	S0 = std::stof(myDataVector.at(1));
	r = std::stof(myDataVector.at(3));
	upfactor = exp(volatility*sqrt(deltaT));
	downfactor = exp(-volatility*sqrt(deltaT));
	pUp = (1.0 + exp(r*deltaT) -downfactor)/(upfactor - downfactor);
	pDown = 1.0 - pUp;
	//TO BE CHANGED BUT WILL BE DEFAULTED TO 1/252
	deltaT = 1/252;
}