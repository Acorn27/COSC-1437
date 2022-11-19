/*
Author: Mai Tran
Course: COSC 1437
Program set 1
Reference: I didn't use any specific help for this problem. Just google to fix some syntax error and string member's function
*/

#include <iostream>
#include <string>

using namespace std;

const int CARD_COUNT = 5,
RANK_COUNT = 13,  	// total number of rank
SUIT_COUNT = 4;   	// total number of suit
const char STANDARD_RANK[RANK_COUNT] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
const char STANDARD_SUIT[SUIT_COUNT] = { 'C', 'D', 'H', 'S' };
const char ROYAFLUSH[CARD_COUNT] = { 'A', 'T', 'J', 'Q', 'K' };

// convert user's string into 2 supplement arrays, which used to store rank and suit
void toArray(string str, char rank[CARD_COUNT], char suit[CARD_COUNT]) {

    // an variable to keep track of array's index
    int arrayIndex = 0;

    for (unsigned i = 0; i < str.length(); i += 3) {

        // convert card's rank into array (convert to uppercase if needed)
        if (isalpha(str[i])) {

            rank[arrayIndex] = toupper(str[i]);

        }
        else {

            rank[arrayIndex] = str[i];

        }

        // convert card's suit into array (convert to uppercase if needed)
        if (isalpha(str[i + 1])) {

            suit[arrayIndex] = toupper(str[i + 1]);

        }
        else {

            suit[arrayIndex] = str[i + 1];

        }


        // increase array index by one
        arrayIndex++;

    }

}


// input validation, return true if card entered is valid
// otherwise display the error message and return false
bool isvalid(char rank[CARD_COUNT], char suit[CARD_COUNT]) {

    int rankValidCount = 0;
    int suitValidCount = 0;
    bool isDuplicate = false;
    bool isvalid = true;


    for (int i = 0; i < CARD_COUNT; i++) {

        // Check if entered ranks is valid or not
        for (int j = 0; j < RANK_COUNT; j++) {

            if (rank[i] == STANDARD_RANK[j]) {

                // if each rank matched, increase valid count by one
                // if total valid count is 5 at the end of the loop
                // we get the valid input
                rankValidCount++;

            }
        }


        // check illegal suit
        for (int j = 0; j < SUIT_COUNT; j++) {

            if (suit[i] == STANDARD_SUIT[j]) {

                // if each suit matched, increase valid count by one
                // if total valid count is 5 at the end of the loop
                // we get the valid input
                suitValidCount++;

            }
        }


        // check duplicate card
        for (int j = i + 1; j < CARD_COUNT; j++) {

            if (rank[i] == rank[j] && suit[i] == suit[j]) {

                isDuplicate = true;

            }
        }

    }

    // check if the cards rank/suit is valid or not
    // display if user entered an illegal/duplicate card
    if (rankValidCount != CARD_COUNT || suitValidCount != CARD_COUNT) {

        cout << "You entered an illegal card\n";
        isvalid = false;

    }

    // display if user entered an illegal card
    if (isDuplicate) {

        cout << "You entered the same card twice\n";
        isvalid = false;

    }

    // if user didn't entered illegal/duplicate card, return true as default
    return isvalid;
}


// complement function for sort algorithm
void swap(int& a, int& b) {

    int temp = a;
    a = b;
    b = temp;

}


// return card entered's index into another array and sorted into ascending order
// fors example, if the first card's rank is T, then its index should be 9
// therefore if rank entered is  A K Q J T, sequence array should be {0, 9, 10, 11, 12}
void returnSequence(const char rank[], int rankSize, int sequence[]) {

    int i;
    int j;

    // add each rank's index into an array
    for (i = 0; i < rankSize; i++) {

        for (j = 0; j < RANK_COUNT; j++) {

            if (rank[i] == STANDARD_RANK[j]) {

                sequence[i] = j;

            }
        }
    }


    // sort an created sequence array in ascending order
    // so that we can check if they are differ by one or not
    for (int start = 0; start < (rankSize - 1); start++) {

        int minIndex = start;
        int minValue = sequence[start];

        for (int index = start + 1; index < rankSize; index++) {

            if (minValue > sequence[index]) {

                minValue = sequence[index];
                minIndex = index;
            }

        }
        swap(sequence[minIndex], sequence[start]);
    }


}

// check is card's ranks index in list is differ by one or not
// if all of them is differ than one, then return true
// the third parameter is used as the start index for checking loop
bool inSequence(const int sequence[], int SIZE, int start) {

    for (int i = start; i < SIZE - 1; i++) {

        // if any of the consecutive index couple is not differ by one, return false
        if ((sequence[i + 1] - sequence[i]) != 1) {
            return false;
        }

    }

    // if programs passed this point, return true
    return (true);
}

// check if 5 cards entered is a Straight
bool isStraight(const char rank[CARD_COUNT], const char suit[CARD_COUNT]) {

    // array to store rank's index
    int sequence[CARD_COUNT];

    // find and sort rank index into an array names sequence
    returnSequence(rank, CARD_COUNT, sequence);

    // if this set of card has 'A' (which mean the first value of the sorted sequence must be 0)
    // If so there is only 2 scenario that this set of card can be a Straight which is A2345 and ATJQK
    // therefore, if the second value equal 1 (which mean the second rank is 2) or 9 (which mean the second rank is T)
    // we only need to check if all other value are in order(differ by one)
    if (sequence[0] == 0 && (sequence[1] == 1 || sequence[1] == 9)) {

        // check other of all other value except the first value (which is A), that is why we start at 1, not 0
        if (inSequence(sequence, CARD_COUNT, 1)) {
            return (true);
        }
        // if this set of card don't have 'A', process as normal
    }
    else {

        // if all value (start at 0) are in order(differ by one), return true
        if (inSequence(sequence, CARD_COUNT, 0)) {
            return (true);
        }

    }

    // if data set failed the previous if statement, then return false
    return (false);
}

// check if 5 cards entered is a flush
bool isFlush(const char suit[CARD_COUNT]) {

    // if all suit is the same then this is a flush
    for (int i = 0; i < CARD_COUNT - 1; i++) {

        // if only one couple is different, return false
        if (suit[i] != suit[i + 1]) {
            return (false);
        }
    }

    // if go up to this point, return true
    return (true);
}

// check if this set consisted of Ace, 10, King, Queen, Jack
bool isAKQJT(const char rank[]) {

    // a variable to keep track of matched rank
    int checkCount = 0;

    for (int i = 0; i < CARD_COUNT; i++) {

        for (int j = 0; j < CARD_COUNT; j++) {

            // if rank is matched with any of A, T, K, Q, or J increase count variable by one
            if (rank[i] == ROYAFLUSH[j]) {
                checkCount++;

            }
        }
    }

    // if all of the rank matched return true, otherwise return false
    if (checkCount == 5) {

        return (true);

    }
    else {

        return (false);
    }

}

int main() {

    // arrays to hold card's rank and suit
    char rank[CARD_COUNT];
    char suit[CARD_COUNT];

    // hold user's input
    string input;
    char runAgain = 'Y';

    do {

        cout << "\nDeal five cards: ";
        getline(cin, input);

        // convert string inputted string into two arrays
        toArray(input, rank, suit);

        cout << endl;

        // input validation
        if (isvalid(rank, suit)) {

            // Royal flush check
            if (isStraight(rank, suit) && isFlush(suit) && isAKQJT(rank)) {

                cout << "This is a Royal Flush\n";

            }
            // Straight flush check
            else if (isStraight(rank, suit) && isFlush(suit)) {

                cout << "This is a Straight Flush\n";

            }
            // flush check
            else if (!(isStraight(rank, suit)) && isFlush(suit)) {

                cout << "This is a FLush\n";

            }
            // Straight check
            else if (isStraight(rank, suit)) {

                cout << "This is a Straight\n";

            }
            // high card check
            else {

                cout << "This is nothing - High Card\n";

            }

        }
        // if input is invalid, ask user to enter 5 cards again
        else {

            cout << "Please re-enter your cards\n";
            continue;

        }

        // run-again decision
        cout << "\nRun again (Y/N): ";
        cin >> runAgain;

        // elimate getline error for the next iteration
        cin.ignore();

    } while (runAgain == 'y' || runAgain == 'Y');
}

