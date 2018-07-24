#include <string>
#include <vector>
#include <iostream>

using namespace std;

string ZigZagConvert(string str, int numRows)
{
    int length = str.size();

    vector<string> vec(numRows, string());

    // for each character in str, put it in the right string rows.
    for (int i = 0; i < length; i++)
    {
        int mod = i % numRows;
        vec[mod].push_back(str[i]);
        vec[numRows - mod + 1].push_back(str[i]);
    }

    string convertedStr;
    for (auto v : vec)
        convertedStr += v;

    return convertedStr;
}

void LC6_ZigZag_Conversion_Test()
{
    // EX1:
    // Input: s = "PAYPALISHIRING", numRows = 3
    // Output : "PAHNAPLSIIGYIR"
    // Explanation :
    // P   A   H   N
    // A P L S I I G
    // Y   I   R
    //
    // EX2:
    // Input : s = "PAYPALISHIRING", numRows = 4
    // Output : "PINALSIGYAHRPI"
    // Explanation :
    // P     I    N
    // A   L S  I G
    // Y A   H R
    // P     I

    string str = "PAYPALISHIRING";
    cout << ZigZagConvert(str, 3) << endl;
    cout << ZigZagConvert(str, 4) << endl;
}

