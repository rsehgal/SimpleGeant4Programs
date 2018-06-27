#include <fstream>
#include<iostream>

using namespace std;

int main()
{  
double x=0., y=0., z=0.;
  ifstream infile("hitstrip.txt");
    while(!infile.eof()){
    infile >> x >> y >> z;
    cout << x <<" "<<y <<" "<<z<< endl;
}
    infile.close();
   return 0;		
}
