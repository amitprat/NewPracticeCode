#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=6287528252407808

A k-palindrome is a string which transforms into a palindrome on removing at most k characters.

Given a string S, and an interger K, print "YES" if S is a k-palindrome; otherwise print "NO".
Constraints:
S has at most 20,000 characters.
0<=k<=30

Sample Test Case#1:
Input - abxa 1
Output - YES
Sample Test Case#2:
Input - abdxa 1
Output - No
*/

class KPalindromeString {
public:
    static void test() {
        KPalindromeString obj;

        {
            string input = "abxa";
            int k = 1;
            auto res = obj.isKPalindromeString(input, k);
            cout << format("Is string '{}' k-palindrome={}", input, res) << endl;
        }

        {
            string input = "abdxa";
            int k = 1;
            auto res = obj.isKPalindromeString(input, k);
            cout << format("Is string '{}' k-palindrome={}", input, res) << endl;
        }
    }

    bool isKPalindromeString(string str, int k) {
        bool res1 = isKPalindromeStringOriginal(str, k);
        bool res2 = isKPalindromeStringOptimized(str, k);

        assert(res1 == res2);

        return res1;
    }

    bool isKPalindromeStringOriginal(string str, int k) {
        int n = str.length();
        vector<vector<int>> table(n + 1, vector<int>(n + 1));
        string revstr = str;
        reverse(revstr.begin(), revstr.end());

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 && j == 0) table[i][j] = 0;
                else if (i == 0) table[i][j] = j; // insert
                else if (j == 0) table[i][j] = i; // delete
                else {
                    if (str[i - 1] == revstr[j - 1]) {
                        // char match
                        table[i][j] = table[i - 1][j - 1];
                    }
                    else {
                        // count difference, minimum of insert and delete
                        table[i][j] = 1 + min(table[i - 1][j], table[i][j - 1]);
                    }
                }
            }
        }

        int minDist = table[n][n];
        cout << format("Minimum distance={} and k={} for string={}", minDist, k, str) << endl;

        return minDist <= 2 * k;
    }

    bool isKPalindromeStringOptimized(string str, int k) {
        int n = str.length();
        vector<vector<int>> table(n + 1, vector<int>(n + 1, INT_MAX));
        string revstr = str;
        reverse(revstr.begin(), revstr.end());

        for (int i = 0; i <= n; i++) {
            int from = max(0, i - k);
            int to = min(n, i + k);
            for (int j = from; j <= to; j++) {
                if (i == 0 && j == 0) table[i][j] = 0;
                else if (i == 0) table[i][j] = j; // insert
                else if (j == 0) table[i][j] = i; // delete
                else {
                    if (str[i - 1] == revstr[j - 1]) {
                        // char match
                        table[i][j] = table[i - 1][j - 1];
                    }
                    else {
                        // count difference, minimum of insert and delete
                        table[i][j] = 1 + min(table[i - 1][j], table[i][j - 1]);
                    }
                }
            }
        }

        int minDist = table[n][n];
        cout << format("Minimum distance={} and k={} for string={}", minDist, k, str) << endl;

        return minDist <= 2 * k;
    }
};