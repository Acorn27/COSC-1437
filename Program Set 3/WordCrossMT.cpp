/*
Author: Mai Tran
COSC 1437
Program Set 3-2
Reference: None
*/

#include <iostream>
using namespace std;

// capitalize word
void upperCase(string& word) {

    for (unsigned i = 0; i < word.size(); i++) {

        word[i] = toupper(word[i]);
    }
}

int main() {

    string word1, word2;
    char runAgain = 'N';
    do {

        // prompt for 2 words
        cout << "\nEnter a word: ";
        cin >> word1;
        cout << "Enter a word: ";
        cin >> word2;

        // upper case word
        upperCase(word1);
        upperCase(word2);

        // cross flag
        bool found = false;

        // cross index
        int word1Index, word2Index;

        // step through word1
        for (unsigned i = 0; i < word1.size() && !(found); i++) {

            // step through word2;
            for (unsigned j = 0; j < word2.size(); j++) {

                // check if there is a cross
                if (word1[i] == word2[j]) {

                    found = true;

                    // save cross index in both word1 and word2
                    word1Index = i;
                    word2Index = j;

                }

            }
        }

        // display output if cross character exist
        if (found) {

            // display manip
            cout << endl;

            // display word1 horizontally at correct index
            for (unsigned i = 0; i < word2.size(); i++) {

                if (i == word2Index) {

                    cout << word1 << endl;

                }
                else {

                    // display space
                    string space;
                    for (int j = 0; j < word1Index; j++) {

                        space += " ";

                    }
                    cout << space;
                    // display one word2 verically per line
                    cout << word2[i] << endl;
                }
            }

        // if cross element not found, return error message
        } else {

            cout << "\nCANNOT CROSS WORDS\n";
        }

        cout << "\nRun Again (Y/n): ";
        cin >> runAgain;


    } while (runAgain == 'y' || runAgain == 'Y');

    return (0);

}