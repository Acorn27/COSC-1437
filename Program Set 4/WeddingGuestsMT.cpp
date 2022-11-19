
/*
Author: Mai Tran
Course: COSC 1437
Program Set 4 - 1
Reference: None
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>        // header for sort
using namespace std;

// file opening function
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

class weddingList {

private:

    // hold birde and groom guests data list
    vector<string> brideList, groomList;

    // hold required list to output
    vector<string> guestList, guestOfBoth, brideGuest, groomGuest;

    // generate 4 required list from data list
    void generateRequiredList();

public:

    // split string by space and push into vector
    void refine(vector<string>&, string);

    // constructor for weddingList
    weddingList(string, string);

    //  accessor
    void display();
};

// construtor
weddingList::weddingList(string bList, string gList) {

    // set data for brideList and groomList
    refine(brideList, bList);
    refine(groomList, gList);

    // generate 4 required list
    generateRequiredList();

}

// member function of weddingList, display all 4 required lists
void weddingList::display() {

    // display all guest attending
    cout << "\nGuests: ";
    if (guestList.size() == 0) {
        cout << "None";
    }
    else {

        for (unsigned i = 0; i < guestList.size(); i++) {

            cout << guestList[i] << " ";
        }
    }

    // display guests appearing on both bride’s and groom’s lists 
    cout << "\nGuests of Both: ";
    if (guestOfBoth.size() == 0) {
        cout << "None";
    }
    else {

        for (unsigned i = 0; i < guestOfBoth.size(); i++) {

            cout << guestOfBoth[i] << " ";
        }
    }

    // display bride's guests not on the grooms list 
    cout << "\nBride's Guests: ";
    if (brideGuest.size() == 0) {
        cout << "None";
    }
    else {

        for (unsigned i = 0; i < brideGuest.size(); i++) {

            cout << brideGuest[i] << " ";
        }
    }

    // display groom's guests not on the birdes list 
    cout << "\nGroom's Guests: ";
    if (groomList.size() == 0) {
        cout << "None";
    }
    else {

        for (unsigned i = 0; i < groomGuest.size(); i++) {

            cout << groomGuest[i] << " ";
        }
    }
}


// split command by space and push plitted words into vector
void weddingList::refine(vector<string>& element, string input) {

    string temp;
    for (unsigned i = 0; i < input.size(); i++) {

        // temporary string to accumulate word
        if (input[i] != ' ') { temp += input[i]; };

        // add word to vector if encoutere space or end of string
        if (input[i] == ' ' || i == input.size() - 1) {

            element.push_back(temp);
            temp = "";
            continue;

        }
    }
}

// member function of weddingList, generated all required list
void weddingList::generateRequiredList() {

    // Generate list for all guests
    // copy birdeList to temp, then append groom list at the end
    vector<string> temp = brideList;
    temp.insert(temp.end(), groomList.begin(), groomList.end());

    // sort in alphabetical order
    sort(temp.begin(), temp.end());

    // remove duplicate name
    for (unsigned i = 0; i < temp.size() - 1; i++) {

        if (temp[i] == temp[i + 1]) {

            // guest appear on both list
            guestOfBoth.push_back(temp[i]);

            // remove the duplicate
            temp.erase(temp.begin() + i + 1);
        }
    }

    // asign guests list to temp and reset temp
    guestList = temp;
    temp.clear();

    // Generate list of guess appear on brides list only
    for (unsigned i = 0; i < brideList.size(); i++) {

        bool unique = true;
        for (unsigned j = 0; j < guestOfBoth.size(); j++) {

            if (brideList[i] == guestOfBoth[j]) {

                unique = false;
            }
        }
        if (unique) {
            temp.push_back(brideList[i]);
        }
    }
    // sort, assign, then reset
    sort(temp.begin(), temp.end());
    brideGuest = temp;
    temp.clear();


    // Generate list of guess appear on groom list
    for (unsigned i = 0; i < groomList.size(); i++) {

        bool unique = true;
        for (unsigned j = 0; j < guestOfBoth.size(); j++) {

            if (groomList[i] == guestOfBoth[j]) {

                unique = false;
            }
        }
        if (unique) {
            temp.push_back(groomList[i]);
        }
    }

    // sort, assign, then reset
    sort(temp.begin(), temp.end());
    groomGuest = temp;
    temp.clear();

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

        // process each sample
        for (int i = 0; i < sampleCount; i++) {

            // hold bride and groomlist
            string list1, list2;

            // get bride list
            getline(inputFile, list1);

            // get groom list
            getline(inputFile, list2);

            // define and initilized wedding plan object
            weddingList weddingPlan(list1, list2);

            // display required list
            cout << "\nWedding " << i + 1 << ":";
            weddingPlan.display();

            // line between each sample
            cout << endl;

        }

     // if file opened unsucessfully
    }
    else {

        cout << "\nFile does not existed\n";
    }

    return 0;

}
