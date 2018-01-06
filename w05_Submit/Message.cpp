/*
**      OOP345 Workshop 5
**      Name: Avinash Singh
**      File: Message.cpp 
*/

#include "Message.h"

namespace w5{
	Message::Message()
	{
		strmsg.reserve(1);
	}

	Message::Message(std::ifstream& in, char c)
	{
		strmsg.reserve(1);

		std::string str, user, reply, tweet, token;
		std::getline(in, str, c);
		size_t pos;

		unsigned short readCnt = 0;
		bool Isvaild = false;
		while (str.length() > 0){

			switch (readCnt)
			{
			case 0:
				pos = str.find(" ");
				if (pos != std::string::npos){
					token = str.substr(0, pos);
					user = " User  : " + token + "\n";
					str.erase(0, pos + 1);
				}
				else{
					pos = str.length();
					token = str.substr(0, pos);
					user = " User  : " + token + "\n";
					str.erase(0, pos);
				}
				break;
			case 1:
				pos = str.find(" ");
				if (pos!= std::string::npos){
					token = str.substr(0, pos);
					if (token.at(0) == '@'){
						token = str.substr(1, pos);
						reply = " Reply : " + token + "\n";
						str.erase(0, pos + 1);
					}
				}
				break;
			case 2:
				pos = str.length();
				if (pos > 0){
					token = str.substr(0, pos);
					tweet = " Tweet : " + token + "\n";
					str.erase(0, pos);
					Isvaild = true;
				}
				break;
			default:
				break;
			}
			readCnt++;
		}

		if (Isvaild){
			strmsg.push_back(user + reply + tweet);
		}
	}

	Message::~Message()
	{
		strmsg.clear();
	}

	bool Message::empty() const
	{
		return strmsg.size() == 0 ? true : false;
	}
	void Message::display(std::ostream& os) const
	{
		os << "Message" << std::endl;
		std::vector<std::string>::const_iterator iter = strmsg.begin();
		for (; iter != strmsg.end(); iter++){
			os << *iter << std::endl;
		}
	}


}
