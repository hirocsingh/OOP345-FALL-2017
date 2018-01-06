/*
*       Name - Avinash Singh
*       Milestome 2
*       Date - 11 Dec 2017
*       Submitted to -  John Blair.
*       File - Task.cpp
*/
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include<iomanip>


#include"Util.h"
#include"Task.h"

using namespace std;

Task::Task (vector<string> line)
{
    switch (line.size())   {
        case 4:
            if (validTaskName(line[3])) {
                fail = line[3];
            }
            else {
                cout << endl << "ERROR: Assinging failed task name." << endl;

            }

        case 3:
            if (validTaskName(line[2])) {
                pass = line[2];
            }
            else {
                cout << endl << "ERROR: Assinging failed passed task name." << endl;

            }
        case 2:
            if (validSlots(line[1])) {
                slots = line[1];
            }
            else {
                cout << endl << "ERROR: Assinging slot." << endl;

            }
        case 1:
            if (validTaskName(line[0])) {
                name = line[0];
            }
            else {
                cout << endl << "ERROR: Assinging task name." << endl;
                break;
            }
            break;
        default:
            cerr << "Error: Searching for 1-4 Task fields." << endl;
            break;
    }

            /*switch(line.size()){
                case 4:
                    if(validTaskName( line[3] ))
                        fail = line[3];
                    else
                        throw string("fail task name not understood ") + line[3] + "<--";
                case 3:
                    if(validSlots( line[2] ))
                         pass = line[2];
                    else
                        throw string("pass task name not understood ") + line[2] + "<--";
                case 2:
                    if(validTaskName( line[1] ))
                        slots = line[1];
                    else
                        throw string("slots not understood ") + line[1] + "<--";
                case 1:
                    if(validTaskName( line[0] ))
                        name = line[0];
                    else
                        throw string("name not understood ") + line[0] + "<--";
                    break;
                default:
                    throw string("expected 1,2,3 or 4 fields, found ") + to_string(line.size());
            }*/
}

void Task::print() {
        cout << left << "|  " << setw(4) << slots << "| " << setw(20) << name
            << "| " << setw(20) << pass << "| " << setw(20) << fail << setw(20)
            << "|" << endl;
}

void Task::graph(fstream& gv) {
        if (!pass.empty())
            gv << '"' << name << '"' << "->" << '"' << pass << '"' << " [color=green];" << std::endl;
        if (!fail.empty())
            gv << '"' << name << '"' << "->" << '"' << fail << '"' << " [color=red];" << std::endl;


        if (pass.empty() && fail.empty())
            gv << '"' << name << '"' << " [shape=box];" << std::endl;
    }

    /*void Task::print(){
        cout    << "|name|slots|pass|fail| = "
                << "|" << name
                << "|" << slots
                << "|" << pass
                << "|" << fail
                << "|\n";
    }

    void Task::graph(fstream& gv){
        if(pass.empty() and fail.empty())
            gv << '"' << name << '"' << ";\n";

        if(not pass.empty())
            gv  << '"' << name << '"'
                << "->"
                << '"' << pass << '"'
                << "[color=green];\n";

        if(not fail.empty())
            gv  << '"' << name << '"'
                << "->"
                << '"' << fail << '"'
                << "[color=red];\n";
    }*/

        TaskManager::TaskManager(vector<vector<string> >& task){
            for(auto& line : task){
                try{
                    tasks.push_back( Task(line) );
                } catch(const string& e){
                    cerr << "Problem " << e << "\n";
                }
            }
        }
        void TaskManager::print(){
            for(auto& t: tasks)
                t.print();
        }

        void TaskManager::graph(string filename){
            fstream gv(filename + ".gv", ios::out | ios::trunc);
            if(gv.is_open()){
                gv << "digraph taskgraph {\n";
                for(auto& t : tasks)
                    t.graph(gv);
                gv << "}\n";
                gv.close();

                vector<string> dotLocations {
                        "/usr/bin/dot",                                       // default UNIX
                        "/usr/local/bin/dot",                                 // sometimes a UNIX package is installed in /usr/local
                        "C:/\"Program Files (x86)\"/Graphviz2.38/bin/dot.exe" // a known DOS location for graphviz 2.38 (current package as of Nov 25, 2017)
                };

                string dot;
                for(auto& e: dotLocations) {
                    auto fileexist = [] (string file) {fstream f(file, ios::in); return f.is_open();};
                    if( fileexist(e) ) {
                        dot = move(e);
                        break;
                    }
                }

                 if(dot.empty()){
                    cerr << R"foo(ERROR: Graphviz program 'dot' not found!  Package 'graphviz' is not installed.)foo";
                 }else{
                    string cmd = dot;
                    cmd += " -Tpng -O " + filename + ".gv";
                    cout << "Running command -->" << cmd << "<--\n";
                    int result = system(cmd.c_str());
                    cout  << "It returned '" << result << (result?  "' (command failed)\n": "' (command passed)\n");
                 }

            }
        }
