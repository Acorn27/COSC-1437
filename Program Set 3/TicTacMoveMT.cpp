/*
Author: Mai Tran
Course: COSC 1437
Program Set 3-EC
Reference:
    +I moodify the TicTac code from this website:
    https://www.stechies.com/tic-tac-toe-cpp/

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// display board
void displayGrid(vector<vector<char> > arr) {

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {

            cout << arr[i][j] << " ";

        }
        cout << endl;
    }
    cout << endl;
}

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

// check if we have immediate win, if yes, change row and collumn
// to win location, symbol can be 'O' or 'X'
bool immeWin(vector<vector<char> > board, const char symbol, int& row, int& collum) {

    // step through both row and collumn by manipulated i 
    for (int i = 0; i < 3; i++) {

        // variable to keep track number of time 'O' or 'X appear in a row
        // if appears more than 2 time and the there is a '.' row
        // that is a one move in row
        int score = 0;
        int Olocation = -1;

        // check if we have a horizontal win
        for (int index = 0; index < 3; index++) {

            // accumulate socre if it is 'O' or 'X'
            if (board[i][index] == symbol) {
                score++;

                // if this is a '.', save '.' location in row
            }
            else if (board[i][index] == '.') {
                Olocation = index;
            }
        }
        // if requirement meet, return row and collumn location, stop function
        if (score >= 2 && Olocation != -1) {

            row = i;
            collum = Olocation;
            return true;

        }

        // check if we have a vertical win, same as horizontal 
        // reset score and winning index
        score = 0;
        Olocation = -1;
        for (int index = 0; index < 3; index++) {

            if (board[index][i] == symbol) {
                score++;
            }
            else if (board[index][i] == '.') {
                Olocation = index;
            }
        }
        if (score >= 2 && Olocation != -1) {

            row = Olocation;
            collum = i;
            return true;

        }

        // check if we have a SouthEast diagonal win, procedure are the same except board coordinate
        score = 0;
        Olocation = -1;
        if (i == 0) {
            for (int i = 0; i < 3; i++) {

                if (board[i][i] == symbol) {
                    score++;
                }
                else if (board[i][i] == '.') {
                    Olocation = i;
                }
                if (score >= 2 && Olocation != -1) {

                    row = Olocation;
                    collum = Olocation;
                    return true;
                }
            }
        }


        // check if we have a NorthEast diagonal win, procedure are the same except board coordinate
        score = 0;
        Olocation = -1;
        if (i == 0) {
            for (int i = 0; i < 3; i++) {

                if (board[i][2 - i] == symbol) {
                    score++;
                }
                else if (board[i][2 - i] == '.') {
                    Olocation = i;
                }
                if (score >= 2 && Olocation != -1) {

                    row = Olocation;
                    collum = 2 - Olocation;
                    return true;
                }
            }
        }
    }

    //if all other scenario fail, we don't have a one move win
    // return false
    return false;
}

// complement function for twoPWin: check if specific row contains only 'O' and '.' or not
bool checkRow(vector<vector<char> > table, const int row) {

    // step through row
    for (int i = 0; i < 3; i++) {

        // if contain 'X' return false immediately
        if (table[row][i] == 'X') {

            return false;
        }
    }
    // otherwise, return true
    return true;

}

// complement function for twoPWin: check if specific collumn contains only 'O' and '.' or not
bool checkCollumn(vector<vector<char> > table, const int collumn) {

    // step through collumn
    for (int i = 0; i < 3; i++) {

        // if collumn contain 'X', retunr false
        if (table[i][collumn] == 'X') {

            return (false);

        }
    }
    // otherwise, return true
    return true;
}

//check if we have a two potential move win. if yes, change row and collumn
// to win location
bool twoPWin(vector<vector<char> > board, int& row, int& collumn) {

    // vector to hold possible row and collumn win
    // possible rows are the row that contain 'O' and '.' only, the same apply to possible collumn
    // contain of a possible row and collumn can be used
    // to create a two potential move win if there cross each other
    vector<int> possibleRow;
    vector<int> possibleCollumn;

    // step through board
    for (int r = 0; r < 3; r++) {

        for (int c = 0; c < 3; c++) {

            // if this is 'O' check if it has a possible row/collumn win or not
            if (board[r][c] == 'O') {

                // if yes, push that row into possible row pool
                if (checkRow(board, r)) {
                    possibleRow.push_back(r);
                }
                // if yes, push collumn into possible collumn pool
                if (checkCollumn(board, c)) {
                    possibleCollumn.push_back(c);
                }
                // if this is a 'X' this, this is not a possible row or collumn
                // skip to the next coordinates
            }
            else if (board[r][c] == 'X') {

                continue;
            }
        }
    }

    // process vector contents: if there is a 2 potential one-move win or not
    // if both vector size is greater than 0 and they are not created by the same 'O' location
    if (possibleCollumn.size() != 0 && possibleRow.size() != 0 && board[possibleRow[0]][possibleCollumn[0]] != 'O') {
        for (unsigned i = 0; i < possibleRow.size(); i++) {

            for (unsigned j = 0; j < possibleCollumn.size(); j++) {

                if (board[possibleRow[i]][possibleCollumn[j]] == '.') {

                    row = possibleRow[i];
                    collumn = possibleCollumn[j];
                    return true;
                }

            }

        }
        // if there is no possible winning collumn and there is more than 1 possible winning row
        // this is the 4th scenarion: The move gives you one potential one-move win.
    }
    else if (possibleCollumn.size() == 0 && possibleRow.size() >= 1) {

        for (int i = 0; i < 3; i++) {

            if (board[possibleRow[0]][i] == '.') {

                row = possibleRow[0];
                collumn = i;
                return true;

            }

        }
        // if there is no possible winning row and there is more than 1 possible winning collumn
        // this is the 4th scenarion: The move gives you one potential one-move win.
    }
    else if (possibleRow.size() == 0 && possibleCollumn.size() >= 1) {

        for (int i = 0; i < 3; i++) {

            if (board[i][possibleCollumn[0]] == '.') {

                row = i;
                collumn = possibleCollumn[0];
                return true;

            }

        }
        // if possible win row and collumn both create by the same 'O' location
        // pick a random coordinte on collumn and row index depend on the location of 'O'
    }
    else if (possibleRow.size() == 1 && possibleCollumn.size() == 1 && board[possibleRow[0]][possibleCollumn[0]] == 'O') {

        int r = 0;

        // if 'O' row location is 1 or 2, next move's row location should be 0 or 1
        if (possibleRow[0] > 1) {

            r = possibleRow[0] - 1;
            // if 'O' row location is 0, next move' row location should be 1 
        }
        else {
            r = possibleRow[0] + 1;
        }

        row = r;
        collumn = possibleCollumn[0];
        return true;

    }

    // if all scenarios fail, this can't be either 3rd or 4th scenario
    return false;
}

int main() {

    // file stream object
    fstream inputFile;

    // hold file's name
    string fileName;

    // get file's name from user
    cout << "\nEnter the file Name: ";
    cin >> fileName;

    // check if file exist
    if (openFile(inputFile, fileName)) {

        // hold total number of sample
        int sampleCount;
        inputFile >> sampleCount;

        // skip the sample count line
        string temp;
        getline(inputFile, temp);

        // define a n dimemsional array, n depend on total number of sample
        //char grid[3][3][3];



        // display manip
        cout << endl;

        // step through each sample
        for (int i = 0; i < sampleCount; i++) {
            
            vector<vector<char> > grid;

            // get board contents into array 
            for (int j = 0; j < 3; j++) {

                getline(inputFile, temp);

                vector<char> tempV;

                // push board contents in to array
                for (unsigned index = 0; index < temp.size(); index++) {
                    
                    tempV.push_back(temp[index]);

                }
                grid.push_back(tempV);
            }

            // temporary variable to store location of the next move
            int row, collumn;

            // if 'O' has an immediate one move win
            if (immeWin(grid, 'O', row, collumn)) {

                grid[row][collumn] = 'O';

                // if 'X' has an immediate one move win, use 'O' to block that location
            }
            else if (immeWin(grid, 'X', row, collumn)) {

                grid[row][collumn] = 'O';

                // if we have a two or one potential winning move
            }
            else if (twoPWin(grid, row, collumn)) {

                grid[row][collumn] = 'O';

                // middle square move
            }
            else if (grid[1][1] == '.') {

                grid[1][1] = 'O';

                // top right move
            }
            else if (grid[0][2] == '.') {

                grid[0][2] = 'O';

                // error check 
            }
            else {

                cout << "\nCAN'T DECIDE NETX MOVE\n";
                return (0);

            }

            // display board
            cout << "Board #" << i + 1 << endl;
            displayGrid(grid);
            grid.clear();

        }
        // display if file is not exist
    }
    else {

        cout << "\nError openning file!\n";
    }
}
