/*
 *       Name - Avinash Singh
 *       Milestome 3
 *       Date - 11 Dec 2017
 *       Submitted to -  John Blair.
 *       File - Order.h
 */
#pragma once
using namespace std;


#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//#include "Util.h"

class Order{
private:
    string customer, product;
    vector<string> itemList;
public:
    Order(){};
    Order(vector<string> line);
    void print();
    void graph(fstream& gv);
};

class OrderManager {
private:
    vector<Order> orderList;
public:
    OrderManager(vector< vector<string> > & csvOrderData);
    void print();
    void graph(std::string filename);
};


