
/*
 *       Name - Avinash Singh
 *       Milestome 3
 *       Date - 22 Dec 2017
 *       Submitted to -  John Blair.
 *       File - Item.h
 */


#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//#include"Util.h"
using namespace std;

class Item {
    string name, installer, sequenceNumber { "1" }, remover, description;
public:
    Item(){};
    Item (vector<string> line);
    void print();
    void graph(fstream& gv);
};

class ItemManager {
private:
    vector<Item> itemList;
public:
    //ItemManager(vector<vector<string> >& csvItemData);
    ItemManager(vector< vector<string> > & csvItemData)
    {
        for (auto& line : csvItemData)
        {
            try
            {
                itemList.push_back( Item(line) );
            } catch(const string& e){
                cerr << "Problem " << e << "\n";
            }
        }
    }
    void print();
    void graph(string filename);
};

