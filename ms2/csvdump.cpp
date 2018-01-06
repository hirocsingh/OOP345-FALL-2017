/*
*       Name - Avinash Singh
*       Milestome 2
*       Date - 11 Dec 2017
*       Submitted to -  John Blair.
*       File - csvdump.cpp [main file]
*/

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include"Util.h"
#include"Task.h"
using namespace std;

int main(int argc, char**argv)
{
  char *filename;
  char delim;

  if(argc != 3) {
    std::cerr << "usage: " << argv[0] << " file delimiter-char\n";
    return 2;
  }

  filename = argv[1];
  delim    = argv[2][0];

  std::vector< std::vector<std::string> > csv;
  csvReader(filename, delim, csv);

  for(size_t line = 0; line < csv.size(); line++) {

    std::cout << csv[line].size() << " fields:";
    for(size_t field =  0; field < csv[line].size(); field++) {
      std::cout << " <<" << csv[line][field] << ">>";
    }
    std::cout << "\n";
  }

  /*filename = argv[1];
    delim = argv[2][0];
    cout << "Task File: " << argv[1] << endl
        << "Field Delimiter: " << argv[2][0] << endl
        << endl;*/

    //csvReader(filename, delim, csv);
    TaskManager testTM(csv);
    testTM.print();
    testTM.graph(filename);
    //system("pause");

  return 0;
}
