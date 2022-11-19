/*
Author: Mai Tran
Course: COSC 1437
Program Set 2
Reference:
	03/01/2022: I got the idea to separate words in string using additional status variable from this website: https://www.geeksforgeeks.org/count-words-in-a-given-string/
				I found it is very interesting because it works with double or even more spaces between each world

	03/01/20222: How to remove single vector elemet: https://www.cplusplus.com/reference/vector/vector/erase/

	03/01/2022: How to remove duplicate vector element: https://www.techiedelight.com/remove-duplicates-vector-cpp/

*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// function to extract words from a string into vector.
void extractWords(string input, vector<string>& words) {

	// variable to hold status of string element
	// "OUT" mean "space" is seen while "IN" mean the cursor is pointing at word's character.
	string state = "OUT";

	// hold starting index for substr function.
	int start = 0;

	// step through the string.
	for (unsigned i = 0; i < input.size(); i++) {

		// if space is encountered and our current status is "IN" or if we reach the end of the string
		// get a word and push it into vector.
		if ((isspace(input[i]) && state == "IN") || i == input.size() - 1) {

			// if i == the end of string, we muse add 1 to length of substr so that we don't miss the last character of string.
			string temp = input.substr(start, ((i == input.size() - 1) ? i - start + 1 : i - start));
			words.push_back(temp);

			// after substr, change status to "OUT" and assign start to the next character.
			state = "OUT";
			start = i + 1;

		} // skip over any whitespace characters.
		else if (isspace(input[i]) && state == "OUT") {

			start++;

		} // change status back to "IN" if an alpha character is encountered.
		else if (isalpha(input[i])) {

			state = "IN";

		}
	}
}

// function to remove all special character that should not included in a "word"
// and turn them into uppercase.
void refineWord(vector<string>& words) {

	for (unsigned i = 0; i < words.size(); i++) {

		for (int j = words[i].size(); j >= 0; j--) {

			// remove and special character in words like "." at the end of the sentence
			if (!(isalnum(words[i][j]))) {

				words[i].erase(j, 1);

			}

			// turn words into uppercase
			words[i][j] = toupper(words[i][j]);
		}
	}
}


// complement function for sort
void swap(string& a, string& b) {

	string temp;

	temp = a;
	a = b;
	b = temp;

}

// functiion to display vector in an alphabetical order
// remove any duplicates. Pass by value so that we don't
// modify global vector contents
void alphabeticalDis(vector<string> words) {

	// alphabetical sort
	for (unsigned i = 0; i < words.size() - 1; i++) {

		for (unsigned j = 0; j < words.size() - i - 1; j++) {

			if (words[j] > words[j + 1]) {

				swap(words[j], words[j + 1]);

			}
		}
	}
	
	// omit duplicates
	for (unsigned i = 0; i < words.size() - 1; i++) {

		// if there is a dupplicate words, erase it from vector
		if (words[i] == words[i + 1]) {

			words.erase(words.begin() + i);

			// decreace index by one since vector size decrease by one after erase
			i--;

		}
	}


	// display sorted and omited vector
	cout << "3: ";
	for (unsigned i = 0; i < words.size(); i++) {


		cout <<  words[i] << " ";
	}

	cout << endl << endl;

}

int main() {

	// hold string input
	string input;

	// get input from user
	cout << "Enter a string: ";
	getline(cin, input);

	
	// vector to hold words in string
	vector<string> words;

	// extrac words from string and put them into vector
	extractWords(input, words);

	// remove any special character from words and capitalize them 
	refineWord(words);


	// display number of words
	cout << endl;
	cout << "1: " << words.size() << endl << endl;

	// print all word in reverse order
	cout << "2: ";
	for (unsigned i = 0; i < words.size(); i++) {

		for (int j = words[i].size(); j >= 0; j--) {

			cout << words[i][j];

		}

		cout << " ";
	}
	cout << endl << endl;


	// print words in alphabetical order and omit the duplicates
	alphabeticalDis(words);


	// print the words in the string in reverse order
	cout << "4: ";
	for (int j = words.size() - 1; j >= 0; j--) {

		cout << words[j] << " ";

	}
	cout << endl << endl;

	// Print all pairs of words in which one word in the string, containing more than one letter, is contained in another
	// need modify since a contained word which appear 
	cout << "5: ";
	for (unsigned i = 0; i < words.size(); i++) {

		// skip if this word has less than 2 characters
		if (words[i].size() <= 1) {
			continue;
		}

		// step through every word in the string
		for (unsigned j = 0; j < words.size(); j++) {

			//  skip if picking word is the test word
			if (j == i) { continue; };

			// hold value of found index
			int found = words[j].find(words[i]);

			// if found and this is not the duplicates couple, display word in size ascending order
			if (found != string::npos && words[i].size() < words[j].size()) {

				cout << words[i] << " " << words[j] << " ";

				// reset found index to 0
				found = 0;

			}
		}
	}
	cout << endl;
}



