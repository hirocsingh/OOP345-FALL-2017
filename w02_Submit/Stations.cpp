/*
**      NAME: AVINASH SINGH
**      COURSE: OOP345
**      DATE:
**      WORKSHOP 2
**      FILE: Stations.cpp
*/
#include "Stations.h"

w2::Stations::Stations(char * s) {
		ifstream fileIn (s);
		if (!fileIn.is_open()){
			cerr << "File is not open" << endl;
		}
		else{
			char readBuff[64];

			char stnName[64];
			unsigned int nStudent;
			unsigned int nAdult;
			Station* pStation;

		//	fileIn.ignore();
			fileIn.getline(readBuff, 64, ';');
			number_of_stations = atoi(readBuff);

			fileIn.ignore();

			if (number_of_stations > 0){
				pStation = new Station[number_of_stations];

				fileIn.ignore();
				unsigned i;
				for (i = 0; i < number_of_stations; i++){

					fileIn.getline(stnName, 64, ';');

					fileIn.getline(readBuff, 64, ' ');
					nStudent = atoi(readBuff);

					fileIn.getline(readBuff, 64);
					nAdult = atoi(readBuff);


					pStation[i].set(stnName, nStudent, nAdult);
				}
			}
			else{
				cerr << "File is empty" << endl;
			}
		}
	}

w2::Stations::~Stations() {
	stations_ = '\0';
}

void w2::Stations::update() const {
	/*
	* Takes input from the user
	*/
	Station s;

	std::cout << "Passes Sold : " << endl;
	std::cout << "--------------" << endl;

	for (int p = 0; p < number_of_stations; p++) {
		int student_passes_sold, adult_passes_sold;

		//accepts the number of passes sold and updates the data for each station
		std::cout << stations_ << endl;

		//takes the amount of student passes sold
		std::cout << " Student Passes sold : ";
		std::cin >> student_passes_sold;

		//takes the amount of adult passes sold
		std::cout << " Adult   Passes sold : ";
		std::cin >> adult_passes_sold;

		student_passes_sold *= -1;
		adult_passes_sold *= -1;

		s.set(stations_, student_passes_sold, adult_passes_sold);
	}

	cout << endl;
}

void w2::Stations::restock() const {

	/*
	* Takes input from the user
	*/
	Station s;

	cout << "Passes Added : " << endl;
	cout << "--------------" << endl;

	for (int p = 0; p < number_of_stations; p++) {
		int student_passes_added, adult_passes_added;

		//accepts the number of passes added and updates the data for each station
		cout << stations_ << endl;

		//takes the amount of student passes added
		cout << " Student Passes added : ";
		cin >> student_passes_added;

		//takes the amount of adult passes added
		cout << " Adult   Passes added : ";
		cin >> adult_passes_added;

		/*
		* Updates the file with the new values
		*/
		s.set(stations_, student_passes_added, adult_passes_added);
	}

	cout << endl;
}

void w2::Stations::report() const {
	/*
	*outputs the values of passes for each station
	*/
	cout << setw(32) << "Passes in Stock : Student Adult" << endl;

	cout << ' ';
	for (int i = 0; i < 31; i++) {
		cout << '-';
	}
	cout << endl;

	for (int o = 0; o < number_of_stations; o++) {
		cout << left << setw(19) << stations_ << setfill(' ')
			<< right << setw(7) << file_student_passes << setfill(' ')
			<< right << setw(6) << file_adult_passes << setfill(' ') << endl;
	}
}
