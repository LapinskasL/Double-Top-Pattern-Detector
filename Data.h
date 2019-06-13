//Name:             Lukas Lapinskas
//Date:             4/29/2018
//Assignment:       Final Project
//Summary:          The code detects a double top pattern in given set(s)
//					of data, that are read from files, and writes results to 
//					other files.

// Data header file
#ifndef DATA_H
#define DATA_H

#include <string>
#include <fstream>

// Data class declaration
class Data
{
private:
	// holds one row of a file (date, adj_close, and volume values).
	std::string date;
	double adj_close;
	long volume;

	// holds converted and reordered date (year + month + day)
	int dateInt;
	// holds bool value of whether or not reorderDate function ran
	bool reordered = false;

	// reorderDate function prototype;
	int reorderDate(std::string);

public:
	// @@@ mutators/setters

	// sets date variable value
	// PRECONDITION: date parameter has to be a string value
	// POSTCONDITION: date member variable will contain a string value
	void setDate(std::string date) { this->date = date; }

	// PRECONDITION: adj_close parameter has to be a double value
	// POSTCONDITION: adj_close member variable will contain a double value
	// sets adj_close variable value

	void setAdj_close(double adj_close) { this->adj_close = adj_close; }
	// PRECONDITION: volume parameter has to be a long value
	// POSTCONDITION: volume member variable will contain a long value
	// sets volume variable value
	void setVolume(long volume) { this->volume = volume; }


	// @@@ accessors/getters

	// PRECONDITION: date must contain a string value
	// POSTCONDITION: the function will return value of member variable date
	std::string getDate() { return date; }

	// PRECONDITION: adj_close must contain a double value
	// POSTCONDITION: the function will return value of member variable adj_close
	double getAdj_close() { return adj_close; }

	// PRECONDITION: volume must contain a long value
	// POSTCONDITION: the function will return value of member variable volume
	long getVolume() { return volume; }

	// friend function of extraction operator overload
	friend std::ifstream& operator >> (std::ifstream&, Data&);

	// friend declaration of insertion operator overload function 
	friend std::ofstream& operator << (std::ofstream&, Data&);

	// operator < overload prototype
	bool operator < (Data&);
	// operator > overload prototype
	bool operator > (Data&);
	// operator == overload prototype
	bool operator == (Data&);
};



#endif // !DATA_H