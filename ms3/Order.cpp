/*
 *       Name - Avinash Singh
 *       Milestome 3
 *       Date - 22 Dec 2017
 *       Submitted to -  John Blair.
 *       File - Order.cpp
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>


#include "Util.h"
#include "Order.h"

using namespace std;

Order::Order (vector<string> line)
{
    if (line.size() < 3)
        throw string("expected at least 3 fields, found " ) + to_string(line.size());
    
    if(validCustomerName( line[0] )) {
        customer = line[0];
        cout << customer;
    }
    else throw string("customer name not understood -->") + line[0] + "<--";
    
    if(validProductName( line[1] ))
        product = line[1];
    else throw string("product name not understood -->") + line[1] + "<--";
    
    for(size_t i = 2; i < line.size(); i++)
    {
        if (line[i].empty())
            continue;
        if(validItemName(line[i]))
            itemList.push_back(line[i]);
        else
            throw string ("item name not understood -->") + line[1] + "<--";
    }
}


void Order::print(){
    cout    << "|customer|product|item 1|item 2|...| = "
    << "|" << customer
    << "|" << product;
    for(auto& item : itemList)
        cout << "|" << item;
    cout << "|\n";
}

void Order::graph(fstream& gv){
    for(auto& item: itemList)
        gv << '"' << customer << "\n" << product << '"'
        << "->"
        <<'"' << item << '"'
        << "[color=blue];\n";
}


OrderManager::OrderManager(vector<vector<string> >& csvOrderData){
    for(auto& line : csvOrderData){
        try{
            orderList.push_back( Order(line) );
        } catch(const string& e){
            cerr << "Problem: " << e << "\n";
        }
    }
}
void OrderManager::print(){
    for(auto& t: orderList)
        t.print();
}

void OrderManager::graph(string filename){
    fstream gv(filename + ".gv", ios::out | ios::trunc);
    if(gv.is_open()){
        gv << "digraph Ordergraph {\n";
        for(auto& t : orderList)
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

