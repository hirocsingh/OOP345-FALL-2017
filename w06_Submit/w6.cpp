// Workshop 6 - Lambda Expression
 // w6.cpp

 #include <iostream>
 #include "Grades.h"

 using namespace w6;

 int main(int argc, char* argv[]) {
     if (argc != 2) {
         std::cerr << argv[0] <<
          ": incorrect number of arguments\n";
         std::cerr << "Usage: " << argv[0] << " file_name\n";
         return 1;
     }


         Grades grades(argv[1]);
         // define the lambda expression for letter
         auto letter = [](float fvalue) {
		std::string strScore;
		if ((fvalue >= 90.0f) && (fvalue <= 100.0f))	strScore = "A+";
		else if ((fvalue >= 80.0f) && (fvalue < 90.0f))	strScore = "A";
		else if ((fvalue >= 75.0f) && (fvalue < 80.0f))	strScore = "B+";
		else if ((fvalue >= 70.0f) && (fvalue < 75.0f))	strScore = "B";
		else if ((fvalue >= 65.0f) && (fvalue < 70.0f))	strScore = "C+";
		else if ((fvalue >= 60.0f) && (fvalue < 65.0f))	strScore = "C";
		else if ((fvalue >= 55.0f) && (fvalue < 60.0f))	strScore = "D+";
		else if ((fvalue >= 50.0f) && (fvalue < 55.0f))	strScore = "D";
		else if ((fvalue >=  0.0f) && (fvalue < 50.0f))	strScore = "F";
		else{
			// error //
		}
		return strScore;
	};





         grades.displayGrades(std::cout, letter);




     std::cout << "Press any key to continue ... ";
     std::cin.get();
 }
