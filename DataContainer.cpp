//Name:             Lukas Lapinskas
//Date:             4/29/2018
//Assignment:       Final Project
//Summary:          The code detects a double top pattern in given set(s)
//					of data, that are read from files, and writes results to 
//					other files.

// DataContainer.cpp file
#include "DataContainer.h"

//@@@@@@@@@ PRIVATE FUNCTIONS @@@@@@@@@@

// second part of algorithm
// PRECONDITION: variables newHigh and valley must contain a value.
// POSTCONDITION: boolean member variable hasDoubleTop will be set to true if
// the adj_close dataset contains a double-top pattern.
void DataContainer::calcDoubleTop2() {
	// index of valley stored
	valleyIndex = i;
	int c = i;
	// as long as vector is not out of bounds and previous element not more than newHigh (this further
	// defines potential peak1 and valley).
	while (c < v.size() && !(v[c - 1].getAdj_close() > newHigh) && (hasDoubleTop == false)) {
		// if element is mroe than newHigh
		if (v[c].getAdj_close() > newHigh) {
			// peak1Index stored
			peak1Index = c;
			c++;
		}
		//
		// if current element is less than valley
		if (v[c].getAdj_close() < valley) {
			// valley value is updated
			valley = v[c].getAdj_close();
			// index of valley updated
			valleyIndex = c;
		}
		// else if valley is not more than current value,
		else {
			// if the rise of second peak is between 5 and 7%,
			if ((v[c].getAdj_close() >= valley * (fivePerc + 1)) && (hasDoubleTop == false) &&
				!(v[c].getAdj_close() >= valley * (fivePerc + 1.02))) {
				// peak2 index is stored
				peak2Index = c;
				// peak2 value is stored
				peak2 = v[c].getAdj_close();
				//
				int q = c;
				//bool valleyReset = false;
				// while vector not out of bounds
				while (q < v.size() && (hasDoubleTop == false)) {
					int t = q;
					while ((t < v.size() - 1) && (v[t + 1].getAdj_close() > peak2)) {
						peak2 = v[t + 1].getAdj_close();
						peak2Index = t + 1;
						t++;
					}
					// if peak2 is more than peak1
					if ((peak2 > peak1)) {
						// valley is reset (because peak2 will become peak1, since peak2 was
						// higher than peak1).
						i = valleyIndex;
						valleySet = false;
						//peak1Index = q;
					}
					// if current value is less than valley (if peak2 drop below neck-line)
					if (v[q].getAdj_close() < valley) {
						int p = peak1Index - 1;
						bool peak1RiseGood = false;
						// while loop checks if peak1 left slope goes below neck-line
						while ((p > -1) && (peak1RiseGood == false)) {
							if (v[p].getAdj_close() <= valley) {
								peak1RiseGood = true;
							}
							p--;
						}
						// if peak1 left slope goes below neck line, peak1 is confirmed and
						// hasDoubleTop is set to true (data set contains a double-top pattern).
						if (peak1RiseGood == true) {
							peak1 = v[peak1Index].getAdj_close();
							hasDoubleTop = true;
						}
					}
					q++;
				}
			}
		}
		c++;
	}
}


// first part of algorithm
// PRECONDITION: member vector v must be a vector of Data objects and 
// contain at least one element.
// POSTCONDITION: alreadyCalced boolean member variable will be set to true.
void DataContainer::calcDoubleTop() {

	// @@@ algorithm begins here
	// while not end of vector and a double top has not been found
	while (i < v.size() && (hasDoubleTop == false)) {
		// assign an element to start the search from
		currentVal = v[i].getAdj_close();

		// if current value is more than new high, save index that may be peak1 and 
		// update newHigh.
		if (currentVal > newHigh) {
			newHigh = currentVal;
			peak1Index = i;
		}

		// if statement runs (if needed) after valley has been set for the first time and
		// currentVal is less than or equal to 95% of newhigh, and currentVal is less than
		// valley. (this finds the drop slope of potential peak1)
		if ((valleySet == true) &&
			(currentVal <= newHigh * (1 - fivePerc)) &&
			(currentVal < valley)) {
			valley = currentVal;
			calcDoubleTop2();
		}

		// if statement runs first if valley has not been set for the first time and
		// currentVal is less than or equal to 95% of newhigh (this finds the drop 
		// slope of potential peak1)
		if ((valleySet == false) &&
			(currentVal <= newHigh * (1 - fivePerc))) {
			valley = currentVal;
			valleySet = true;
			calcDoubleTop2();
		}
		i++;
	}
	// set to true after function finishes calculations
	alreadyCalced = true;
	// @@@ algorithm ends here
}

// PRECONDITION: v member vector must have at least two unsorted elements for swapping
// to occur.
// POSTCONDITION: all the elements in v vector will be sorted based by their date member
// variables in ascending order.
void DataContainer::bubbleSortDate() {
	bool swap;
	Data temp;

	do {
		swap = false;
		// loop through every element in v vector
		for (int i = 0; i < (v.size() - 1); i++) {
			// if an element is larger than the next element, swap them.
			if ((v[i] > v[i + 1]) && (v.size() > 1)) {
				temp = v[i];
				v[i] = v[i + 1];
				v[i + 1] = temp;
				swap = true;
			}
		}
		// run until for loop iterates through every element without a swap occuring.
	} while (swap);
}








//@@@@@@@@@@@@@ PUBLIC FUNCTIONS @@@@@@@@@@@@@

// constructor
// PRECONDITION: infile must be open and ticker must be a string
// POSTCONDITION: ticker member variable will contain ticker of stock,
// dataObj will contain a line of data (date, adj_close, volume), dataObj
// objects will be pushed back to v member array, and bubbleSortDate 
// algorithm will be called.
DataContainer::DataContainer(std::ifstream& infile, std::string ticker) {
	// holds line that's skipped
	std::string skipLine;
	// skip first line of file (column names);
	std::getline(infile, skipLine);

	Data dataObj;
	// while there are lines to read, push_back each line (Data object)
	// to vector of Data.
	while (infile >> dataObj) {
		v.push_back(dataObj);
		Data dataObj;
	}

	// assign the value of parameter ticker to member variable ticker.
	this->ticker = ticker;

	// run bubble sort to make sure objects are sorted by date.
	bubbleSortDate();
}

// hasDoubleTop function calculates double top and/or returns whether or not one exists.
// PRECONDITION: the only precondition is a DataContainer object must exist.
// POSTCONDITION: will return either true or false if calcDoubleTop function
// ran once, if calcDoubleTop function never ran then will return either true or false 
// calcDoubleTop after running it.
bool DataContainer::doubleTop() {
	if (alreadyCalced) {
		return hasDoubleTop;
	}
	else {
		calcDoubleTop();
		return hasDoubleTop;
	}
}

// returns valley if object has double top, otherwise returns -1 (represents empty)
// PRECONDITION: the only precondition is a DataContainer object must exist.
// POSTCONDITION: This function will either return the value of valley member variable
// or -1.
double DataContainer::getValley() {
	if (hasDoubleTop) {
		return valley;
	}
	else {
		// -1 (represents empty)
		return -1;
	}
}

// returns peak1 if object has double top, otherwise returns -1 (represents empty)
// PRECONDITION: the only precondition is a DataContainer object must exist.
// POSTCONDITION: This function will either return the value of peak1 member variable
// or -1.
double DataContainer::getPeak1() {
	if (hasDoubleTop) {
		return peak1;
	}
	else {
		return -1;
	}
}


// returns peak2 if object has double top, otherwise returns -1 (represents empty)
// PRECONDITION: the only precondition is a DataContainer object must exist.
// POSTCONDITION: This function will either return the value of peak2 member variable
// or -1.
double DataContainer::getPeak2() {
	if (hasDoubleTop) {
		return peak2;
	}
	else {
		return -1;
	}
}

// PRECONDITION: For the function to successfully create a file for a ticker, the object must
// have hasdoubleTop boolean set to true. Otherwise, the inside of the if statement does not run.
// POSTCONDITION: if the hasDoubleTop boolean value is true, a file will be written to 
// data_files folder that will be named ticker + "-final.csv". The file will contain
// a row of column names, and one more row consisting of file name, peak1 value, peak2 value,
// and valley value.
//.
void DataContainer::createFile() {
	if (hasDoubleTop) {
		// create a Data object
		Data dataObj;
		// open file for writing
		std::ofstream outfile("../data_files/" + ticker + "-final.csv");
		// write row of column names
		outfile << "file name," << "peak 1," << "valley," << "peak 2" << std::endl;
		// write second row of file name, peak1, valley, and peak 2 values.
		outfile << ticker + ".csv" << ",";
		dataObj = v[peak1Index];
		outfile << dataObj << ",";
		dataObj = v[valleyIndex];
		outfile << dataObj << ",";
		dataObj = v[peak2Index];
		outfile << dataObj << std::endl;
		// close file.
		outfile.close();
	}
}