//Name:             Lukas Lapinskas
//Date:             4/29/2018
//Assignment:       Final Project
//Summary:          The code detects a double top pattern in given set(s)
//					of csv data. The results of the detection are written in
//					the same folder, in the file called FILETESTED-final.csv.
//					The data file to be tested must be in data_files folder and the
//					file's name must be in the names.csv.
//					All csv files were downloaded from https://finance.yahoo.com.

#include "DataContainer.h"

using namespace std;

int main()
{
	// vector to hold DataContainer objects
	vector<DataContainer> fileVector;

	// open name.csv for reading
	ifstream namesFile("../data_files/names.csv");

	// displays and error message if names.csv does not open
	if (!namesFile.is_open()) {
		cout << "Error opening names.csv!" << endl;
	}

	// variable to hold ticker from names.csv
	string tempFileName;

	// get line and store it in tempFileName variable while names.csv is open
	while ((namesFile.is_open()) && (getline(namesFile, tempFileName))) {
		// open file for reading
		ifstream infile("../data_files/" + tempFileName + ".csv");
		// if file does not open, display an error message with file's name
		if (infile.fail()) {
			cout << "Failed to open " + tempFileName + ".csv" << endl;
		}
		// if file opens...
		else {
			// create a DataContainer object
			DataContainer dataContainerObj(infile, tempFileName);
			// push DataContainer object to fileVector
			fileVector.push_back(dataContainerObj);
		}
	}

	// if fileVector contains elements and names.csv file is open..
	if ((fileVector.size() > 0) && (namesFile.is_open())) {
		// open status.csv for writing
		ofstream statusFile("../data_files/status.csv");
		// write column names
		statusFile << "Ticker,Double-top?" << endl;
		for (int i = 0; i < fileVector.size(); i++) {
			// write whether or not each file has a double-top pattern.
			statusFile << fileVector[i].getTicker() << ",";
			// if file has a double top
			if (fileVector[i].doubleTop()) {
				// write "Yes" in status.csv
				statusFile << "Yes" << endl;
				// write the individual file for double top.
				fileVector[i].createFile();
			}
			else {
				// write "No" in status.csv
				statusFile << "No" << endl;
			}
		}
	}

	// close namesFile
	namesFile.close();
	system("pause");
	return 0;
}
