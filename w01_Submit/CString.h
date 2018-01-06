/*
	File:		CString.h
	Author:		Avinash Singh
	Date:		05-SEP-2017
	Course:		OOP345
 */


#ifndef W1_CSTRING_H_
#define W1_CSTRING_H_

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

// Maximum character allowed.
const int MAX_CHAR = 3;

namespace w1
{
	class CString
	{
		char m_str[MAX_CHAR + 1];
	public:
		// default constructor
		CString();

		CString(const char* s);

		// Destructor
		~CString();

		std::ostream& display(std::ostream& os)const;
	};

	// helper function
	std::ostream& operator<<(std::ostream& os, const CString& str);
}


#endif
