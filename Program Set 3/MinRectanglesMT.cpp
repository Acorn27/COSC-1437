/*
Author: Mai Tran
Course: COSC 1437
Program Set 3-3
Reference: None
*/

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;

// display table 
void display(vector<vector<int> >& table) {

    cout << "\nGenerated grid: \n";
    for (unsigned i = 0; i < table.size(); i++) {

        for (unsigned j = 0; j < table[i].size(); j++) {

            cout << table[i][j] << " ";

        }
        cout << endl;
    }
    cout << endl;
}

bool isPow2(const int number) {

    if (number == 1 || number == 2 || number == 4 || number == 8) {

        return (true);
    }
    else {

        return (false);

    }
}

bool isRectangle(vector<vector<int> > table, int row, int col, int rowCount, int colCount) {

    bool rectangle = true;

    if (rowCount == 1 || colCount == 1) { return false; };

    for (int i = row; i < row + colCount; i++) {

        for (int j = col; j < col + rowCount; j++) {

            if (table[i][j] != 1) {

                rectangle = false;
                break;
            }

        }

    }

    return (rectangle);

}

// check if group is overlap or not
bool checkPool(vector<string> sample, vector<string> pool, int score) {

    int count = score;
    //cout << "total count is: " << score << endl;
    for (unsigned i = 0; i < sample.size(); i++) {

        for (unsigned j = 0; j < pool.size(); j++) {

            if (sample[i] == pool[j]) {

                //cout << "Sampe " << i + 1 << ". " << sample[i] << " is matches with pool " << j << ". " << pool[j] << endl;
                --count;
                goto cnt;
                
            }
        }
    cnt:;
    }
    //cout << "After score is: " << count << endl;
    // check score
    if (count <= 0) {

        //cout << "TRUE\n\n";
        return true;
    }
    else {

        //cout << "FALSE\n\n";
        return false;
    }
}

// complement function sort vector
void swap(vector<vector<int> >& vt1, vector<vector<int> >& vt2) {

    vector<vector<int> > temp;
    temp = vt1;
    vt1 = vt2;
    vt2 = temp;
}

// sort rec
void sort(vector<vector<vector<int> > >& vtr) {

    unsigned i, j, min_idx;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < vtr.size() - 1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < vtr.size(); j++)
            if (vtr[j].size() < vtr[min_idx].size())
                min_idx = j;
        // Swap the found minimum element with the first element
        swap(vtr[min_idx], vtr[i]);

    }

}

// check if if group is overlapped on not
bool isOverlap(vector<vector<vector<int> > > table, int index) {


    vector<string> pool;
    vector<string> sample;

    for (unsigned i = 0; i < table.size(); i++) {

        for (unsigned j = 0; j < table[i].size(); j++) {

            string temp;
            for (unsigned k = 0; k < table[i][j].size(); k++) {

                temp += to_string(table[i][j][k]);

            }

            if (i == index) {

                sample.push_back(temp);

            }
            else {

                pool.push_back(temp);

            }
        }
    }

    return (checkPool(sample, pool, table[index].size()));
}
// get horizontal group
void getGroup(vector<vector<int> >& table, vector<vector<vector<int> > >& rectangle) {

    // get horizontal group
    for (unsigned i = 0; i < table.size(); i++) {

        for (unsigned j = 0; j < table[i].size(); j++) {

            // if element is 1
            if (table[i][j] == 1) {

                // bool variable to check if the next array element is 1 or not
                bool next = true;

                // save the first coordiate that we encounter 1
                vector<vector<int> > mid;
                vector<int> small;
                small.push_back(i);
                small.push_back(j);
                mid.push_back(small);

                // check if the next to value is 1 or not
                // if true, save the next coordinate
                for (unsigned index = j + 1; index < table[i].size() && next; index++) {

                    if (table[i][index] == 1) {

                        vector<int> temp;
                        temp.push_back(i);
                        temp.push_back(index);
                        mid.push_back(temp);

                    }
                    else {

                        next = false;

                    }
                }

                //todo: wrap around
                bool wrapNex = true;
                if (j == 0) {

                    // check mid size and table size so that we don't group the all 1 row twice
                    for (int index = table[i].size() - 1; index >= 0 && mid.size() != table[i].size() && wrapNex; index--) {

                        if (table[i][index] == 1) {

                            vector<int> temp;
                            temp.push_back(i);
                            temp.push_back(index);
                            mid.push_back(temp);

                        }
                        else {

                            wrapNex = false;

                        }
                    }
                }


                // group size must be the power of 2
                while (mid.size() != 1 && mid.size() != 2 && mid.size() != 4 && mid.size() != 8) {
                    mid.pop_back();
                }

                rectangle.push_back(mid);
            }
        }
    }
    
    // get vertical rectangle group
    for (unsigned j = 0; j < table[0].size(); j++) {

        // step through specific row for each collumn
        for (unsigned i = 0; i < table.size(); i++) {

            // if element is 1
            if (table[i][j] == 1) {

                // bool variable to check if the next array element is 1 or not
                bool next = true;

                // save the first coordiate that we encounter 1
                vector<vector<int> > mid;
                vector<int> small;
                small.push_back(i);
                small.push_back(j);
                mid.push_back(small);

                // check if the next to value is 1 or not
                // if true, save the next coordinate
                for (unsigned index = i + 1; index < table.size() && next; index++) {
                    if (table[index][j] == 1) {
                        vector<int> temp;
                        temp.push_back(index);
                        temp.push_back(j);
                        mid.push_back(temp);
                    }
                    else {
                        next = false;
                    }
                }

                
                //todo: wrap around
                bool wrapNex = true;
                if (i == 0) {
                    // check mid size and table size so that we don't group the all 1 row twice
                    for (int index = table.size() - 1; index >= 0 && mid.size() != table.size() && wrapNex; index--) {
                        if (table[index][j] == 1) {
                            vector<int> temp;
                            temp.push_back(index);
                            temp.push_back(j);
                            mid.push_back(temp);
                        }
                        else {
                            wrapNex = false;
                        }
                    }
                }
                
                // group size must be the power of 2
                while (mid.size() != 1 && mid.size() != 2 && mid.size() != 4 && mid.size() != 8) {
                    mid.pop_back();
                }
                rectangle.push_back(mid);
            }
        }
    }
    
    for (unsigned row = 0; row < table.size(); row++) {

        for (unsigned col = 0; col < table[row].size(); col++) {

            if (table[row][col] == 1) {

                //cout << "\ncoordinate is: (" << row << "," << col << ")\n";

                // flag to get a larger rectangle as much as possible
                bool rowNext = true;
                bool colNext = true;
                unsigned rowCount = 1,
                    colCount = 1;

                // check row
                for (unsigned colIndex = col + 1; colIndex < table[row].size() && rowNext; colIndex++) {

                    if (table[row][colIndex] == 1) {

                        rowCount++;

                    }
                    else { rowNext = false; };
                }
                //cout << "\nrow count is " << rowCount << endl;

                // check collumn
                for (unsigned rowIndex = row + 1; rowIndex < table.size() && colNext; rowIndex++) {

                    if (table[rowIndex][col] == 1) {

                        colCount++;
                    }
                    else { colNext = false; };
                }

                //cout << "\ncol count is " << colCount << endl;


                while (!(isPow2(rowCount))) { rowCount--; };
                while (!(isPow2(colCount))) { colCount--; };


                if (isRectangle(table, row, col, rowCount, colCount)) {

                    //cout << "\nThis is a rectangle\n";

                    // create a temporary vector
                    vector<vector<int> > mid;


                    for (unsigned i = row; i < row + colCount; i++) {

                        for (unsigned j = col; j < col + rowCount; j++) {

                            // create innter vector
                            vector<int> small;
                            small.push_back(i);
                            small.push_back(j);
                            mid.push_back(small);

                        }

                    }

                    rectangle.push_back(mid);
                }
            }
        }
    }
}



int main() {

    char runAgain = 'N';

    do {

        //get row and collumn, just ignore it for now
        int rowMax, collumnMax;
        cout << "\nEnter the number of rows (2-10): ";
        cin >> rowMax;
        cout << "Enter the number of collumn (2-10): ";
        cin >> collumnMax;

        srand((unsigned int)time(NULL));

        // generate random table
        vector<vector<int> >table;
        for (int i = 0; i < rowMax; i++) {

            vector<int> temple;
            for (int j = 0; j < collumnMax; j++) {

                temple.push_back(rand() % 2);
            }
            table.push_back(temple);
        }

        display(table);


        //3d vector to store rectangle and its coordinate
        vector<vector<vector<int> > > rectangle;

        // group
        getGroup(table, rectangle);

        sort(rectangle);

        // remove overlap rectangle
        for (unsigned i = 0; i < rectangle.size(); i++) {

            if (isOverlap(rectangle, i)) {

                rectangle.erase(rectangle.begin() + i);
                --i;
            }
        }

        if (DISPLAY) { display3D(rectangle); };
        cout << "The minimum number of rectangles/squares formed is " << rectangle.size() << endl;

        cout << "\nRun Again (Y/N): ";
        cin >> runAgain;

    } while (runAgain != 'N' && runAgain != 'n');

}