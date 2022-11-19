/*
Author: Mai Tran
Course: COSC 1437
Extra Credit Final Exam Spring 2022
Reference: NONE
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {

	char runAgain = 'N';
	do {

		// hold total number in the list
		int totalNum;
		cout << "\nEnter size of the list: ";
		cin >> totalNum;

		// hold sum of square
		double sumSquare = 0;
		
		// temp storage varibal
		double temp;

		// accumualte sum square
		for (int i = 0; i < totalNum; i++) {
			cout << "\nEnter number #" << i + 1 << ": ";
			cin >> temp;

			// accumulate temp square to sum
			sumSquare += pow(temp, 2);
		}

		// display value
		cout << "\nValue: " << setprecision(3) << fixed << sqrt(sumSquare / totalNum) << endl;

		// run again branch
		cout << "\nRun Again (Y/N)?";
		cin >> runAgain;
	} while (runAgain == 'y' || runAgain == 'Y');

	return 0;
}