/*
Author: Mai Tran
Course: COSC 1437
Program set 1
Reference: I did not get any specific help on this problem except some google search on iomanip function like how to use setw, setfill, etc
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

// get data from file, take file's name and string vector as parameters
// return true and read data from file into vector is file exist
// otherwise return false
bool getData(const string fileName, vector<string>& data) {

    ifstream inputFile(fileName);
    bool is_success;
    int count;

    if (inputFile >> count) {

        for (int i = 0; i < count; i++) {

            string temp;
            inputFile >> temp;
            data.push_back(temp);
        }

        is_success = true;

    }
    else {

        cout << "Error opening file\n";
        is_success = false;
    }

    return (is_success);
    inputFile.close();

}

// take a string (store each frame data) and a 2d vector as parameters. For 2d vector:
// row store number of frame, which size should be 10 after running function
// column store data for 2 throws each frame, 10th frame can hold up to 3 throws
void toVector(string str, vector<vector<char> >& v) {

    int count = 0;                              	// count to keep track of 2 tries per frame
    vector<char> temp;                          	// temporary vector to store information of each frame, which will be latter pushed into outer vector
    int vectorIndex = 0;                        	// keep track of vector's element index, used to identify the 10th frame

    for (unsigned i = 0; i < str.size(); i++) {

        // push number of pin knock down one by one into temp vector, increase count by one after each push
        temp.push_back(str[i]);
        count++;

        // special process for the 10th frame because this frame can hold up to 3 throws
        if (vectorIndex == 9) {

            // clear temp vector
            temp.clear();

            // a sub string to hold all elements from i to the end of string, which is the data for 10th frame
            string lastFrame = str.substr(i, str.size() - i + 1);

            // convert string into many singles char and push into temp vector
            for (char c : lastFrame) {
                temp.push_back(c);
            }

            // push temp into an outer vector and breakthrough loop because this is the last run
            v.push_back(temp);
            break;
        }

        // process for frame number from 1 to 9
        // if 2 balls has been throwed or a strike or a spare has been made
        // push that frame data into an outter vector
        // then reset temp vector and count variable
        if (count == 2 || str[i] == 'X' || str[i] == '/') {

            v.push_back(temp);
            // keep track of vector's element index
            vectorIndex++;
            // reset temp vector
            temp.clear();
            // reset count to 0
            count = 0;

        }
    }
}

// function to check if a set of value store in vector is a strike or not
bool isAStrike(const vector<char> v) {

    if (v[0] == 'X') {

        return (true);

    }
    else {

        return (false);
    }

}

// function to check if a set of value store in vector is a spare or not
bool isASpare(const vector<char> v) {

    if (v[1] == '/') {

        return (true);
    }
    else {

        return (false);

    }

}

// display separion line
void displaySeperateLine() {

    for (int count = 0; count < 107; count++) {
        cout << "-";
    }
    cout << endl;

}

// display separation line with slash
void displaySlashLine() {

    cout << setfill(' ') << setw(10) << "|";

    for (int count = 0; count < 10; count++) {

        if (count == 9) {
            cout << "|-----|";
        }
        else {
            cout << setfill('-') << setw(10) << "|---|";
        }
    }
}

// function to display first line
void display1Line() {

    cout << setw(12) << left << "\nGame";

    for (unsigned i = 1; i <= 10; i++) {

        cout << setw(10) << left << i;

    }

    cout << endl;
}

// fucntion to display each frame score, take 2d vector as constant parameter
void displayFrame(const vector<vector<char> > frame) {

    // display each frame score
    cout << setw(10) << left << "|";
    for (unsigned i = 0; i < frame.size(); i++) {

        string temp = "|";

        for (unsigned j = 0; j < frame[i].size(); j++) {

            // display '-' for missed throw
            if (frame[i][j] == '0') {
                temp += '-';
            }
            else {
                temp += frame[i][j];
            }

            temp += '|';

        }

        if (temp == "|X|") {
            temp = "  |X|";
        }

        cout << setw(10) << left << temp;

    }

    cout << endl;
}

// function to find each frame total score and count
// take a 2d vector, 2 integer arrays that hold each frame socre and count as parameter
// Frame score is the total socre of each frame before adding strike/spare bonus points
// Frame number is 1 if this is a strike, 2 if this is a spare, 10th frame can have up to 3 count
void findFrameIdentity(vector<vector<char> >& frame, int frameScore[10], int frameCount[10]) {

    for (unsigned i = 0; i < frame.size(); i++) {

        // special process for 10th frame
        if (i == 9) {
            // reset frame score to 0 just for sure
            frameScore[i] = 0;
            for (unsigned k = 0; k < frame[i].size(); k++) {

                // if there is strike increase score by 10
                if (frame[i][k] == 'X') {

                    frameScore[i] += 10;

                }   // if there is a spare, it must be the second throw, therefore, reset score to 10
                else if (frame[i][k] == '/') {

                    frameScore[i] = 10;

                }   // if is not a strike or a spare, treat it as a normal integer
                else {

                    frameScore[i] += (frame[i][k] - 48);

                }
                frameCount[i] = frame[i].size();

            }
        }// if there is a strike, set frame score to 10, count to 1
        else if (isAStrike(frame[i])) {

            frameScore[i] = 10;
            frameCount[i] = 1;

        }
        // if there is a spare, set frame score to 10, count to 2
        else if (isASpare(frame[i])) {

            frameScore[i] = 10;
            frameCount[i] = 2;
        }
        // if there is pin standing after 2 throws
        else {

            // just to make sure
            frameScore[i] = 0;

            for (unsigned j = 0; j < frame[i].size(); j++) {
                int value = frame[i][j] - 48;
                frameScore[i] += (frame[i][j] - 48);
            }
            frameCount[i] = 2;
        }

    }

}

// display total function, take 2d vector and 2 integer arrays frameSocre and frameCount as parameter
// display total for each frame
void displayTotal(vector<vector<char> > frame, int frameScore[10], int frameCount[10]) {

    // variable to hold total for each frame
    int total = 0;

    for (unsigned i = 0; i < frame.size(); i++) {

        // 10th frame, break loop because this is a last iteration
        if (i == frame.size() - 1) {
            total += frameScore[frame.size() - 1];
            cout << "|";
            cout << setfill(' ') << setw(5) << right << total << '|';
            cout << setw(5) << " \n";
            break;
        }

        // if this frame is a strike
        if (isAStrike(frame[i])) {

            // add 10 to total
            total += 10;

            // if next frame's count is 2, add next that frame's value to total
            if (frameCount[i + 1] == 2) {

                total += frameScore[i + 1];

            } // else if next frame's count is 1, add that frame value to total and divide the following frame into 2 scenario
            else if (frameCount[i + 1] == 1) {

                total += frameScore[i + 1];

                // if the following frame count is 1, add the whole following frame's value to total
                if (frameCount[i + 2] == 1) {

                    total += frameScore[i + 2];

                } // else if the following frame count is 2 or 3(10th frame)
                else {
                    // if that throw is a strike, add 10 total (only work in 10th frame)
                    if (frame[i + 2][0] == 'X') {
                        total += 10;
                    }
                    // else if that throw is not a strike, convert to int and add up to total
                    else {

                        int value = frame[i + 2][0] - 48;
                        total += value;
                    }
                }

            } // if next frame's count is 3, which is also mean that is a 10th frame
            else {

                total += frameScore[i + 1];
                total -= 10;
            }
        }
        // if this is a spare
        else if (isASpare(frame[i])) {

            // add 10 to total
            total += 10;

            // if the next frame's count is 1, add that frame's value to total    
            if (frameCount[i + 1] == 1) {

                total += frameScore[i + 1];
            } // else if the next frame's count is 2, add the the first throw value to total
            else {

                // if that first throw is a strike (10th frame scenario)
                if (frame[i][0] == 'X') {
                    total += 10;
                } // if that is the normal throw, convert char to int then add to total;
                else {

                    int value = frame[i + 1][0] - 48;
                    total += value;
                }
            }
        } // if this is not a spare as well as a strike
        else {

            total += frameScore[i];

        }
        // display total after each iteration
        cout << "|";
        cout << setfill(' ') << setw(3) << right << total << '|';
        cout << setw(5) << " ";


    }
}


int main() {

    string FileName;
    vector<string> data;
    // 2d vector to hold information for each testcase
    vector<vector<char> > frame;


    cout << "Enter the file name: ";
    cin >> FileName;
    if (getData(FileName, data)) {

        display1Line();

        for (unsigned i = 0; i < data.size(); i++) {

            displaySeperateLine();


            frame.clear();
            toVector(data[i], frame);

            displayFrame(frame);

            displaySlashLine();

            int frameScore[10] = { 0 };
            int frameCount[10] = { 0 };

            // find frame identity( which is frame's value and frame's count)
            findFrameIdentity(frame, frameScore, frameCount);
            cout << endl;

            //displayTotal
            cout << "|Game " << i + 1 << "   ";
            displayTotal(frame, frameScore, frameCount);


        }

    }

}










