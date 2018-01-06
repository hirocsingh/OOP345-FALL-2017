/*
	File:	CString.cpp
	Author:	Avinash Singh
	Date:	5-SEP-2017
	Course: OOP345
*/
#include "CString.h"

namespace w1
{
	CString::CString()
	{
		m_str[0] = 0;
	}

	CString::CString(const char* _inputStr)
	{
		if (_inputStr != NULL) {
			strncpy(m_str, _inputStr, MAX_CHAR);
			m_str[MAX_CHAR] = 0;
		}
		else {
			m_str[0] = 0;
		}
	}
	CString::~CString() {}

	std::ostream& CString::display(std::ostream& os)const {
		static int count = 0;
		return os << count++ << ": " << m_str;
	}

	std::ostream& operator<<(std::ostream& os, const CString& str) {
		return str.display(os);
	}
}
