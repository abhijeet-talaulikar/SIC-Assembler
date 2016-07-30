#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
using namespace std;

int Atoi(string str) {
	int res = 0;
	for (int i = 0; str[i] != '\0'; ++i) res = res*10 + str[i] - '0';
	return res;
}

string itos(int num) {
	stringstream ss;
	ss<<num;
	return ss.str();
}

vector<string> explode(const string& str, const char& ch) {
	string next;
	vector<string> result;
	for (string::const_iterator it = str.begin(); it != str.end(); it++) {
		if (*it == ch) {
			if (!next.empty()) {
				result.push_back(next);
				next.clear();
			}
		} else next += *it;
    	}
	if (!next.empty()) result.push_back(next);
	return result;
}

string get_opcode(string operation) {
	map <string, string> optab;
	optab["ADD"] = "18";
	optab["AND"] = "40";
	optab["COMP"] = "28";
	optab["COMPF"] = "88";
	optab["DIV"] = "24";
	optab["J"] = "3C";
	optab["JEQ"] = "30";
	optab["JGT"] = "34";
	optab["JLT"] = "38";
	optab["JSUB"] = "48";
	optab["LDA"] = "00";
	optab["LDCH"] = "50";
	optab["LDL"] = "08";
	optab["LDX"] = "04";
	optab["MUL"] = "20";
	optab["OR"] = "44";
	optab["RD"] = "D8";
	optab["RSUB"] = "4C";
	optab["STA"] = "0C";
	optab["STCH"] = "54";
	optab["STL"] = "14";
	optab["STSW"] = "E8";
	optab["STX"] = "10";
	optab["SUB"] = "1C";
	optab["TD"] = "E0";
	optab["TIO"] = "F8";
	optab["TIX"] = "2C";
	optab["WD"] = "DC";
	return optab[operation];
}

int hextodec(int input) {
	stringstream ss;
	ss<<dec<<input;
	return input;
}

string dectohex(int input) {
	stringstream ss;
	ss<<hex<<input;
	return ss.str();
}
