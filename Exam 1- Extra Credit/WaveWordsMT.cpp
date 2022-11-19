/*
Author: Mai Tran
Couse: COSC 1437
EC EXam 1
Reference: 02/02/2022
*/

#include <iostream>
#include <string>
using namespace std;


// print space character n time
void printSpace(int num) {

	for (int i = 0; i < num; i++) {

		cout << " ";

	}

}

int main() {

	// hold word
	string word;

	// get word for user and input validation
	do {

		cout << "Enter a word: ";
		cin >> word;

		if (word.length() > 10 || word.length() < 3) {

			cout << "\nPlease enter 3 to 10 characters word only\n\n";
			
		}

	} while (word.length() > 10 || word.length() < 3);

	// hold number of space
	int spaceNum;

	// print the first line, which has the fist character appear 3 times
	spaceNum = 2 * (word.length() - 1) - 1;
	cout << endl;
	cout << word[0]; 
	printSpace(spaceNum);
	cout << word[0];
	printSpace(spaceNum);
	cout << word[0];
	cout <<	endl;

	// print all intermediate lines, which has intermediate character appear 4 times on each line
	for (unsigned i = 1; i < word.size() - 1; i++) {

		spaceNum = 2 * (word.length() - i - 1) - 1;
		printSpace(i);
		cout << word[i];
		printSpace(spaceNum);
		cout << word[i];
		printSpace(2*i - 1);
		cout << word[i];
		printSpace(spaceNum);
		cout << word[i];
		printSpace(2 * i - 1);
		cout << endl;

	}

	// print the last line, which has the last charater appear 2 times
	printSpace(word.length() - 1); 
	cout << word[word.length() - 1]; 
	printSpace(2 * (word.length() - 1) - 1); 
	cout << word[word.length() - 1];
	cout << endl;

}