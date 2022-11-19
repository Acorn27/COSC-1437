/*
Author: Mai Tran
course: COSC 1437
Program set 1
Reference: I didn't use any specific help. Just a quick google search on how to use stoi and to_string function. 
*/

#include <iostream>
#include <string>
using namespace std;

// a function to check if a year is a unique year or not
// take a string as parameter
// return true if year is a unique year, otherwise return false
bool isUnique(string str) {

    // return value for function, default as true
    bool isUnique = true;

    // nested loop to check if a year is unique or not
    for (unsigned i = 0; i < str.length() - 1; i++) {

        for (unsigned j = i + 1; j < str.length(); j++) {

            if (str[i] == str[j]) {

                // if there is 2 same elements in a number
                // set return value to false
                isUnique = false;

            }
        }
    }

    // return final value
    return isUnique;
}


// a function to find next unique year
// take a string as parameter
// return the next unique year as a string
string nextUnique(string str) {

    // continues to increase year number until it become a unique year
    do {

        // a integer varibale for year in order to use mathematic operation
        int number = stoi(str);

        // increase year number by one each iteration
        number++;

        // convert integer back to string to pass into isUnique function
        str = to_string(number);

        // stop if the year is already a unique year
        if (isUnique(str)) {

            break;

        }

        // I use while (true) and break instead of additional flag variable in order to increase the simplicity of the program
    } while (true);

    // return unique year
    return str;
}

int main() {

    // hold user input
    string currentYear;
    char repeat = 'y';

    do {

        cout << "\nEnter a year: ";
        getline(cin, currentYear);

        // input validation
        int year = stoi(currentYear);
        if (year < 0 || year > 10000) {

            cout << "Please enter year in range of 0-10000\n";
            continue;

        }

        // display next unique year
        cout << "\nThe next dstrinct year: " << nextUnique(currentYear) << endl;

        // run again or not
        cout << "\nRun again (Y/N): ";
        cin >> repeat;

        // elimate getline error for the next iteration
        cin.ignore();

    } while (repeat == 'Y' || repeat == 'y');

}


