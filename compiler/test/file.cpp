// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>
using namespace std;

int main () {
  string line;
  
  ifstream myfile ("example.txt");
  if (myfile.is_open())
  {
     
      myfile>>line;
      cout << line << endl;
     int x = boost::lexical_cast<int>("123");
     cout<<x;
    
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}
