#include <iostream>
#include <fstream>
#include <string>
#include "pass1.h"
#include "pass2.h"
using namespace std;

int main() {
	string f;
	cout<<"E.g \"mycode.txt\"\nEnter file: ";
	cin>>f;
	ifstream t(f.c_str());
	stringstream buffer;
	buffer<<t.rdbuf();
	t.close();
	string y = process_pass1(buffer.str());
	cout<<"After Pass 1"<<endl;
	cout<<y<<endl;
	string o = process_pass2(y);
	cout<<endl<<"After Pass 2"<<endl;
	cout<<o<<endl;
	return 0;
}
