/*
**      OOP345 Workshop 5
**      Name: Avinash Singh
**      File: Notification.cpp
*/

#include "Notifications.h"

namespace w5{
	Notifications::Notifications() : numOfmsg(10)
	{
		vecmsg.reserve(numOfmsg);
	}

	// copy constructor //
	Notifications::Notifications(const Notifications& N) : numOfmsg(10)
	{
		vecmsg.reserve(numOfmsg);
		*this = N;
	}

	// move constroctor //
	Notifications::Notifications(Notifications&& N) : numOfmsg(10)
	{
		vecmsg.reserve(numOfmsg);
		*this = std::move(N);
	}

	// copy assignment //
	Notifications& Notifications::operator = (const Notifications& N)
	{
		vecmsg = N.vecmsg;
		return *this;
	}

	// move assignemt //
	Notifications&& Notifications::operator=(Notifications&& N)
	{
		vecmsg = std::move(N.vecmsg);
		return std::move(*this);
	}

	// destructor //
	Notifications::~Notifications()
	{
		//std::vector<Message>::iterator iter = vecmsg.begin();
		vecmsg.clear();
	}


	void Notifications::operator += (const Message& msg)
	{
		if (vecmsg.size() < numOfmsg){
			vecmsg.push_back(msg);
		}
	}

	void Notifications::display(std::ostream& os) const
	{
		std::vector<Message>::const_iterator iter = vecmsg.begin();
		for (; iter != vecmsg.end() ; iter++){
			iter->display(os);
		}
	}
}
