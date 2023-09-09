#pragma once
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <unordered_set>
#include <cassert>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

class LongestCommonSeq
{
public:
    static void test()
    {
        LongestCommonSeq lis;
        vector < pair<string, string>> contexts =
        { {"AGGTAB","GXTXAYB"}
        };
        for (auto context : contexts)
        {
            cout << "Input:" << context.first << ", " << context.second << endl;
            auto res = lis.longestCommonSeqDP(context.first, context.second, context.first.size(), context.second.size());
            cout << "Result:" << res << endl;
        }
    }

    int longestCommonSeq(string f, string s, int n, int m)
    {
        if (n < 0 || m < 0) return 0;
        if (f[n] != s[m]) return max(longestCommonSeq(f, s, n - 1, m), longestCommonSeq(f, s, n, m - 1));
        return 1 + longestCommonSeq(f, s, n - 1, m - 1);
    }

    int longestCommonSeqDP(string f, string s, int n, int m)
    {
        int** table = new int* [n + 1];
        for (int i = 0; i <= n; i++) table[i] = new int[m + 1];

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 || j == 0) table[i][j] = 0;
                else {
                    if (f[i - 1] == s[j - 1]) table[i][j] = 1 + table[i - 1][j - 1];
                    else {
                        table[i][j] = max(table[i][j - 1], table[i - 1][j]);
                    }
                }
            }
        }

        return table[n][m];
    }
};