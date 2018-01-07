
/*
 *       Name - Avinash Singh
 *       Milestome 3
 *       Date - 22 Dec 2017
 *       Submitted to -  John Blair.
 *       File - main.cpp
 */

#include <iostream>
#include "Item.h"
#include "Order.h"
#include "Util.h"
#include "Task.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
    if(argc != 5)
    {
        cerr << "Usage: " << argv[0] << " item_file tasks_file order_file csv-seperator-char\n";
        return 1;
    }
    string item = argv[1];
    string task = argv[2];
    string order = argv[3];
    char sep = argv[4][0];
    vector<vector<string> > csvItemData;
    vector<vector<string> > csvOrderData;
    vector<vector<string> > taskData;
    
    try{
         csvRead( item, sep , csvItemData);
         ItemManager in (csvItemData);
         in.print();
         in.graph(item);
        
         csvRead( order, sep , csvOrderData);
         OrderManager ii(csvOrderData);
         ii.print();
         ii.graph(order);
         
         csvRead( task, sep , taskData);
         TaskManager ts(taskData);
         ts.print();
         ts.graph(task);
        
    } catch (const string& e){
        cerr << "It threw = " << e << "\n";
    }
}
