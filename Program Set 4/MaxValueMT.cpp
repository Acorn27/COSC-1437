/*
Author: Mai Tran
Course: COSC 1437
Prgram Set 4- EC
Reference: A part of my code is from this website: https://www.geeksforgeeks.org/minimum-maximum-values-expression/
*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

// Utility method to check whether a character
// is operator or not
bool isOperator(char op)
{
    return (op == '+' || op == '*');
}

// method return maximum value obtainable from an expression
int returnMax(string exp)
{
    vector<int> num;
    vector<char> opr;
    string tmp = "";

    //  store operator and numbers in different vectors
    for (unsigned i = 0; i < exp.length(); i++)
    {
        if (isOperator(exp[i]))
        {
            opr.push_back(exp[i]);
            num.push_back(atoi(tmp.c_str()));
            tmp = "";
        }
        else
        {
            tmp += exp[i];
        }
    }

    //  storing last number in vector
    num.push_back(atoi(tmp.c_str()));

    int len = num.size();

    vector<vector<int> > maxVal;
    for (int i = 0; i < len; i++) {
        vector<int> temp;
        for (int j = 0; j < len; j++) {

            temp.push_back(0);
        }
        maxVal.push_back(temp);
    }

    //  initializing maxVal 2D array
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (i == j) {
                maxVal[i][j] = num[i];
            }
        }
    }

    // looping similar to matrix chain multiplication and updating 2D maximum array
    for (int L = 2; L <= len; L++)
    {
        for (int i = 0; i < len - L + 1; i++)
        {
            int j = i + L - 1;
            for (int k = i; k < j; k++)
            {
                int maxTmp = 0;

                // if current operator is '+', updating tmp
                // variable by addition
                if (opr[k] == '+')
                {
                    maxTmp = maxVal[i][k] + maxVal[k + 1][j];
                }

                // if current operator is '*', updating tmp
                // variable by multiplication
                else if (opr[k] == '*')
                {
                    maxTmp = maxVal[i][k] * maxVal[k + 1][j];
                }

                //  updating array values by tmp variables
                if (maxTmp > maxVal[i][j])
                    maxVal[i][j] = maxTmp;
            }
        }
    }

    //  last element of first row will store the result
    return (maxVal[0][len - 1]);
}

// convert int to binary, used to manipulated all combination of '+' and '*'
string toBinary(int n)
{
    string r;
    while (n != 0) {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    return r;
}

int main()
{
    // get user's input
    string value;
    cout << "Enter the integer value: ";
    getline(cin, value);

    // total number of operator can be inserted
    unsigned operatorCount = value.size() / 2;

    // total number of operator combination
    unsigned maxCombination = int(pow(2, operatorCount));

    // spartial fill array to hold all posisble expression
    string expression[100];

    // initialize expression with input expression
    for (unsigned i = 0; i < maxCombination; i++) {
        expression[i] = value;
    }

    // create all possible expression
    for (unsigned i = 0; i < maxCombination; i++) {

        // temp string to binary string
        string temp = toBinary(i);

        // add leading 'O' to binary string 
        while (temp.size() < operatorCount) {
            temp = '0' + temp;
        }

        // manipulate binary string to create expression with '+' and '*'
        for (unsigned k = 0; k < temp.size(); k++) {

            if (temp[k] == '0') {
                expression[i][2 * k + 1] = '+';
            }
            else {
                expression[i][2 * k + 1] = '*';;
            }
        }
    }

    // hold maximum value, initialize to maximum value of the first expression
    int maxOutput = returnMax(expression[0]);

    // calulate and compare maximum value of the remaining expression
    for (unsigned i = 1; i < maxCombination; i++) {

        /// Maximum value of current expression
        int temp = returnMax(expression[i]);

        // compare with maxOutput
        if (temp > maxOutput) {

            maxOutput = temp;

        }

    }

    // display output
    cout << "\nMaximum value: " << maxOutput << endl;

    return 0;
}