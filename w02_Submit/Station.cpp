/*
**      NAME: AVINASH SINGH
**      COURSE: OOP345
**      DATE:
**      WORKSHOP 2
**      FILE: Station.cpp
*/
#include "Station.h"

Station::Station() {
	station_ = '\0';
}

void Station::set(const string & station, unsigned int student_, unsigned int adult_) {
	station_ = station;
	student_passes = student_;
	adult_passes = adult_;
}

void Station::update(PassType station_passes, int numOfPasses) {
	switch (station_passes) {
	case student: student_passes += numOfPasses; break;
	case adult: adult_passes += numOfPasses; break;
	}
}

unsigned Station::inStock(PassType station_passes) {
	unsigned int res = 0;
	switch (station_passes)
	{
	case student:
		res = student_passes;
		break;
	case adult:
		res = adult_passes;
		break;
	default:
		break;
	}

	return res;
}

const string & Station::getName() const {
	return station_;
}
