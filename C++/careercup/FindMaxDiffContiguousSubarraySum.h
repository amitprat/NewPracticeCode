#include "../Header.h"

/*
https://www.careercup.com/question?id=19286747

Given an array of integers. Find two disjoint contiguous sub-arrays such that the absolute difference between the sum of
 two sub-array is maximum.
* The sub-arrays should not overlap.

eg- [2 -1 -2 1 -4 2 8] ans - (-1 -2 1 -4) (2 8), diff = 16

I gave him o(n^2) algorithm but he was not satisfied.
*/

/*
An O(n) solution is possible.

We consider all "split points", i.e. points such that one subarray lies to the left of it, and one to the right, and compute the best for each possible split point.

Dynamic programming works.

Given Array A[1,...n]

Using the standard dynamic programming algorithm, we can compute for a given i, the maximum and minimum sum subarrays in A[1...i] and A[i+1 ... n]. Note that the point between i and i+1 is a split point.

This can be done by making two passes once from 1 to n, and other from n to 1 and give us four arrays with the max and min sub-array sums.

Now given the above four arrays, for split point between i and i+1, we can take the max and min combinations (max from right, min from left and max from left, min from left), and get the combination which gives the better result.

Once we have the max for each split point, we get the global optimum.

O(n) time, O(n) space.
*/