/**
 * Incorrect code to identify palindromes
 */

#include <iostream>
#include <sstream>
#include <cstring> 
#include <fstream>

using namespace std;

int main (int argc, char * argv[]){

int len;
string length;

ifstream infile;
infile.open(argv[1]);

if (infile.good()){
	infile >> len;
}

string* backward = new string[len];

for(int i = 0; i < len; i++){
	string temp;
	infile >> temp;
	backward[len - 1 - i] = temp;
}

for(int i = 0; i<len; i++){
	cout << backward[i] << endl;
}

delete[] backward

return 0;

}