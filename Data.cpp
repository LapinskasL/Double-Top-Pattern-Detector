//Name:             Lukas Lapinskas
//Date:             4/29/2018
//Assignment:       Final Project
//Summary:          The code detects a double top pattern in given set(s)
//					of data, that are read from files, and writes results to 
//					other files.

// Data.cpp file
#include "Data.h"


//@@@@@@@@@@@@@ PRIVATE FUNCTIONS @@@@@@@@@@@@@

// this private member function extracts month, day, and year from
// a string, stores them in year + month + day order in another
// string variable, and returns the contents converted to an int.
// PRECONDITION: dateVar parameter must have at least 1 digit and two '/' chars
// and no other symbols.
// POSTCONDITION: the variable value returned by the function (dateInt) 
// will contain only digits.
int Data::reorderDate(std::string dateVar) {
	// if reorderDate has already ran once, the dateInt value is returned
	// so that date variable wouldn't have to be converted a second time.
	if (reordered) {
		return dateInt;
	}
	else {
		// temporarily holds month, day, and year digits
		std::string month = "";
		std::string day = "";
		std::string year = "";

		// holds string that will be converted to int
		std::string tempStr = "";
		int i = 0;

		// add chars to month variable until '/' char is reached
		while (dateVar[i] != '/') {
			month += dateVar[i];
			i++;
		}
		i++;
		// if month is only one digit, adds a 0 before the number
		if (month.size() == 1) {
			tempStr = month[0];
			month = "0" + tempStr;
		}

		// add chars to day variable until '/' char is reached
		while (dateVar[i] != '/') {
			day += dateVar[i];
			i++;
		}
		i++;
		// if day is only one digit, adds a 0 before the number
		if (day.size() == 1) {
			tempStr = day[0];
			day = "0" + tempStr;
		}

		// add chars to year variable until end of string is reached
		while (i != dateVar.size()) {
			year += dateVar[i];
			i++;
		}

		// orders year first, month second, and day last
		std::string dateStr = year + month + day;
		// converts dateInt to an intiger type so dates can be compared
		dateInt = std::stoi(dateStr);

		return dateInt;
	}
}

//@@@@@@@@@@ PUBLIC FUNCTIONS @@@@@@@@@@@@@

// less than operator overload based on date variable
// PRECONDITION: object on the right must be of Data type and contain a value in 
// date member variable.
// POSTCONDITION: will return true if thisDate is less than rightDate, false otherwise.
bool Data::operator < (Data& rightObj) {
	// get this object's date reordered and converted to integer
	int thisDate = reorderDate(date);
	// get rightObj date reordered and converted to integer
	int rightDate = reorderDate(rightObj.getDate());

	// return true if this object's date is less than rightObj, false otherwise.
	if (thisDate < rightDate) {
		return true;
	}
	else {
		return false;
	}
}

// more than operator overload based on date variable
// PRECONDITION: object on the right must be of Data type and contain a value in
// date member variable.
// POSTCONDITION: will return true if thisDate is more than rightDate, false otherwise.
bool Data::operator > (Data& rightObj) {
	// get this object's date reordered and converted to integer
	int thisDate = reorderDate(date);
	// get rightObj date reordered and converted to integer
	int rightDate = reorderDate(rightObj.getDate());

	// return true if this object's date is more than rightObj, false otherwise.
	if (thisDate > rightDate) {
		return true;
	}
	else {
		return false;
	}
}

// equal to operator overload based on date variable
// PRECONDITION: object on the right must be of Data type and contain a value in
// date member variable.
// POSTCONDITION: will return true if thisDate is equal to rightDate, false otherwise.
bool Data::operator == (Data& rightObj) {
	// get this object's date reordered and converted to integer
	int thisDate = reorderDate(date);
	// get rightObj date reordered and converted to integer
	int rightDate = reorderDate(rightObj.getDate());

	// return true if this object's date is equal to rightObj, false otherwise.
	if (thisDate == rightDate) {
		return true;
	}
	else {
		return false;
	}
}

//@@@@@@@@@@ FRIEND FUNCTIONS @@@@@@@@@@@@@@@@@

// overloaded extraction operator function.
// Reads entire line from file.
// PRECONDITION: object on the right must be of Data type.
// POSTCONDITION: Data object will contain a value in date, adj_close, and
// volume member variables.
std::ifstream& operator >> (std::ifstream& in, Data& obj) {
	std::string tempStr;

	// maximum value a long can hold
	long maxLong = std::numeric_limits<long>::max();

	// set date
	getline(in, tempStr, ',');
	obj.setDate(tempStr);

	// if tempStr (date) was not empty, read the rest of line.
	// The reason for this is so that stod and stoll don't attempt
	// to convert an empty string.
	if (tempStr != "") {
		// set adj_close
		getline(in, tempStr, ',');
		obj.setAdj_close(stod(tempStr));

		// set volume
		getline(in, tempStr);

		try
		{
			obj.setVolume(stol(tempStr));
		}
		// if an out_of_range error occurs for stol(), maximum long value is
		// set instead
		catch (std::out_of_range)
		{
			obj.setVolume(maxLong);
		}
	}
	return in;
}

// overloaded insertion operator function.
// Writes adj_close variable value to file.
// PRECONDITION: object on the right must be of Data type and contain a
// value in adj_close memeber variable.
// POSTCONDITION: this function will write a value to the output file
std::ofstream& operator << (std::ofstream& out, Data& obj) {
	out << obj.getAdj_close();

	return out;
}