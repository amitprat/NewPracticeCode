#pragma once
#include "../header.h"
using namespace std;

class SortArrByGivenIndices
{
    static void test()
    {
        SortArrByGivenIndices obj;
        vector<int> a = {};
        vector<int> order = {};
        obj.sortArray(a, order);

        cout << "Sorted Array: ";
        for (auto i : a) cout << i << " ";
        cout << endl;
    }

    void sortArray(vector<int>& a, vector<int> order)
    {
        sort(a.begin(), a.end(), [order]() {});
    }
};