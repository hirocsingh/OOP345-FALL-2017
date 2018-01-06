/*
	File:	w1.cpp
	Author:	Avinash Singh
	Date:	5-SEP-2017
	Course: OOP345
*/

#include "process.h"
#include <iostream>

extern const int MAX_CHAR;
int main(int argc, char *argv[])
{
	if (argc > 1) {
		std::cout << "Maximum number of characters stored : " << MAX_CHAR << std::endl;
		int i = 0;
		for (i = 1; i < argc; i++) {
			process(argv[i]);
		}
	}
	else {
		std::cout << "Insufficient number of arguments(min 1)" << std::endl;
	}
}
