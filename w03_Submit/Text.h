/*
**      NAME: AVINASH SINGH
**      COURSE: OOP345
**      WORKSHOP 2
**      FILE: Text.h
*/
#ifndef W2_TEXT_H__
#define W2_TEXT_H__

#include <string>
#include<iostream>

namespace w3
{
	class Text
	{
	public:
		Text();
		Text(const char* filename);

		Text(const Text& text);  		// copy constructor
		Text(Text&& text);			// move constructor

		Text& operator=(const Text& text);	// copy assignment operator
		Text&& operator=( Text&& text);		// move assignment operator

		~Text();

		void init(const Text& text);
		size_t size() const { return m_numOfString; }

	private:
		std::string* m_pString;
		unsigned m_numOfString;
	};
}

#endif
