/*
**      NAME: AVINASH SINGH
**      COURSE: OOP345
**      DATE: 
**      WORKSHOP 2
**      FILE: Stations.h
*/
#ifndef W2_STATIONS_H__
#define W2_STATIONS_H__

#include "Station.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

namespace w2 {
	class Stations : public Station {
		string stations_;
		int number_of_stations;
		int file_student_passes, file_adult_passes;
	public:
		Stations(char* s);
		~Stations();
		void update() const;
		void restock() const;
		void report() const;
	};
}

#endif