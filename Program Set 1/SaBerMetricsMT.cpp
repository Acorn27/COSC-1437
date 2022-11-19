/*
Author: Mai Tran
Course: COSC 2436
Program set 1
Reference: I get help on StackOverflow for the following task:
 How to convert int to double from this website
 https://stackoverflow.com/questions/10438249/in-c-what-are-the-differences-between-static-castdoublea-and-doublea
 I use an algorith static_cast<int>(number + 0.5) to round double to int but i don't remember the address of the page

*/

#include <iostream>
#include <cmath>
using namespace std;


int main() {

    char repeat = 'N';	// flag for multiple times runs

    int h,  	// number of hits
        w,  	// number of walks
        hbp,	// number of times hit by pitch
        hr, 	// number of home runs
        iw, 	// number of intentional walks
        tb, 	// total number of bases
        sb, 	// number of stolen bases
        cs, 	// number of times caught stealing
        gdp,	// number of times ground into a double play
        ab; 	// number of at bats

    int pr, 	// predicted runs
        ar; 	// actually number of runs


    do {
        // get datas from user   	 
        cout << "\nNumber of hits (H): ";
        cin >> h;
        cout << "Number of walks (W): ";
        cin >> w;
        cout << "Number of times hit by pitch (HBP): ";
        cin >> hbp;
        cout << "Number of home runs (HR): ";
        cin >> hr;
        cout << "Number of intentional walks (IW): ";
        cin >> iw;
        cout << "Total number of bases (TB): ";
        cin >> tb;
        cout << "Number of stolen bases (SB): ";
        cin >> sb;
        cout << "Number of times caught stealing (CS): ";
        cin >> cs;
        cout << "Number of times ground into a double play (GDP): ";
        cin >> gdp;
        cout << "Number of at bats (AB): ";
        cin >> ab;
        cout << "Actual runs scored (AR): ";
        cin >> ar;


        // calculate predicted runs
        double a = static_cast<double>(h) + w + hbp - hr - .5 * iw;

        double b = (1.4 * tb - .6 * h - 3 * static_cast<double>(hr) + .1 * (static_cast<double>(w) + hbp - iw) + .9 * (static_cast<double>(sb) - cs - gdp)) * 1.1;

        double c = static_cast<double>(ab) - h + cs + gdp;

        double d = hr;

        // calculate and round predicted runs
        pr = static_cast<int>((a * b / (b + c) + d) + 0.5);

        // display predicted number of runs
        cout << "\nNumber of Runs: " << pr;

        // lucky or not decision?
        // because pr and ar are both integer, ar > pr also mean ar is greater more than 1 than pr and vice versa
        if (ar > pr) {
            cout << "- LUCKY" << endl;
        }
        else if (ar < pr) {
            cout << "- UNLUCKY" << endl;
        }
        // this also mean ar == pr
        else {
            cout << "- VALID" << endl;
        }

        // repeat or not ?
        cout << "\nRun again (Y/N): ";
        cin >> repeat;

        // elimite '\n' in keyboard buffering
        cin.ignore();

    } while (repeat == 'Y' || repeat == 'y');

}





