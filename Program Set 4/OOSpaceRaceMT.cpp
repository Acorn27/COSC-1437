/*
Author: Mai Tran
Course: COSC 1437
Program Set 4 - Required Problem
Reference:
    I used check prime number number function code from this website
    https://www.programiz.com/cpp-programming/examples/prime-number
    I used check perfect square number code from this website:
*/

#include <iostream>
#include <cstdlib> //for random numbers
#include <string>
#include <cmath>
#include <string>
#include <iomanip> //for setw()
using namespace std;

// data structure for space ship position information
struct Position
{
    unsigned startPosition,     // postion at the start of each move
        midPostion,             // psotion after roll
        newPosition;            // position after bonus/penalty point is apply
};

// SpaceShip class
class SpaceShip {

// private member
private:

    // spaceShip moveNo or turn
    unsigned moveNo;

    // hold ship positon 
    Position shipPos;

    // value of dice for each roll
    unsigned diceValue;

    // bonus point message for each move, if pos
    string bonusMess;

    // utility method, check for prime
    bool isPrime(unsigned);

    // utility method, check for perfect square
    bool isPerfectSquare(unsigned);

// public method
public:

    // constructor
    SpaceShip();

    // move ship to a new position
    void moveShip();

    // display data after each move
    void displayMove();

    // return ship positon
    unsigned getPosition() {
        return (shipPos.newPosition);
    }

    // get total number of move before winning
    unsigned getMove() {
        return moveNo;
    }
};

// constructor
SpaceShip::SpaceShip() {

    // set move number to 0
    moveNo = 0;

    // set Position
    shipPos.startPosition = shipPos.midPostion = shipPos.newPosition = 1;

    // set dice value to 0
    diceValue = 0;

    // set bonus message to start
    bonusMess = "Start";

}

// utility private method: check for prime number
bool SpaceShip::isPrime(unsigned n) {

    unsigned i = 1;
    bool is_prime = true;
    if (n == 0 || n == 1) {
        is_prime = false;
    }

    // loop to check if n is prime
    for (i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            is_prime = false;
            break;
        }
    }
    return (is_prime);
}

// utility private method: check for perfect square number
bool SpaceShip::isPerfectSquare(unsigned x)
{
    // Find floating point value of
    // square root of x.
    if (x >= 0) {

        unsigned sr = int(sqrt(x));

        // if product of square root
        //is equal, then
        // return T/F
        return (sr * sr == x);
    }

    // else return false if n<0
    return false;
}

// mutator: rool dice to demtermin ship's move
void SpaceShip::moveShip() {

    // reset bonus message
    bonusMess = "";

    // get random dice value, in range of 1-20
    diceValue = rand() % 20 + 1;

    // set ship start position
    shipPos.startPosition = shipPos.newPosition;

    // set ship positive after roll dice but before bonus point
    shipPos.midPostion = shipPos.startPosition + diceValue;

    int temp = shipPos.midPostion;

    // prime number bonus point
    if (isPrime(temp)) {

        // set bonus 
        bonusMess = "Prime Number";
        temp++;
        while (!isPrime(temp)) {
            temp++;
        }

    } // perfect square penalty
    else if (isPerfectSquare(temp)) {

        bonusMess = "Perfect Square";
        temp--;
        while (!(isPerfectSquare(temp))) {
            temp--;
        }

    }

    // set final positoin
    shipPos.newPosition = temp;

    // increase move number
    moveNo++;
}

// display move data
void SpaceShip::displayMove() {

    // display move and old position
    cout << moveNo << "\t" << setw(10) << shipPos.startPosition << "\t";

    // display card drawed
    cout << setw(10) << diceValue << "\t";

    // display new pos and bons string
    cout << setw(5) << shipPos.newPosition << "\t" << setw(20) << bonusMess << endl;
    cout << "---------------------------------------------------------------------" << endl;

}

//display the heading
void displayHeading()
{
    cout << "\nMove#\tCurrent Position\tCard\tNew Position\tSpace Bonus" << endl;
    cout << "---------------------------------------------------------------------" << endl;
}


int main() {

    // seed randomizer
    srand((unsigned int)time(NULL));

    // create ship object
    SpaceShip ship1, ship2;

    // display heading
    cout << "\n\t\t\tSHIP 1\n";
    displayHeading();

    // play ship1
    do {
        ship1.moveShip();
        ship1.displayMove();

    } while (ship1.getPosition() < 1000);

    // display ship2 heading
    cout << "\n\t\t\tSHIP 2\n";
    displayHeading();

    // play ship2
    do {
        ship2.moveShip();
        ship2.displayMove();

    } while (ship2.getPosition() < 1000);


    // Display result
    cout << "\n-----------SUMARY---------\n";
    cout << "Ship 1: " << " total moves: " << ship1.getMove() << endl;
    cout << "Ship 2: " << " total moves: " << ship2.getMove() << endl;

    // get winner
    cout << "=> ";
    if (ship1.getMove() > ship2.getMove()) {
        cout << "Ship 2 Won\n";
    }
    else if (ship1.getMove() == ship2.getMove()){
        cout << "Tie\n";
    }
    else {
        cout << "Ship 1 Won\n";
    }

    return 0;
}