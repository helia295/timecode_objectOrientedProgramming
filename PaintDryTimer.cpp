
//g++ -std=c++11 -Wall -Wc++11-extensions TimeCode.cpp PaintDryTimer.cpp -o pdt

#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include <sstream>
#include "TimeCode.h" // for timecode's (duh)

using namespace std;


struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};


long long int get_time_remaining(DryingSnapShot dss){
	
	//get the current time
	time_t currTime;
	currTime = time(0);
	
	//calculate the duration
	time_t duration;
	duration = (currTime - dss.startTime);
	unsigned long long int durationInt = static_cast<unsigned long long int>(duration);
	
	//calculate the time remaining in seconds
	long long unsigned int timeDry = (dss.timeToDry)->GetTimeCodeAsSeconds();
	
	if (durationInt < timeDry) {
		
		long long unsigned int timeRemaining = timeDry - durationInt;
		
		return timeRemaining;
		
	} else {
		
		return -1;
	}
}


string drying_snap_shot_to_string(DryingSnapShot dss){
	
	long long int timeRemain = get_time_remaining(dss);
	
	TimeCode Remaining = TimeCode(0, 0, timeRemain);
	
	return dss.name + " (takes " + (*(dss.timeToDry)).ToString() + " to dry) time remaining: " + Remaining.ToString();
	
}


double get_sphere_sa(double rad){
	
	if (rad < 0.0) {
		throw invalid_argument("Negative arguments not allowed!");
	}
	
	double sa;
	
	sa = 4.0 * M_PI * rad * rad;
	
	return sa;
}


TimeCode *compute_time_code(double surfaceArea){
	
	TimeCode *timeDry;
	
	timeDry = new TimeCode(0, 0, static_cast<long long unsigned int>(surfaceArea));
	
	return timeDry;
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here

	
	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here

	
	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;
	

	// add more tests here*/


	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	//tests();
	
	istringstream inSS;       // Input string stream
	
	bool   inputDone;         // Flag to indicate next iteration
	inputDone = false;
	
	vector<DryingSnapShot> vecSS;
	
	string lineString;
	cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
	
	while (!inputDone) {
      
		// Entire line into lineString
		cin >> lineString;
		
		if (lineString == "a" || lineString == "A") {
			
			DryingSnapShot dss;
			double radius;
			
			cout << "Enter radius: ";
			cin >> radius;
			
			//Create a dss object
			dss.name = "Batch-" + to_string(rand());
			dss.startTime = time(0);
			dss.timeToDry = compute_time_code(get_sphere_sa(radius));
			
			//print the new dss object out and push it to the vector
			cout << drying_snap_shot_to_string(dss) << endl;
			vecSS.push_back(dss);
			
		} else if (lineString == "v" || lineString == "V") {
			
			//case: there are some dss still drying
			if (vecSS.size() >= 1) {
			
				for (unsigned int i = 0; i < vecSS.size(); i++) {
				
					if (get_time_remaining(vecSS.at(i)) != -1) { 	//if still drying
						
						cout << drying_snap_shot_to_string(vecSS.at(i)) << endl;
						
					}
					if (get_time_remaining(vecSS.at(i)) == -1) { 	//if it's finished drying
						
						delete vecSS.at(i).timeToDry;
						vecSS.erase(vecSS.begin()+i);
						i--;
					}
				}
				cout << vecSS.size() << " batch(es) being tracked." << endl;
			}
			//case: none dss left to dry
			if (vecSS.size() < 1) {
				
				cout << "No batch left to dry! Add more or Exit!" << endl;
				
			}
			
		} else if (lineString == "q" || lineString == "Q") {
			
			vecSS.clear();
			
			inputDone = false;
			
			cout << "Quitting..." << endl;
			
			break;
			
		} else {
			
			cout << "Invalid input!!!" << endl;
		}
		
		cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
		
	}
	
	return 0;
}
