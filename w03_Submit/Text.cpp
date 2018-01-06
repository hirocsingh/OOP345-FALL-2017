/*
**      NAME: AVINASH SINGH
**      COURSE: OOP345
**      WORKSHOP 2
**      FILE: Text.cpp
*/
#include "Text.h"


#include <fstream>
#include <iostream>


using namespace std;
namespace w3
{
	Text::Text()
	{
		m_pString = nullptr;
		m_numOfString = 0;
	}

	Text::Text(const char* filename){
		ifstream fp(filename);

		m_numOfString = 0;
		string strRecord;
		if (fp.is_open()){
			string unused;
			while (getline(fp, strRecord)){
				++m_numOfString;
			}


			// alocate string memory //
			if (m_numOfString > 0){
				m_pString = new  string[m_numOfString];

				fp.clear();
				fp.seekg(0, fp.beg);
				//	 string* pStart = m_pString;
				int idx = 0;

				while (getline(fp, m_pString[idx])){
				}
			}

			fp.close();
		}
	}


	void Text::init(const Text& text)
	{
		m_numOfString = text.size();
		m_pString = new string[m_numOfString];
		unsigned i;
		for (i = 0; i < m_numOfString; i++){
			m_pString[i] = text.m_pString[i];
		}
	}

	Text::Text(const Text& text)  			// copy constructor
	{
		init(text);
	}
	Text::Text(Text&& text)				// move constructor
	{
		m_numOfString = text.size();
		m_pString = text.m_pString;

		text.m_pString = nullptr;
		text.m_numOfString = 0;
	}



	Text& Text::operator=(const Text& text)		// copy assignment operator
	{
		init(text);
		return *this;
	}
	Text&& Text::operator=( Text&& text)		// move assignment operator
	{
		m_numOfString = text.size();
		m_pString = text.m_pString;

		text.m_pString = nullptr;
		text.m_numOfString = 0;

		return  move(*this);
	}



	Text::~Text()
	{

		if (m_pString != nullptr){
			delete[] m_pString;
		}
	}

}
