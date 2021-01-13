
#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	// Random but "safe" inputs
	
	TimeCode tc2 = TimeCode(3, 17, 42);
	//cout << "tc2: " << tc2.ToString() << endl;
	assert(tc2.ToString() == "3:17:42");
	
	// More tests go here!
	TimeCode tc3 = TimeCode(tc2);
	assert(tc3.ToString() == "3:17:42");
	
	try {
		TimeCode tc4 = TimeCode(3, 17, 62);
		//cout << "tc4: " << tc4.ToString() << endl;
		assert(false);
		
	} catch(const invalid_argument& e) {
		// just keep doing more tests
	}
	
	try {
		TimeCode tc5 = TimeCode(-3, 17, 6);
		//cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
		
	} catch(const invalid_argument& e) {
		// just keep doing more tests
	}
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestAddition(){
	cout << "Testing Addition" << endl;
	TimeCode tc1 = TimeCode(1, 10, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 + tc2;
	assert(tc3.ToString() == "2:0:0");
	
	TimeCode tc4 = TimeCode(1, 10, 59);
	TimeCode tc5 = TimeCode(0, 50, 1);
	TimeCode tc6 = tc4 + tc5;
	assert(tc6.ToString() == "2:1:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just keep doing more tests
	}

	// more tests
	
	cout << "PASSED!" << endl << endl;
}


void TestProduct(){
	cout << "Testing Product" << endl;
	TimeCode tc1 = TimeCode(1, 10, 0);
	TimeCode tc2 = TimeCode(0, 50, 43);
	TimeCode tc3 = tc1 * 2.0;
	assert(tc3.ToString() == "2:20:0");
	
	TimeCode tc4 = tc1 * 0.0;
	assert(tc4.ToString() == "0:0:0");
	
	try{
		TimeCode tc5 = tc1 * (-32);
		//cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just keep doing more tests
	}
	
	TimeCode tc6 = tc2 * 3.3;
	//cout << "tc6: " << tc6.ToString() << endl;
	assert(tc6.ToString() == "2:47:21");
	
	cout << "PASSED!" << endl << endl;
}


void TestDivision(){
	cout << "Testing Division" << endl;
	TimeCode tc1 = TimeCode(1, 10, 0);
	TimeCode tc2 = TimeCode(0, 50, 43);
	TimeCode tc3 = tc1 / 2.0;
	assert(tc3.ToString() == "0:35:0");
	
	try {
		TimeCode tc4 = tc1 / 0.0;
		assert(false);
	} catch(const invalid_argument& e){
		
	}
	
	try{
		TimeCode tc4 = tc1 * (-32);
		//cout << "tc4: " << tc4.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just keep doing more tests
	}
	
	TimeCode tc5 = tc2 / 3.5;
	//cout << tc5.ToString() << endl;
	assert(tc5.ToString() == "0:14:29");
	
	
	cout << "PASSED!" << endl << endl;
}


void TestComparisonOperators() {

	TimeCode tc1 = TimeCode(1, 10, 0);
	TimeCode tc2 = TimeCode(0, 50, 43);
	TimeCode tc3 = TimeCode(1, 10, 0);
	TimeCode tc4 = TimeCode(5, 53, 43);
	
	cout << "Testing Operator (==) & (!=)" << endl;
	assert(tc1 == tc3);
	assert(tc1 != tc2);
	
	cout << "Testing Operator (<) & (<=)" << endl;
	assert(tc1 < tc4);
	assert(tc1 <= tc1);
	assert(tc2 <= tc3);
	
	cout << "Testing Operator (>) & (>=)" << endl;
	assert(tc1 >= tc3);
	assert(tc1 >= tc2);
	assert(tc4 > tc3);
	
	cout << "PASSED!" << endl << endl;
}


// Test GetHours
void TestGetHours() {
	
	cout << "Testing Get Hours" << endl;
	TimeCode tc1 = TimeCode(1, 10, 0);
	TimeCode tc2 = TimeCode(0, 50, 43);
	TimeCode tc3 = tc1 * 2.0;
	//assert(tc3.ToString() == "2:20:0");
	assert(tc3.GetHours() == 2);
	
	TimeCode tc4 = tc1 * 0.0;
	//assert(tc4.ToString() == "0:0:0");
	assert(tc4.GetHours() == 0);
	
	TimeCode tc5 = tc2 * 3.3;
	//cout << "tc5: " << tc6.ToString() << endl;
	//assert(tc5.ToString() == "2:47:21");
	assert(tc5.GetHours() == 2);
	
	cout << "PASSED!" << endl << endl;
	
}


// Test GetMinutes
void TestGetMinutes() {
	
	cout << "Testing Get Minutes" << endl;
	TimeCode tc1 = TimeCode(1, 10, 0);
	TimeCode tc2 = TimeCode(0, 50, 43);
	
	TimeCode tc3 = tc1 * 2.0;
	assert(tc3.GetMinutes() == 20);
	
	TimeCode tc4 = tc1 * 0.0;
	assert(tc4.GetMinutes() == 0);
	
	TimeCode tc5 = tc2 * 3.3;
	//cout << "tc5: " << tc6.ToString() << endl;
	assert(tc5.GetMinutes() == 47);
	
	cout << "PASSED!" << endl << endl;
	
}


void TestGetSeconds() {
	
	cout << "Testing Get Seconds" << endl;
	TimeCode tc1 = TimeCode(1, 10, 0);
	TimeCode tc2 = TimeCode(0, 50, 43);
	
	TimeCode tc3 = tc1 * 2.0;
	assert(tc3.GetSeconds() == 0);
	
	TimeCode tc4 = tc1 * 0.0;
	assert(tc4.GetSeconds() == 0);
	
	TimeCode tc5 = tc2 * 3.3;
	assert(tc5.GetSeconds() == 21);
	
	cout << "PASSED!" << endl << endl;
	
}

	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestAddition();
	TestSubtract();
	TestProduct();
	TestDivision();
	TestComparisonOperators();
	TestGetHours();
	TestGetMinutes();
	TestGetSeconds();

	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
