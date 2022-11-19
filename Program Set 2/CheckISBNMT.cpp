/*
Author: Mai Tran
Course: COSC 1437
Program Set 2 - EC
Reference: None
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// display digits in ISBN format
void display(vector<int>& digit) {

    for (unsigned i = 0; i < digit.size(); i++) {


        cout << digit[i];

        if (i == 2 || i == 3 || i == 6 || i == 11) {

            cout << '-';

        }
    }
}


// function to extract isbn digits into vectors. also check
// if there all digit enter is valid and range from 12 to 13 digits only
bool extractISBN(string str, vector<int>& digit) {

    // keep track number of digits
    int count = 0;

    // step through string
    for (unsigned i = 0; i < str.length(); i++) {

        // if character is a digit, convert it to int
        // then push into vector
        if (isdigit(str[i])) {

            digit.push_back(str[i] - 48);
            count++;


        }
        else if (str[i] == '-') {

            // skip any dash
            continue;

            // if character is not a digit or a dash
            // input is invalid
        }
        else {

            cout << "\nISBN can not contain of " << str[i] << endl;
            return false;

        }

        if ((i == str.length() - 1) && (count > 13 || count < 12)) {

            cout << "\nISBN input should contain 12-13 digits\n";
            return false;

        }
    }

    // return true if go up to this point
    return true;

}


// calculate the last digit
int calcCheckDigit(vector<int>& digit) {

    // hold sum of digit from a1 to a12 with proper coefficient
    int sum = 0;

    // calculate sum
    for (int i = 0; i <= 11; i++) {

        // if digits index is odd, multiply by 3 and add up to sum
        if (i % 2 != 0) {

            sum += 3 * digit[i];

            // if digit's index is even, multiply by one   
        }
        else {

            sum += digit[i];

        }
    }

    // calculate check digits
    int checkDigit = (10 - (sum % 10)) % 10;

    return (checkDigit);

}
int main() {

    char runAgain = 'y';
    string input;

    do {

        cout << "\nEnter an ISBN with or without the check digit (XXX-X-XXX-XXXXX-?): ";
        getline(cin, input);

        //  vector to hold ISBN digit
        vector<int> digit;

        // get ISBS into vector
        if (extractISBN(input, digit)) {

            // calculate check digit;
            int checkDigit = calcCheckDigit(digit);

            if (digit.size() == 12) {

                digit.push_back(checkDigit);
                cout << "\nThe ISBN with Check Digit: ";
                display(digit);
                cout << endl;

                // else mean digit size equal 13
            }
            else {

                cout << "\nThe ISBN ";
                display(digit);
                cout << " is";

                if (checkDigit == digit[12]) {

                    cout << " valid.\n";

                }
                else {

                    cout << " NOT valid.\n";

                }

            }
            // if input is invalid, run program again
        }
        else {

            continue;

        }



        cout << "\nRun again (Y/N): ";
        cin >> runAgain;
        cin.ignore();

    } while (runAgain == 'y' || runAgain == 'Y');


}


