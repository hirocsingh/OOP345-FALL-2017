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
void csvPrint(std::vector < std::vector<std::string> > &csvData);
void csvRead(std::string& filename, char sep, std::vector<std::vector<std::string> > & csvdata);
bool validSequenceNumber(std::string s);
bool validItemName(std::string s);
bool validCustomerName(std::string s);
bool validProductName(std::string s);

