
#include <iostream>
#include <string> 
#include "TimeCode.h"

using namespace std;


TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
	
	this->SetHours(hr);
	this->SetMinutes(min);
	this->SetSeconds(sec);
}


TimeCode::TimeCode(const TimeCode& tc) {
	
	this->t = tc.t;
}


void TimeCode::SetHours(unsigned int hours) {
	
	if (static_cast<int>(hours) < 0) {
		throw invalid_argument("Negative arguments not allowed: " + to_string(static_cast<int>(hours)));
	}
	
	this->t += hours * 3600;
}


void TimeCode::SetMinutes(unsigned int minutes) {
	
	if (minutes > 59) {
		throw invalid_argument("Invalid argument: Number of minutes has to be < 60!!!");
		
	}
	if (static_cast<int>(minutes) < 0) {
		throw invalid_argument("Negative arguments not allowed: " + to_string(static_cast<int>(minutes)));
		
	}
	
	this->t += minutes * 60;
}


void TimeCode::SetSeconds(unsigned int seconds) {
	
	if (seconds > 59) {
		throw invalid_argument("Invalid argument: Number of seconds has to be < 60!!!");
	}
	
	if (static_cast<int>(seconds) < 0) {
		throw invalid_argument("Negative arguments not allowed: " + to_string(static_cast<int>(seconds)));
	}
	
	this->t += seconds;
}


void TimeCode::reset() {
	
	SetHours(0);
	SetMinutes(0);
	SetSeconds(0);
}


unsigned int TimeCode::GetHours() const {
	
	return t / 3600;
}


unsigned int TimeCode::GetMinutes() const {
	
	return (t % 3600) / 60;
}


unsigned int TimeCode::GetSeconds() const {
	
	return (t % 3600) % 60;
}


void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
	
	hr = this->t / 3600;
	min = (this->t % 3600) / 60;
	sec = (this->t % 3600) % 60;
	
}


long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec) {
	
	return hr * 3600 + min * 60 + sec;
	
}


string TimeCode::ToString() const {
	
	return to_string(this->GetHours()) + ":" + to_string(this->GetMinutes()) + ":" + to_string(this->GetSeconds());
}


TimeCode TimeCode::operator+(const TimeCode& other) const {
	
	TimeCode total;
	
	total.t = this->t + other.t;
	
	return total;
}


TimeCode TimeCode::operator-(const TimeCode& other) const {
	
	TimeCode subtraction;
	
	if (this->t > other.t) {
		subtraction.t = this->t - other.t;
		return subtraction;
		
	} else {
		throw invalid_argument("Negative results not allowed!!!");
	
	}
}


TimeCode TimeCode::operator*(double a) const {
	
	TimeCode product;
	
	if (a >= 0.0) {
		product.t = this->t * a;
		
	} else {
		throw invalid_argument("Negative results not allowed!!!" + to_string(a));
	}

	return product;
}


TimeCode TimeCode::operator/(double a) const {
	
	TimeCode division;
	
	if (a == 0.0 || a < 0.0) {
		throw invalid_argument("Zero or negative argument not allowed in division: " + to_string(a));
		
	} else {
		division.t = this->t / a;
		
	}
	return division;
}


bool TimeCode::operator == (const TimeCode& other) const {
	
	return (this->t == other.t);
}


bool TimeCode::operator != (const TimeCode& other) const {
	
	return (this->t != other.t);
}


bool TimeCode::operator < (const TimeCode& other) const {
	
	return (this->t < other.t);
}


bool TimeCode::operator <= (const TimeCode& other) const {
	
	return (this->t <= other.t);
}


bool TimeCode::operator > (const TimeCode& other) const {
	
	return (this->t > other.t);
}


bool TimeCode::operator >= (const TimeCode& other) const {
	
	return (this->t >= other.t);
}






