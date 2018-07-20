//**************************************************************
//              Find similar number of given non-negative integer
//**************************************************************

// Two non-negative integers N and M are said to be similar if their
// decimal representations can be obtained from each other by rearranging
// their digits. Note that a correct decimal representation does not 
// contain leading zeroes (except for number 0). For example:
// 1234 is similar to 2431.
// 1010 is similar to 1001.
// 12 is similar to 12.
// 123 is NOT similar to 234 (there are different sets of digits).
// 113 is NOT similar to 133 (there are different numbers of individual digits).
// 100 is NOT similar to 10 (010 contains a leading zero, so it is not a 
// correct decimal representation).
// given a non-negative integer N, returns the number of non-negative integers
// similar to N.

#include <algorithm>
#include <assert.h>
#include <vector>
#include <iostream>

using namespace std;

int FindSimilarNumber(int N)
{
    assert(N >= 0);
    int inputVal = N;

    // get all digits from input value.
    vector<int> digits;
    if (inputVal == 0)
    {
        digits.push_back(0);
    }
    else
    {
        while (N != 0)
        {
            digits.push_back(N % 10);
            N /= 10;
        }
    }

    for (auto val : digits)
    {
        cout << val << " ";
    }
    cout << endl;

    sort(digits.begin(), digits.end());

    vector<vector<int>> permutation;
    // find all permutation of digits.
    do
    {
        // exclude zero of first digit. or digits itself is 0.
        if (digits.front() != 0 || (digits.size() == 1 && digits.front() == 0))
        {
            permutation.push_back(digits);
        }
    }
    while (next_permutation(digits.begin(), digits.end()));

    // print similar numbers
    for (auto perm : permutation)
    {
        for (auto val : perm)
        {
            cout << val;
        }
        cout << endl;
    }

    int similarNum = permutation.size();
    cout << "similar number of " << inputVal << " is: " << similarNum << endl;

    return similarNum;
}

