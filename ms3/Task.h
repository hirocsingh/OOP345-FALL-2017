/*
 *       Name - Avinash Singh
 *       Milestome 2
 *       Date - 11 Dec 2017
 *       Submitted to -  John Blair.
 *       File - Task.h
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//#include"Util.h"
using namespace std;

class Task {
    string name, slots { "1" }, pass, fail;
public:
    Task(){};
    Task (vector<string> line);
    void print();
    void graph(fstream& gv);
};

class TaskManager {
private:
    vector<Task> tasks;
public:
    TaskManager(vector<vector<string> >& task);
    void print();
    void graph(string filename);
};

