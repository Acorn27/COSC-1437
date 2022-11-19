/*
Author: Mai Tran
Course: COSC 1437
Program Set 4-3
Reference: I interpret the rule of card game from this website:
            https://www.calstatela.edu/sites/default/files/users/u2536/MATH-4740/poker-hand-cheat-sheet.pdf
*/

#include <iostream>
#include <cstdlib> //for random numbers
#include <vector>
#include <string>
using namespace std;

// number of dice
const int DICE_NUM = 5;

// hand value structure
struct hand {

    // "Five of a kind" , "Four of a kind",...
    string combinationName = "";

    // value of combination. Format is abcxy
    // five of a kind: 5x, where x is the rank of five identical dices
    // four of a kind: 4xy, where x is the rank of four identical dices, y is the value of the remaining dice
    // full house: 32xyz, x is the rank of 3 identical dice, y is the ranks of 2 identical dices, z is the rank of the remaining dice
    // three of a kind: 31xy, x is the rank of 3 identical dices, y is the sum of the remaining dice
    // two pair: 22xyz, x is the rank of the first pair(which is the higher rank), y is the rank of the lower pair, z is the rank of the remaining dice
    // a pair: 1xy, x is the rank of a pair and y is the sum of the last 3 dices
    // nothing 0x, x is the sum of five different dices.

    // Note: If sum is greater than 10, which is 1x, convert to 9x so that we have a more accurate comparasion later on
    string combinationValue = "";
};

// diceGame class
class DiceGame {

    // Member variables
    private:

        // mode of game: Test or Game 
        char gameMode;

        // value of five dices for computer
        vector<string> computerDices;

        // value of five dices for player
        vector<string> playerDices;

        // utility method to process string input (get into vector)
        void refine(vector<string>&, string);

        // generate hand value based on fives dice value 
        void generateHandValue();

        // store hand values(consist of combination name and value)
        hand playerHand,
             computerHand;

        // money lose for each round
        int moneyLost;

        // money bet
        unsigned bet;

    // member functions
    public:

        // constructor, take game mode, and initial money as parameter
        DiceGame(char, unsigned);

        // destructor
        ~DiceGame() {

            // reset values of five dices (just to make sure)
            computerDices.clear();
            playerDices.clear();
        }

        // Acessor: display value of five dices if user choose Game mode
        void display();

        // Accessor: debug purpose only, display coded valude of Hand (work with arithmetric comparasion)
        void displayHand() {

        cout << "Computer has " << computerHand.combinationName << endl;// << "-" << computerHand.combinationValue << endl;
        cout << "You have " << playerHand.combinationName << endl;;// << "-" << playerHand.combinationValue << endl;

    }

        // display winner of each row
        void getWinner();

        // check for invalid input
        bool errorCheck();

        // get number of money lost for each round
        int getMoneyLost() {
            return moneyLost;
        }
};

// Constructor: Take game mode and initial money as parameter
// G mode: random generate roll values
// T mode: get roll values from user
DiceGame::DiceGame(char gameMode, unsigned moneyBet) {

    // upper case game mode 
    gameMode = toupper(gameMode);

    // initilized money lost
    moneyLost = 0;

    // get money bet
    bet = moneyBet;

    // construct object based on game mode
    if (gameMode == 'T') {

        // hold user's input
        string temp;

        // eliminate getline error
        cin.ignore();

        // error check loop
        loop:

        // get computer dices values
        cout << "\nEnter computer values: ";
        getline(cin, temp);
        refine(computerDices, temp);

        // get player dices values
        cout << "Enter player values: ";
        getline(cin, temp);
        refine(playerDices, temp);

        // check user's input
        if (!errorCheck()) {
            cout << "\nPlease enter a valid input.\n";
            playerDices.clear();
            computerDices.clear();

            // get user to enter again
            goto loop;
        }

    } // random game mode
    else if (gameMode == 'G') {

        // seed randomizer for rand
        srand((unsigned int)time(NULL));

        // temp vector to hold random number 
        vector<string> temp;

        // get computer dices values
        for (int i = 0; i < DICE_NUM; i++) {

            string random = to_string(rand() % 6 + 1);
            temp.push_back(random);

        }
        computerDices = temp;

        // reset temp
        temp.clear();

        // get player dices values
        for (int i = 0; i < DICE_NUM; i++) {

            string random = to_string(rand() % 6 + 1);
            temp.push_back(random);

        }
        playerDices = temp;
        temp.clear();
    }

    // immediate generate hand value from founded dice value
    generateHandValue();
}

// member function
void DiceGame::generateHandValue() {

    // Vector to hold the repition of dices side
    // e.g. if 1-sides is rolled for 3 time
    // the first element of score is set to 3 and so on
    vector<int> playerScore = { 0, 0, 0, 0, 0, 0 };
    vector<int> computerScore = { 0, 0, 0, 0, 0, 0 };

    // get value for both repetition vector
    // step through six-sides of dice
    for (int currentCheck = 1; currentCheck <= 6; currentCheck++) {

        // step throuh 5 dices
        for (int diceNo = 0; diceNo < 5; diceNo++) {

            // e.g: if dice #1 is 3 then the 3rd element in repetition vector increased
            if (playerDices[diceNo] == to_string(currentCheck)) {

                (playerScore[currentCheck - 1])++;
            }

            // same for computer's repetition vector
            if (computerDices[diceNo] == to_string(currentCheck)) {

                (computerScore[currentCheck - 1])++;
            }
        }
    }

    // determine combination for player
    // step through six-sides of dice
    for (int score = 0; score < 6; score++) {

        // Five of a kind
        if (playerScore[score] == 5) {

            playerHand.combinationName = "5 of a kind";

            // get combination value. Format is 5x
            playerHand.combinationValue = "5";
            playerHand.combinationValue += to_string(score + 1);


            // skip loop
            goto END;

        }// Four of a kind (format 4xy)
        else if (playerScore[score] == 4) {

            // get 4x
            playerHand.combinationName = "4 of a kind";
            playerHand.combinationValue = "4";
            playerHand.combinationValue += to_string(score + 1);

            // get y
            for (int inner = 0; inner < 6; inner++) {

                if (playerScore[inner] == 1) {

                    playerHand.combinationValue += to_string(inner + 1);

                }

            }
            // todo
            goto END;

        }// Full House or Three of a Kind 
        else if (playerScore[score] == 3) {

            for (int inner = 0; inner < 6; inner++) {

                // Full House (format: 32xyz)
                if (playerScore[inner] == 2) {

                    // get 32xy
                    playerHand.combinationName = "full house";
                    playerHand.combinationValue = "32";
                    playerHand.combinationValue += to_string(score + 1);
                    playerHand.combinationValue += to_string(inner + 1);

                    // get z
                    for (int mostInner = 0; mostInner < 6; mostInner++) {

                        if (playerScore[mostInner] == 1) {

                            playerHand.combinationValue += to_string(mostInner + 1);
                        }
                    }
                    goto END;
                }

            }

            // Three of a kind (format: 31xy)
            // get 31x
            playerHand.combinationName = "3 of a kind";
            playerHand.combinationValue = "31";
            playerHand.combinationValue += to_string(score + 1);

            // get y
            int sum = 0;
            for (int mostInner = 0; mostInner < 6; mostInner++) {

                if (playerScore[mostInner] == 1) {

                    sum += (mostInner + 1);
                }
            }
            playerHand.combinationValue += to_string(sum);
            goto END;

            // Two Pair or a Pair
        }
        else if (playerScore[score] == 2) {

            // step backward so that the higher value is proceeded first (from 6-dots to 1-dot)
            for (int inner = 5; (inner >= 0) && (inner != score); inner--) {

                // Two Pair (format: 22xyz)
                if (playerScore[inner] == 2) {

                    // get 22
                    playerHand.combinationName += "2 pair";
                    playerHand.combinationValue = "22";

                    // compare to get the highet rank out of two pairs
                    // or get xy
                    if (score > inner) {
                        playerHand.combinationValue += to_string(score + 1);
                        playerHand.combinationValue += to_string(inner + 1);
                    }
                    else {

                        playerHand.combinationValue += to_string(inner + 1);
                        playerHand.combinationValue += to_string(score + 1);
                    }

                    // get z
                    for (int mostInner = 0; mostInner < 6; mostInner++) {

                        if (playerScore[mostInner] == 1) {

                            playerHand.combinationValue += to_string(mostInner + 1);
                        }
                    }
                    goto END;
                }
            }

            // A Pair (format: 1xy)
            // get 1x
            playerHand.combinationName = "a fair";
            playerHand.combinationValue = "1";
            playerHand.combinationValue += to_string(score + 1);

            // get y
            int sum = 0;
            for (int mostInner = 0; mostInner < 6; mostInner++) {

                if (playerScore[mostInner] == 1) {

                    sum += (mostInner + 1);
                }
            }
            string middle = to_string(sum);
            if (middle.size() == 2) {
                middle[0] = '9';
            }
            playerHand.combinationValue += middle;

            goto END;

        }
    }
    // end of loop
END:;

    // nothing case (format 0x)
    if (playerHand.combinationValue == "") {

        playerHand.combinationName = "nothing";
        playerHand.combinationValue = "0";
        int sum = 0;

        for (int mostInner = 0; mostInner < 6; mostInner++) {

            if (playerScore[mostInner] == 1) {

                sum += (mostInner + 1);
            }
        }

        // get x
        playerHand.combinationValue += to_string(sum);
    }



    // determine combination for player, do the same thing
    // step through six-sides of dice
    for (int score = 0; score < 6; score++) {

        // Five of a kind (format 5x)
        if (computerScore[score] == 5) {

            computerHand.combinationName = "five of a kind";

            // get 5x
            computerHand.combinationValue = "5";
            computerHand.combinationValue += to_string(score + 1);

            // skip loop
            goto END2;

        }// Four of a kind (format 4xy)
        else if (computerScore[score] == 4) {

            // get 4x
            computerHand.combinationName = "4 of a kind";
            computerHand.combinationValue = "4";
            computerHand.combinationValue += to_string(score + 1);

            // get y
            for (int inner = 0; inner < 6; inner++) {

                if (computerScore[inner] == 1) {

                    computerHand.combinationValue += to_string(inner + 1);
                }
            }
            // todo, add inner loop
            goto END2;

        }// Full House or Three of a Kind 
        else if (computerScore[score] == 3) {

            for (int inner = 0; inner < 6; inner++) {

                // Full House 32xyz
                if (computerScore[inner] == 2) {

                    // get 32xy
                    computerHand.combinationName = "full house";
                    computerHand.combinationValue = "32";
                    computerHand.combinationValue += to_string(score + 1);
                    computerHand.combinationValue += to_string(inner + 1);

                    // get z
                    for (int mostInner = 0; mostInner < 6; mostInner++) {

                        if (computerScore[mostInner] == 1) {

                            computerHand.combinationValue += to_string(mostInner + 1);
                        }
                    }
                    goto END2;
                }

            }

            // Three of a kind 31xy
            // get 31x
            computerHand.combinationName = "3 of a kind";
            computerHand.combinationValue = "31";
            computerHand.combinationValue += to_string(score + 1);

            // get y
            int sum = 0;
            for (int mostInner = 0; mostInner < 6; mostInner++) {

                if (computerScore[mostInner] == 1) {

                    sum += (mostInner + 1);
                }
            }
            string middle = to_string(sum);
            if (middle.size() == 2) {
                middle[0] = '9';
            }

            computerHand.combinationValue += middle;

            goto END2;

            // Two Pair or a Pair
        }
        else if (computerScore[score] == 2) {

            // step backward so that the higher value is proceeded first (from 6-dots to 1-dot)
            for (int inner = 5; (inner >= 0) && (inner != score); inner--) {

                // Two Pair 22xyz
                if (computerScore[inner] == 2) {

                    computerHand.combinationName += "2 pair";
                    computerHand.combinationValue = "22";

                    // get 22xy
                    if (score > inner) {
                        computerHand.combinationValue += to_string(score + 1);
                        computerHand.combinationValue += to_string(inner + 1);
                    }
                    else {

                        computerHand.combinationValue += to_string(inner + 1);
                        computerHand.combinationValue += to_string(score + 1);
                    }

                    // get z
                    for (int mostInner = 0; mostInner < 6; mostInner++) {

                        if (computerScore[mostInner] == 1) {

                            computerHand.combinationValue += to_string(mostInner + 1);
                        }
                    }
                    goto END2;
                }
            }

            // A Pair (format: 1xy)
            // get 1x
            computerHand.combinationName = "a fair";
            computerHand.combinationValue = "1";
            computerHand.combinationValue += to_string(score + 1);
            int sum = 0;

            // get y
            for (int mostInner = 0; mostInner < 6; mostInner++) {

                if (computerScore[mostInner] == 1) {

                    sum += (mostInner + 1);
                }
            }
            string middle = to_string(sum);
            if (middle.size() == 2) {
                middle[0] = '9';
            }
            computerHand.combinationValue += middle;
            goto END2;
        }
    }
    // end of loop
END2:;

    // nothing case (0x)
    if (computerHand.combinationName == "") {

        computerHand.combinationName = "nothing";
        computerHand.combinationValue = "0";

        int sum = 0;
        for (int mostInner = 0; mostInner < 6; mostInner++) {

            if (computerScore[mostInner] == 1) {

                sum += (mostInner + 1);
            }
        }

        // get x
        computerHand.combinationValue += to_string(sum);
    }
}

// member function
void DiceGame::display() {

    // display computer 5 dices values
    cout << "\nComputer rolled: ";
    for (unsigned i = 0; i < computerDices.size(); i++) {

        cout << computerDices[i] << " ";
    }

    // display player 5 dices values
    cout << "\nYou rolled: ";
    for (unsigned i = 0; i < computerDices.size(); i++) {

        cout << playerDices[i] << " ";
    }
}

// Utility method: split command by space and push plitted words into vector
void DiceGame::refine(vector<string>& element, string input) {

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

// memberfunction: determine round winner
void DiceGame::getWinner() {

    if (computerHand.combinationValue > playerHand.combinationValue) {

        cout << "Computer wins.\n";
        moneyLost = bet;


    }
    else if (computerHand.combinationValue == playerHand.combinationValue) {

        cout << "It's a tie.\n";
        moneyLost = 0;

    }
    else {

        cout << "You win.\n";
        moneyLost = 0-bet;

    }
}

// input validation check
bool DiceGame::errorCheck() {

    if (playerDices.size() != 5 || computerDices.size() != 5) {
        return false;
    }

    for (int i = 0; i < 5; i++) {

        int num1 = stoi(playerDices[i]);
        int num2 = stoi(computerDices[i]);
        if (num1 < 0 || num1 > 6 || num2 < 0 || num2 > 6) {
            return false;
        }
    }
    return true;
}

int main() {

    // intro
    cout << "\n\tDice Game\n";

    // get player total money
    int balance;
    do {
        cout << "\nEnter your money to play: $";
        cin >> balance;
        if (balance > 0) {
            break;
        }
        else {
            cout << "\nAmount of money should be greater than 0\n";
        }
    } while (true);

    // save player initial money
    unsigned originalBL = balance;

    // get game mode from player
    char mode;
    do {
        cout << "\nDo you wish to play in (T)-Test or (G)-Game mode? ";
        cin.ignore();
        cin.get(mode);
        mode = toupper(mode);
        if (mode != 'T' && mode != 'G') {
            cout << "\nPlease enter a valid input.\n";
        }
        else {
            break;
        }
    } while (true);

    // runAgain flag
    char runAgain = 'N';

    // play loop
    do {

        // hold amount of bet for each round
        unsigned bet;

        // get bet and input validation
        do {

            cout << "\nEnter your bet: $";
            cin >> bet;

            if (bet <= balance) {
                break;
            }
            else {
                cout << "\nPlease enter a reasonable bet.\n";
            }
        
        } while (true);


        // construct game object from game mode
        DiceGame game(mode, bet);

        // only display rolled value in 'G' mode
        if (mode == 'G') {
            game.display();
            cout << endl;
        }

        // display Hand
        cout << endl;
        game.displayHand();

        // diplay winner
        cout << endl;
        game.getWinner();

        // display each round balance
        balance = balance - game.getMoneyLost();
        if (game.getMoneyLost() > 0) {
            cout << "\nYou just lost $" << game.getMoneyLost();
        }
        else {
            cout << "\nYou just win $" << 0 - game.getMoneyLost();
        }
        cout << ". Your new balance is: $" << balance << endl;

        if (balance == 0) {

            break;
        }

        // play again loop
        cout << "\nPlay again (Y/N)? ";
        cin >> runAgain;

    } while (runAgain == 'Y' || runAgain == 'y');

    // display summary
    if (balance == 0) {
        cout << "\nYou're Broke. Better Luck Next Time\n";
    }
    else {

        if (balance > originalBL) {
            cout << "\nCongratulation! You win $" << balance - originalBL << " today." << endl;
        }
        else {
            cout << "\nYou lost $" << originalBL - balance << " today." << endl;
        }
    }

}
