/*
**      OOP345 Workshop 6
**      Name: Avinash Singh
**      File: Grades.cpp
*/

#include "Grades.h"
#include <fstream>
#include <string>

namespace w6{
	Grades::Grades()
	{
	}

	Grades::Grades(const char* filepath)
	{
		try{
			readFile(filepath);
		}
		catch (const char* msg){
			std::cout << msg << std::endl;
		}
	}

	Grades::~Grades()
	{
		pData.clear();
	}


	void Grades::readFile(const char* filepath)
	{
		std::string line;
		std::ifstream fileIn(filepath);
		if (fileIn.is_open()){
			while (fileIn.good()){
				GradeInfo pinfo;
				fileIn >> pinfo.sid;
				fileIn >> pinfo.fscore;

				pData.push_back(std::move(pinfo));
			}
		}
		else{
			throw "File open failed";
		}
	}

	void Grades::displayGrades(std::ostream& os, pFunc lambda) const
	{
		for (size_t i = 0; i < pData.size(); i++){
			os << pData.at(i).sid << " " << pData.at(i).fscore << " " << lambda(pData.at(i).fscore) << std::endl;
		}
	}
}
