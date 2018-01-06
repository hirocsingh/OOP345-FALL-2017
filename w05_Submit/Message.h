/*
**      OOP345 Workshop 5
**      Name: Avinash Singh
**      File: Message.h
*/

#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

namespace w5{
	class Message
	{
		std::vector<std::string> strmsg;
	public:
		Message();
		Message(std::ifstream& in, char c);
		~Message();

		bool empty() const;
		void display(std::ostream& os) const;


	};
}
