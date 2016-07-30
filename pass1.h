#include<iostream>
#include<fstream>
#include<string>
#include "helper_functions.h"
using namespace std;

string process_pass1(string x) {
	string output = "";
	vector<string> lines = explode(x,'\n');
	int i, j, addresses[lines.size()];
	addresses[0] = 0;
	for(i=1;i<lines.size();i++) {
		addresses[i] = addresses[i-1];
		std::vector<std::string> words = explode(lines[i-1],' ');
		if(words[1] == "RESW") for(j=0;j<Atoi(words[2]);j++) addresses[i]+=3;
		else if(words[1] == "RESB") for(j=0;j<Atoi(words[2]);j++) addresses[i]++;
		else if(words[1] == "BYTE" || words[1] == "byte") for(j=0;j<(words[2].length()-3);j++) addresses[i]++;
		else addresses[i]+=3;
	}
	string addrs[lines.size()];
	for(i=0;i<lines.size();i++) {
		if(dectohex(addresses[i]).length()==1) addrs[i] = "000"+dectohex(addresses[i]);
		else if(dectohex(addresses[i]).length()==2) addrs[i] = "00"+dectohex(addresses[i]);
		else if(dectohex(addresses[i]).length()==3) addrs[i] = "0"+dectohex(addresses[i]);
		else if(dectohex(addresses[i]).length()==4) addrs[i] += dectohex(addresses[i]);
	}
	for(i=0;i<lines.size();i++) {
		output += addrs[i] + " " + lines[i] + "\n";
	}
	ofstream o;
	o.open ("intermediate.txt");
	o<<output;
	o.close();
	return output;
}

