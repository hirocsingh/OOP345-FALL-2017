#include <iostream>
#include <string>
#include <vector>
#include "Task.h"


using namespace ms3;

int main(int argc, char** argv) {

    vector<vector<string> > task_csv;

    if (argc != 3) {
        cerr << "You must provide 2 arguments" << endl
            << "Command Line: "
            << "Arg1= Filename Arg2= File Delimiter" << endl;
        return 1;
    }

    string task_filename =argv[1];
    char delim = argv[2][0];

   cout << "Task File: " << argv[1] << endl
        << "Field Delimiter: " << argv[2][0] << endl
        << endl;

    csvReader(task_filename, delim, task_csv);

    TaskManager tm = TaskManager(task_csv);
    tm.print();
    tm.graph(task_filename);
  
  system("pause");
  return 0;
}