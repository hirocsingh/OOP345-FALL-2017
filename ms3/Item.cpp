/*
 *       Name - Avinash Singh
 *       Milestome 3
 *       Date - 22 Dec 2017
 *       Submitted to -  John Blair.
 *       File - Item.cpp
 */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include<iomanip>


#include"Util.h"
#include"Item.h"

using namespace std;

Item::Item (vector<string> line)
{
    switch (line.size())   {
        case 5:
            description = line[4];
        case 4:
            if (validSequenceNumber(line[3]))
                sequenceNumber = line[3];
            
            else
                throw string("sequence number not understood --<") + line[3] + "<--";
            
            if(validTaskName(line[2]))
                remover = line[2];
            else
                throw string("remover task name not understood -->") + line[2] +"<--";
            
            if(validTaskName(line[1]))
                installer = line[1];
            else
                throw string("installer task name not understood -->") + line[1] +"<--";
            
            if (validItemName(line[0]))
                name = line[0];
            else
                throw string ("item name not understood -->" ) + line[0] + "<--";
            break;
        default:
            throw string("expected 4 or 5 fields, found " ) + to_string( line.size());
    }
}

void Item::graph(fstream& gv) {
    gv << '"' << name << '"'
    << "->"
    << '"' << installer << '"'
    << " [color=green];" << std::endl;
    
    gv << '"' << name << '"'
    << "->"
    << '"' << remover
    << '"' << " [color=red];" << std::endl;
}

void Item::print()
{
    //string name;
    cout    << "|name|installer|remover|sequenceNumber|description| = "
    << "|" << name
    << "|" << installer
    << "|" << remover
    << "|" << sequenceNumber
    << "|" << description
    << "|\n";
}

void ItemManager::print()
{
    for(auto& item: itemList)
        item.print();
}

void ItemManager::graph(string filename){
    fstream gv(filename + ".gv", ios::out | ios::trunc);
    if(gv.is_open()){
        gv << "digraph Itemgraph {\n";
        for(auto& item : itemList)
            item.graph(gv);
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
};


