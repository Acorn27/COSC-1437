/*
Author: Mai Tran
Course: COSC 1437
Program set 2-1
Reference:
I use the stringc++.pdf from chapter 10 to learn about find() and erase() string function
*/

#include <iostream>
#include <string>
using namespace std;

// Translation table
const int DASH_COUNT = 6;
const int ASTERISK_COUNT = 2;
const int ONE_COUNT = 4;
const int TWO_COUNT = 8;
const int THREE_COUNT = 2;
const int FOUR_COUNT = 1;
const int FIVE_COUNT = 2;
const int SIX_COUNT = 1;

char dash[DASH_COUNT] = { 'A', 'E', 'I', 'O', 'U', 'Y' };
char asterisk[ASTERISK_COUNT] = { 'H', 'W' };
char one[ONE_COUNT] = { 'B', 'F', 'P', 'V' };
char two[TWO_COUNT] = { 'C', 'G', 'J', 'K', 'Q', 'S', 'X', 'Z' };
char three[THREE_COUNT] = { 'D', 'T' };
char four[FOUR_COUNT] = { 'L' };
char five[FIVE_COUNT] = { 'M', 'N' };
char six[SIX_COUNT] = { 'R' };

// array of translate characters in data table
const int CHAR_COUNT = 8;
char characters[CHAR_COUNT] = { '-', '*', '1', '2', '3', '4', '5', '6' };

// function to check if test Characters is a dash/asterisk/...
// return true is test Characters can be translated into target character
// return true is convertible
bool isEquivalent(const char test, const char target) {

    // final return value of function, default to false 
    bool found = false;

    // switch statement to check the ASCII code of test Character
    switch (target) {

    case ('-'):

        for (int i = 0; i < DASH_COUNT && not(found); i++) {

            if (test == dash[i]) {
                found = true;
            }

        }
        break;

    case ('*'):

        for (int i = 0; i < ASTERISK_COUNT && not(found); i++) {

            if (test == asterisk[i]) {
                found = true;

            }

        }
        break;

    case ('1'):

        for (int i = 0; i < ONE_COUNT && not(found); i++) {

            if (test == one[i]) {
                found = true;

            }

        }
        break;


    case ('2'):

        for (int i = 0; i < TWO_COUNT && not(found); i++) {

            if (test == two[i]) {

                found = true;
            }

        }
        break;


    case ('3'):

        for (int i = 0; i < THREE_COUNT && not(found); i++) {

            if (test == three[i]) {

                found = true;

            }

        }
        break;

    case ('4'):

        for (int i = 0; i < FOUR_COUNT && not(found); i++) {

            if (test == four[i]) {

                found = true;

            }

        }
        break;

    case ('5'):

        for (int i = 0; i < FIVE_COUNT && not(found); i++) {

            if (test == five[i]) {

                found = true;
            }

        }
        break;


    case ('6'):

        for (int i = 0; i < SIX_COUNT && not(found); i++) {

            if (test == six[i]) {

                found = true;
            }

        }
        break;

    }

    // return final value
    return (found);
}

//convert to all uppercase and stripping any non-alphabetic characters 
string rmAndCap(string input) {

    for (unsigned i = 0; i < input.size(); i++) {

        input[i] = toupper(input[i]);

        if (!(isalpha(input[i]))) {

            input.erase(i, 1);
            i--;

        }

    }

    return(input);

}

int main() {

    // run Again flag
    char runAgain = 'N';

    // hold surname input
    string surName;


    do {

        cout << "\nEnter surname: ";
        getline(cin, surName);

        // remove non-alphabetic character and capitalize using rmAndCap function
        surName = rmAndCap(surName);

        // hold soundex
        string soundex;

        // apply the translation table to translate every character to a digit
        for (unsigned i = 0; i < surName.length(); i++) {

            for (int j = 0; j < CHAR_COUNT; j++) {

                if (isEquivalent(surName[i], characters[j])) {

                    soundex += characters[j];

                }
            }
        }

        // a copy of the original word translated 
        string originalCopy = soundex;


        // delete all occurrences of *
        int pos = soundex.find('*');
        while (pos != string::npos) {

            soundex.erase(pos, 1);
            pos = soundex.find('*');

        }



        // delete any digit that follows an identical digit
        for (unsigned i = 0; i < soundex.size() - 1; i++) {

            if (soundex[i] == soundex[i + 1]) {

                soundex.erase(i, 1);

            }
        }



        // Delete all occurrences of -
        pos = soundex.find('-');
        while (pos != string::npos) {

            soundex.erase(pos, 1);
            pos = soundex.find('-');

        }


        // If the first letter of the original word translated to a digit, replace that digit, which now begins 
        // the translated word, by the letter; otherwise prepend the letter to the translated word(prepend
        // is to 'beginning' as append is to 'end')
        if (isdigit(originalCopy[0])) {

            soundex[0] = surName[0];

        }
        else {

            soundex = surName[0] + soundex;

        }


        // The translated word now consists of a letter followed by zero or more digits. Discard all digits 
        // but the first three. If there are less than 3 digits, append '0's until there are 3 digits

        if (soundex.size() > 3) {

            soundex.erase(4, soundex.size() - 4);

        }
        else {

            while (soundex.size() <= 3) {

                soundex += '0';
            }

        }

        cout << "\nSoundex code for " << surName << " is " << soundex << endl;

        cout << "\nRun again (Y/N): ";
        cin >> runAgain;
        cin.ignore();

    } while (runAgain == 'y' || runAgain == 'Y');


}




