#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
namespace ms3 {

   string& trim(string& string);
   void csvReader(string filename, char delimiter, vector <vector<string> > &data);
   bool is_nameValid(const string& taskName);
   bool is_slotValid(const string& slots);

}