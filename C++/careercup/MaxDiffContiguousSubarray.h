#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=19286747
*
* Given an array of integers. Find two disjoint contiguous sub-arrays such that the absolute difference between the sum of two sub-array is maximum.
* The sub-arrays should not overlap.

eg- [2 -1 -2 1 -4 2 8] ans - (-1 -2 1 -4) (2 8), diff = 16

I gave him o(n^2) algorithm but he was not satisfied.

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
class MaxDiffContiguousSubarray
{
public:
    static void test()
    {
        vector<int> arr = { 2, -1, -2, 1, -4, 2, 8 };
        auto result = getMaxDiffSubarray(arr);

        cout << "Max diff sum: " << result << endl;
    }

    static int getMaxDiffSubarray(vector<int> arr)
    {
        long a[10000];
        long b[10000];
        long max1[10000];
        long min1[10000];
        long max2[10000];
        long min2[10000];
        int n = arr.size();

        int i = 0;
        for (auto e : arr)
        {
            a[i] = e;
            b[i] = -a[i];
            i++;
        }

        long maxsofar = a[0], maxendinghere = a[0]; max1[0] = a[0];
        for (i = 1; i < n; i++)
        {
            maxendinghere = maxendinghere + a[i];
            maxendinghere = maxendinghere > a[i] ? maxendinghere : a[i];
            maxsofar = maxsofar > maxendinghere ? maxsofar : maxendinghere;
            max1[i] = maxsofar;
        }

        max2[n - 1] = maxendinghere = maxsofar = a[n - 1];
        for (i = n - 2; i >= 0; i--)
        {
            maxendinghere = maxendinghere + a[i];
            maxendinghere = maxendinghere > a[i] ? maxendinghere : a[i];
            maxsofar = maxsofar > maxendinghere ? maxsofar : maxendinghere;
            max2[i] = maxsofar;
        }

        maxendinghere = maxsofar = b[0];
        min1[0] = -b[0];
        for (i = 1; i < n; i++)
        {
            maxendinghere = maxendinghere + b[i];
            maxendinghere = maxendinghere > b[i] ? maxendinghere : b[i];
            maxsofar = maxsofar > maxendinghere ? maxsofar : maxendinghere;
            min1[i] = -maxsofar;
        }

        maxendinghere = maxsofar = b[n - 1];
        min2[n - 1] = -b[n - 1];
        for (i = n - 2; i >= 0; i--)
        {
            maxendinghere = maxendinghere + b[i];
            maxendinghere = maxendinghere > b[i] ? maxendinghere : b[i];
            maxsofar = maxsofar > maxendinghere ? maxsofar : maxendinghere;
            min2[i] = -maxsofar;
        }

        long globalmax = 0;
        for (i = 1; i < n; i++)
        {
            long m1 = abs(max1[i - 1] - min2[i]);
            long m2 = abs(max2[i] - min1[i - 1]);
            globalmax = max(globalmax, max(m1, m2));
        }

        return globalmax;
    }
};