/*
Author: Mai Tran
Course: COSC 1437
Program Set 3-1
Reference: None
*/

#include <iostream>
#include <string>
#include <vector> 
using namespace std;

// check if 2d vector has horizontal symmetric or not
bool isHorizontal(const vector<vector<char > >& table) {


    // only check half of the table
    for (unsigned i = 0; i < table.size() / 2; i++) {

        // loop through all collumn in row
        for (unsigned j = 0; j < table[i].size(); j++) {

            //check horizontal symmetric
            if (table[i][j] != table[table.size() - i - 1][j]) {

                //return false if only one element violate the rules
                return (false);

            }

        }

    }

    // return true if passed this point
    return (true);
}


// check if 2d vector has horizontal symmetric or not
bool isVertical(const vector<vector<char > >& table) {

    // only check half of the table
    for (unsigned i = 0; i < table.size(); i++) {

        // loop through all collumn in row
        for (unsigned j = 0; j < table[i].size() / 2; j++) {

            //check horizontal symmetric
            if (table[i][j] != table[i][table[i].size() - j - 1]) {

                //return false if only one element violate the rules
                return (false);

            }

        }

    }

    // return true if passed this point
    return (true);
}

// check if 2d vector has southeast diagonal or not
bool isSE(const vector<vector<char > >& table) {

    // only check half of the table
    for (unsigned i = 0; i < table.size(); i++) {

        // loop through all collumn in row
        for (unsigned j = 0; j < table[i].size(); j++) {

            //check horizontal symmetric
            if (table[i][j] != table[j][i]) {

                //return false if only one element violate the rules
                return (false);

            }
        }
    }

    // return true if passed this point
    return (true);
}

// complement function for isNE function
void swap(char& a, char& b) {

    char temp;
    temp = a;
    a = b;
    b = temp;

}

// flip 2d vector up side down
void upSDown(vector<vector<char> >& table) {

    // loop half of the table
    for (unsigned i = 0; i < table.size() / 2; i++) {

        // loop through all collumn in row
        for (unsigned j = 0; j < table[i].size(); j++) {

            // swap opposite row data
            swap(table[i][j], table[table.size() - i - 1][j]);

        }
    }

}

// check if 2d vector has northeast diagonal or not
bool isNE(vector<vector<char > > table) {

    // flip 2d vector up side down
    upSDown(table);


    if (isSE(table)) {

        return (true);

    }
    else {

        return (false);
    }
}

int main() {

    // hold rectangle dimemsion
    int row, collumn;

    // run again flag
    char runAgain = 'N';

    do {

        // get rectangle size
        string temp;
        cout << "\nEnter the size: ";
        getline(cin, temp);

        // get row and collumn, assume proper input
        row = temp[0] - '0';
        collumn = temp[2] - '0';

        // 2d vector to hold table
        // initilize so that we don't have segmentation error
        vector<vector<char> > table;

        cout << "\nEnter the matrix:\n\n";
        for (int i = 0; i < row; i++) {

            // get row in string format
            getline(cin, temp);

            // temporary vector to store each row data
            vector<char> row;

            // collumn count
            int collumnCount = 0;

            // get collumn data on each row
            for (unsigned j = 0; j < temp.size() && collumnCount < collumn; j += 2) {

                row.push_back(temp[j]);
                collumnCount++;

            }

            // push each row data
            table.push_back(row);

        }


        // display output
        string output = "";
        if (isHorizontal(table)) {

            output += "H- Horizontal ";

        }

        if (isVertical(table)) {

            output += "V- Vertical ";

        }

        if (isSE(table)) {

            output += "S- SE Diagonal ";

        }

        if (isNE(table)) {

            output += "N- NE Diagonal ";

        }

        if (output == "") {

            cout << "\nNO SYMMETRIES\n";

        }
        else {

            cout << "\nThe matrix is symmetric: " << output << endl;

        }

        cout << "\nRun again(Y/N): ";
        cin >> runAgain;
        cin.ignore();

    } while (runAgain == 'Y' || runAgain == 'y');


}