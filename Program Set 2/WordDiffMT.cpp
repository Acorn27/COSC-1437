/*
Author: Mai Tran
Course: COSC 1437
Program set 2-2
Reference: None
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// fucntion to open a file and check if 
// that file exist or not.
bool openFile(fstream& file, string name) {

	// open file for reading
	file.open(name, ios::in);

	// if fail opening failed, return false
	if (file.fail()) {

		return (false);
	} // otherwise, return true
	else {

		return (true);

	}
}

// function to check if a word is lowwercase or not
bool checkUpper(string word) {

	bool upper = true;

	// step through word
	for (unsigned i = 0; i < word.size(); i++) {

		if (!islower(word[i])) {
			
			return (false);

		}
	}

	return (true);
}

// return number of words between two entered words
int calDistance(fstream& file, string word1, string word2, string &errorMessage) {

	// temporary varibale to hold dictionary words
	string test;
	
	// hold index of the dictionary word being reffered
	int index = 0;

	// hold line number for word1 and word2, initilized to -1
	int index1 = -1,
		index2 = -1;

	// get line number for the first word
	do {

		getline(file, test, '\n');
		index++;
		if (test == word1) {

			index1 = index;
			continue;

		}

	} while (test != word1 && !file.fail());
	
	
	// get line number for the second word
	do {

		getline(file, test, '\n');
		index++;
		if (test == word2) {

			index2 = index;
			continue;

		}

	} while (test != word2 && !file.fail());


	// if word1 and word2 index still no longer 0, which mean words are found
	if (index1 != -1 && index2 != -1) {

		return (index2 - index1 - 1);

	} // return -1 if words are not found
	else if (index1 == -1 && index2 == -1) {

		errorMessage += word1;
		errorMessage += ", ";
		errorMessage += word2;
		errorMessage += " NOT FOUND";
	
	}
	else if (index2 == -1) {

		errorMessage += word2;
		errorMessage += " NOT FOUND";
	
	}
	else {

		errorMessage += word1;
		errorMessage += " NOT FOUND";
	}

	return (-1);
}

int main() {

	// file stream object name dict
	fstream dictFile;

	// hold file's name
	string fileName;

	// get file's name from user input
	cout << "\nEnter the file Name: ";
	cin >> fileName;

	
	if (openFile(dictFile, fileName)) {

		// hold two words
		string word1, word2;
		cout << "\nEnter word one: ";
		cin >> word1;
		cout << "Enter word two: ";
		cin >> word2;

		// calculate distance between two words
		string errorMessage = "";
		int dist = calDistance(dictFile, word1, word2, errorMessage);


		cout << endl;
		// check duplicate words
		if (word1 == word2) {

			cout << "Please enter different words\n";
			
		} // check lowercase
		else if (!(checkUpper(word1) && checkUpper(word2))) {

			cout << "Please enter lowercase words only.\n";

		// display words in between if 2 words were found
		} else if (dist != -1) {

			cout << "There are " << dist << " words between " << word1 << " and " << word2 << endl;
		
		}
		else {

			cout << errorMessage << endl;

		}

	} // display error if file not exist
	else {

		cout << "\nError opening file " << fileName << endl;

	}

	dictFile.close();

}