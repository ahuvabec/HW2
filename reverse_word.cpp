#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#include <stack>
#include <string>
using namespace std;

void reverseWord(string &s, int len);

int main(){

	string word,filename;

	fstream file;

	filename = "chuck.txt";
	
	file.open(filename.c_str()); //opening the file to read from it
	
	while(file >> word){ //taking in word by word 
		
		reverseWord(word, word.length()); //running the function on each word
		cout<< word << " ";
		
	}

    return 0;
}

void reverseWord(string &s, int len){ 
	stack <char> stack;
	for(int i = 0; i < len; i++){ 
		stack.push(s[i]); //pushing each character onto the stack 
	}
	
	int j =0;
	while(!stack.empty()){
	
		s[j++]= stack.top(); //inserting the characters back into the string in a reversed manor 
		stack.pop();
		
	}
};
