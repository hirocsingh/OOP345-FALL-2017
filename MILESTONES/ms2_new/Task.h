#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include"Util.h"
using namespace std;

namespace ms3 {
    
    class Task {

    private:
        string name_, slots_ , passed_, failed_;

    public:
      
        Task(vector <string> & csv);
        void print();
        void graph(ostream& os);
    };

    class TaskManager {
    private:
        vector<Task> tasks;

    public:
        TaskManager(vector<vector<string> >& task);
        void print();
        void graph(string file);
    };

}