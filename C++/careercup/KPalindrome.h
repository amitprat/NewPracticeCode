#include "../Header.h"

/*
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

/*
The question asks if we can transform the given string S into its reverse deleting at most K letters.
We could modify the traditional Edit-Distance algorithm, considering only deletions, and check if this edit distance is <= K. There is a problem though. S can have length = 20,000 and the Edit-Distance algorithm takes O(N^2). Which is too slow.

(From here on, I'll assume you're familiar with the Edit-Distance algorithm and its DP matrix)

However, we can take advantage of K. We are only interested *if* manage to delete K letters. This means that any position more than K positions away from the main diagonal is useless because its edit distance must exceed those K deletions.

Since we are comparing the string with its reverse, we will do at most K deletions and K insertions (to make them equal). Thus, we need to check if the ModifiedEditDistance is <= 2*K
Here's the code:
*/

int ModifiedEditDistance(const string &a, const string &b, int k)
{
    int i, j, n = a.size();
    // for simplicity. we should use only a window of size 2*k+1 or
    // dp[2][MAX] and alternate rows. only need row i-1
    int dp[MAX][MAX];
    memset(dp, 0x3f, sizeof dp); // init dp matrix to a value > 1.000.000.000
    for (i = 0; i < n; i++)
        dp[i][0] = dp[0][i] = i;

    for (i = 1; i <= n; i++)
    {
        int from = max(1, i - k), to = min(i + k, n);
        for (j = from; j <= to; j++)
        {
            if (a[i - 1] == b[j - 1]) // same character
                dp[i][j] = dp[i - 1][j - 1];
            // note that we don't allow letter substitutions

            dp[i][j] = min(dp[i][j], 1 + dp[i][j - 1]); // delete character j
            dp[i][j] = min(dp[i][j], 1 + dp[i - 1][j]); // insert character i
        }
    }
    return dp[n][n];
}
cout << ModifiedEditDistance("abxa", "axba", 1) << endl;           // 2 <= 2*1 - YES
cout << ModifiedEditDistance("abdxa", "axdba", 1) << endl;         // 4 > 2*1 - NO
cout << ModifiedEditDistance("abaxbabax", "xababxaba", 2) << endl; // 4 <= 2*2 - YES