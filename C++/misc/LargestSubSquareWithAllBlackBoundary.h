#include "../header.h"

/* Cracking the coding interview
20.11 Imagine you have a square matrix, where each cell is filled with either black or white. Design an algorithm to find the maximum subsquare such that all four borders are filled with black pixels.
Assumption: Square is of size NxN.
This algorithm does the following:
1. Iterate through every (full) column from left to right.
2. At each (full) column (call this currentColumn), look at the subcolumns (from biggest to smallest).
3. At each subcolumn, see if you can form a square with the subcolumn as the left side. If so, update currentMaxSize and go to the next (full) column.
4. If N - currentColumn <= currentMaxSize, then break completely. We’ve found the largest square possible. Why? At each column, we’re trying to create a square with that column as the left side. The largest such square we could possibly create is N - currentColumn. Thus, if N-currentColumn <= currentMaxSize, then we have no need to proceed.
Time complexity: O(N^2).
*/

class LargestSubSquareWithAllBlackBoundary {
    struct Square {
        int r;
        int sz;
        Square(int r = 0, int sz = 0) : r(r), sz(sz) {}
    };

   public:
    static void test() {
        vector<vector<bool>> matrix = {{1, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}, {1, 0, 1, 1}};
        Sqaure square = findLargestSubsquare(arr);
        cout << square.sz << endl;
    }

   private:
    subsq findLargestSubsquare(vector<vector<bool>>& matrix) {
        int maxSz = 0;
        int col = 0;
        Square sq;
        while (N - col > maxSz) {
            for (int row = 0; row < N; row++) {
                int size = N - max(row, col);
                while (size > maxSz) {
                    if (isSquare(arr, row, col, size)) {
                        maxSz = size;
                        sq = Sqaure(row, size);
                        break;
                    }
                    size--;
                }
            }
            col++;
        }

        return sq;
    }

    bool isSquare(bool arr[][N], int r, int c, int sz) {
        for (int i = r; i < r + sz; i++) {
            if (!arr[i][c] || !arr[i][c + sz - 1])
                return false;
        }
        for (int i = c; i < c + sz; i++) {
            if (!arr[r][i] || !arr[r + sz - 1][i])
                return false;
        }

        return true;
    }
};