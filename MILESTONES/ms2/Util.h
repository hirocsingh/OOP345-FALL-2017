/*
*       Name - Avinash Singh
*       Milestome 2
*       Date - 11 Dec 2017
*       Submitted to -  John Blair.
*       File - Util.h 
*/
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


std::string& trim(std::string& s, char trimChar);
bool validSlots(std::string s);
bool validTaskName(std::string s);
void csvReader(char* filename, char delim, std::vector< std::vector<std::string> > &csv);
