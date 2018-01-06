/*
*       Name - Avinash Singh
*       Milestome 2
*       Date - 11 Dec 2017
*       Submitted to -  John Blair.
*       File - Util.cpp
*/
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//#include"Util.h"

using namespace std;
std::string& trim(std::string& s, char trimChar = ' ');
std::string& trim(std::string& s, char trimChar)
{
  while(not s.empty() and s[0] == trimChar)
    s.erase(0, 1);

  while(not s.empty() and s[s.size()-1] == trimChar)
    s.erase(s.size()-1, 1);

  return s;
}

bool validSlots(string slots) {
        if (slots.empty()) {
            return false;
        }
        for (auto chr : slots) {
            if (isdigit(chr)) {
                continue;
            }
            return false;
      }
    return true;
}


bool validTaskName(string taskName) {
        if (taskName.empty()) {
            return false;
        }

        for (auto tasks : taskName) {
            if (isspace(tasks) || isalnum(tasks) || tasks == '_') {
                continue;
            }
            return false;
        }
        return true;
}


void csvReader(char* filename, char delim, std::vector< std::vector<std::string> > &csv)
{
  std::ifstream is(filename);
  if(is) {
    std::string line;
    std::vector<std::string> fields;

    while(getline(is, line)) {
      auto cr = line.find('\r');
      if(cr != std::string::npos) line.erase(cr, 1);

      std::string field;
      for(size_t i = 0; i < line.size(); i++) {
      #ifdef PROCESS_DOUBLE_QUOTES
         if(line[i] == '"') {
           field += line[i];        // copy 1st "
           for( i++ ; i < line.size() ; i++ ) {
             field += line[i];
             if(line[i] == '"')     // found 2nd "
               break;
           }
         }
         else
       #endif
         if(line[i] != delim) {
           field += line[i];
         } else {
            trim(field);
            fields.push_back(move(field));
            // field.clear(); // not needed if we do a move
         }
      }
      trim(field);
      fields.push_back(field);
      csv.push_back(move(fields));
      // field.clear(); // not needed if we do a move
    }
    is.close();
  } else {
    std::cerr << "cannot open file " << filename << "\n";
  }
}
