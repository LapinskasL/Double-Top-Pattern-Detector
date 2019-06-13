//Name:             Lukas Lapinskas
//Date:             4/29/2018
//Assignment:       Final Project
//Summary:          The code detects a double top pattern in given set(s)
//					of data, that are read from files, and writes results to 
//					other files.

// DataContainer header file
#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Data.h"

class DataContainer {
private:
	// vector to hold Data objects
	std::vector<Data> v;

	// holds ticker
	std::string ticker;

	// holds indexes of double top peak1, valley, and peak2
	int peak1Index;
	int valleyIndex;
	int peak2Index;

	// holds values of peak1, valley, and peak2
	double peak1;
	double valley;
	double peak2;

	// holds false if algorithm hasn't ran yet, true if it has.
	// This is so that the object does not have to run the
	// algorithm more than once.
	bool alreadyCalced = false;

	// holds false if object has a double top, holds false if not.
	bool hasDoubleTop = false;


	// second part of algorithm
	int i = 0;
	// constant 5% value
	const double fivePerc = 0.05;

	double newHigh;
	// holds current value (used to find a potential valley)
	double currentVal;
	// boolean valleySet (defines whether or not a potential valley was found)
	bool valleySet = false;

	// calcDoubleTop2 prototype
	void calcDoubleTop2();
	// calcDOubleTop prototype
	void calcDoubleTop();
	// bubbleSortDate prototype
	void bubbleSortDate();

public:
	// DataContainer constructor prototype
	DataContainer(std::ifstream&, std::string);

	// gets ticker variable value
	// PRECONDITION: ticker must contain a string value.
	// POSTCONDITION: this function will return that string value
	std::string getTicker() { return ticker; }

	// doubleTop prototype
	bool doubleTop();
	// getValley prototype
	double getValley();
	// getPeak1 prototype
	double getPeak1();
	// getPeak2 prototype
	double getPeak2();
	// createFile prototype
	void createFile();
};

#endif // !DATACONTAINER_H