
#include <iostream>
#include "TimeCode.h"
#include <fstream>
#include <vector> 
#include <sstream>


using namespace std;


/* 
 * This function takes a string and a single character (delimiter).  
 * Returns a vector containing the sub-strings between any / all 
 * occurrences of the delimiter.
 */
vector<string> split(string lineData, char delim) {
	
	vector<string> tokens;
	
	istringstream iss(lineData); //zyBook 9.3 -- <sstream> -- reads input from a string instead of the keyboard
	
	string item;
	
	while (getline(iss, item, delim)) {
		
		tokens.push_back(item);
	}
	return tokens;
}


/* 
 * This function takes a line from the file (a string). Returns the 
 * TimeCode object for the time embedded in that line. 
 */
TimeCode parse_line(string lineData) {
	
	//this splits the line into vector of strings with delimiter ','
	vector<string> tokensLine;
	tokensLine = split(lineData, ',');
	
	TimeCode timeObj;
	
	//this splits and reads the UTC value (index 4 in the line) into the vector tokensUTC
	vector<string> tokensUTC;
	tokensUTC = split(tokensLine.at(4), ' ');
	
	//this reads the Hour & Minute value (index 2 in the vector UTC into tokensHrMin
	vector<string> tokensHrMin;
	//check if there is a time (size of vector UTC will be > 2) in the line
	if (tokensUTC.size() > 2) {
		tokensHrMin = split(tokensUTC.at(2), ':');
	
		//Convert string to int using stringstream class 
		int hour = 0;
		int min = 0;
		
		//easy way to convert string to int - https://www.geeksforgeeks.org/converting-strings-numbers-cc/
		stringstream convertHr(tokensHrMin.at(0)); 		//Object from class stringstream (<sstream>) convertHr
		convertHr >> hour; 								//stream it to the int hour
		
		stringstream convertMin(tokensHrMin.at(1));		//Object from class stringstream (<sstream>) convertMin
		convertMin >> min;								//stream it to the int min
		
		if (hour >= 0 && min >= 0 && min <= 59) {
			timeObj = TimeCode(hour, min, 0);
		}
	} else {
		return TimeCode(99, 0, 0); 		//I choose (99,0,0) because there're no such time in csv file
	}
	
	return timeObj;
}


int main() {
	
	ifstream MyReadFile("Space_Corrected.csv");
	//open and check if there's any error opening the file
	if (!MyReadFile.is_open()) {
      cout << "Could not open file Space_Corrected.csv." << endl;
      return 1;
	}
	
	double count = 0.0;
	string myLine;
	TimeCode timeObj;
	TimeCode totalTime;
	
	//iterate through the whole file to read each line into myLine
	while (getline(MyReadFile, myLine)) {
		
		timeObj = parse_line(myLine);
		//parse_line() will still return TimeCode(99,0,0) if it cannot detect timecode in the line
		
		if (timeObj != TimeCode(99,0,0)) {		
			totalTime = totalTime + timeObj;
			count ++;
		}
	}
	
	TimeCode avgTime;
	
	avgTime = totalTime / count;
	
	cout << count << " data points." << endl;
	cout << "AVERAGE: " << avgTime.ToString() << endl;
	
	MyReadFile.close();
	
	return 0;
}
