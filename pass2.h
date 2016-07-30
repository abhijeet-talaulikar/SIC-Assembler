#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

string process_pass2(string x) {
	string output = "";
	vector<string> lines = explode(x,'\n');
	string addresses[lines.size()], labels[lines.size()], operations[lines.size()], operands[lines.size()], obj[lines.size()];
	int i;
	for(i=0;i<lines.size();i++) {
		std::vector<std::string> words = explode(lines[i],' ');
		addresses[i] = words[0];
		labels[i] = words[1];
		operations[i] = words[2];
		operands[i] = words[3];
	}
	map <string, string> symtab;
	int indexed=0;
	for(i=0;i<lines.size();i++) if(labels[i] != "-" || labels[i] != "") symtab[labels[i]] = addresses[i];
	for(i=0;i<lines.size();i++) {
		obj[i] = get_opcode(operations[i]);
		if(symtab.find(operands[i]) != symtab.end() || 
		(operands[i].find(",X") != string::npos && symtab.find(operands[i].substr(0,operands[i].length()-2)) != symtab.end())
		) {
			string addr;
			if(operands[i].find(",X") == string::npos) {
				if(symtab[operands[i]].length()==1) addr="000"+symtab[operands[i]];
				else if(symtab[operands[i]].length()==2) addr="00"+symtab[operands[i]];
				else if(symtab[operands[i]].length()==3) addr="0"+symtab[operands[i]];
				else if(symtab[operands[i]].length()==4) addr+=symtab[operands[i]];
				obj[i]+=addr;
			} else {
				indexed=1;
				string opr = operands[i].substr(0,operands[i].length()-2);
				if(symtab[opr].length()==1) addr="000"+symtab[opr];
				else if(symtab[opr].length()==2) addr="00"+symtab[opr];
				else if(symtab[opr].length()==3) addr="0"+symtab[opr];
				else if(symtab[opr].length()==4) addr+=symtab[opr];
				obj[i]+=addr;
			}
		}
		if(operations[i]=="WORD") obj[i]+=operands[i];
		else if(operations[i]=="BYTE" && operations[i].find("EOF")==string::npos) {
			obj[i]+=operands[i].substr(2);
			obj[i]=obj[i].substr(0,obj[i].length()-1);
		} else if(operations[i]=="BYTE" && operations[i].find("EOF")!=string::npos) {
			obj[i]="454F46";
		}
		if(indexed) {
			if(obj[i][2]=='0') obj[i][2]='8';
			else if(obj[i][2]=='1') obj[i][2]='9';
			else if(obj[i][2]=='2') obj[i][2]='A';
			else if(obj[i][2]=='3') obj[i][2]='B';
			else if(obj[i][2]=='4') obj[i][2]='C';
			else if(obj[i][2]=='5') obj[i][2]='D';
			else if(obj[i][2]=='6') obj[i][2]='E';
			else if(obj[i][2]=='7') obj[i][2]='F';
		}
	}
	for(i=0;i<lines.size();i++) {
		output += lines[i]+ " " + obj[i] + "\n";
	}
	ofstream o;
	o.open ("objectcode.txt");
	o<<output;
	o.close();
	return output;
}

