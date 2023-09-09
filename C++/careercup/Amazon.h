#pragma once
#include "../Header.h"

class AmazonProblems {
public:
    /*
    * https://www.careercup.com/question?id=22809662
        A tree, (NOT NECESSARILY BINARY), has nodes numbered 0 to N-1. An array has indices ranging from 0 to N-1. The indices denote the node ids and values denote the ids of parents. A value of -1 at some index k denotes that node with id k is the root. For ex:


        3 3 3 -1 2
        0 1 2 3 4
        In the above, nodes with ids 0, 1 & 2 have 3 as parent. 3 is the root as its parent = -1 and 2 is the parent of node id 4.

        Given such an array, find the height of the tree.
    */
    static int findTreeHeight() {
        vector<int> nodes = { 3, 3, 3, -1, 2 };

        int h1 = findTreeHeight(nodes, -1);
        int h2 = countDepth(nodes);

        assert(h1 == h2);

        return h1;
    }

    /*
    * https://www.careercup.com/question?id=5106425965576192
        You are given with an array of 1s and 0s. And you are given with an integer m, which signifies number of flips allowed.

        find the position of zeros which when flipped will produce maximum continuous series of 1s.

        e.g.
        input:
        arr={1 1 0 1 1 0 0 1 1 1 } m=1
        output={1 1 1 1 1 0 0 1 1 1} position=2

        arr={1 1 0 1 1 0 0 1 1 1 } m=2
        output={1 1 0 1 1 1 1 1 1 1} position=5,6

        I would use SLIDING WINDOW for this problem. (Just realized that I have used it at least 3 times at careercup!)

        Lets use a window covering from index wL to index wR. Let the number of zeros inside the window be nZero. We try to maintain the window with at most m zeros inside.

        The main steps are:
        - While nZero is no more than m: expand the window to the right (wR++) and update the count nZero;
        - While nZero exceeds m, shrink the window from left (wL++), update nZero;
        - Update the widest window along the way. The positions of must-flip zeros are inside the best window.

        This solution assumes we can use m or less number of flips.
        Time complexity = O(n), space = O(1).
    */
    static int maxWindow() {
        vector<int> arr = { 1, 1, 0, 1, 1, 0, 0, 1, 1, 1 };
        int m = 2;

        return maxWindow(arr, m);
    }

private:
    static int findTreeHeight(vector<int>& nodes, int parent) {
        int mxDepth = 0;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] == parent) {
                int depth = 1 + findTreeHeight(nodes, i);
                mxDepth = max(mxDepth, depth);
            }
        }

        return mxDepth;
    }

    static int countDepth(vector<int>& nodes) {
        vector<int> height(nodes.size(), -1);

        int mxHeight = -1;
        for (int i = 0; i < nodes.size(); i++) {
            if (height[i] == -1) {
                mxHeight = max(mxHeight, countDepth(i, nodes, height));
            }
        }

        return mxHeight;
    }

    static int countDepth(int parent, vector<int>& nodes, vector<int>& height) {
        if (height[parent] != -1) return height[parent];

        if (nodes[parent] == -1) {
            height[parent] = 1;
        }
        else {
            height[parent] = 1 + countDepth(nodes[parent], nodes, height);
        }

        return height[parent];
    }

    static int maxWindow(vector<int>& arr, int m) {
        int mxLength = 0;
        int l = 0, r = 0;
        int zeros = 0;
        pair<int, int> window = { -1,-1 };

        while (r < arr.size()) {
            if (zeros <= m) {
                if (arr[r] == 0) zeros++;
                r++;
            }
            else {
                if (arr[l] == 0) zeros--;
                l++;
            }

            if (r - l + 1 >= mxLength) {
                mxLength = r - l + 1;
                window = { l, r };
            }
        }

        cout << "Window: " << to_string(window) << endl;

        return mxLength;
    }
};