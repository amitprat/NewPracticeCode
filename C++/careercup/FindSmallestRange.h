#pragma once
#include "../Header.h"

class FindSmallestRange
{
public:
    static void test() {
        vector<int> arr1 = { 4, 10, 15, 24, 26 };
        vector<int> arr2 = { 0, 9, 12, 20 };
        vector<int> arr3 = { 5, 18, 22, 30 };

        auto res = findSmallestRange(arr1, arr2, arr3);
        cout << to_string(res) << endl;
    }

    static vector<int> findSmallestRange(vector<vector<int>> arrs)
    {
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        int mx = INT_MIN;
        for (int i = 0; i < arrs.size(); i++)
        {
            pq.push({ arrs[i][0],{i,0} });
            mx = max(mx, arrs[i][0]);
        }

        vector<int> result;
        int smallestRange = INT_MAX;

        while (!pq.empty())
        {
            auto cur = pq.top(); pq.pop();
            if (mx - cur.first < smallestRange) {
                result = { cur.first, mx };
                smallestRange = mx - cur.first;
            }
            if (arrs[cur.second.first].size() <= cur.second.second + 1) break;
            pq.push({ arrs[cur.second.first][cur.second.second + 1],{cur.second.first,cur.second.second + 1} });
            mx = max(mx, arrs[cur.second.first][cur.second.second + 1]);
        }

        return result;
    }

    static vector<int> findSmallestRange(vector<int> arr1, vector<int> arr2, vector<int> arr3)
    {
        vector<int> indices(arr1.size(), 0);
        vector<int> result;
        int smallestRange = INT_MAX;

        while (true)
        {
            auto minMax = getMinMax(arr1, arr2, arr3, indices);
            if (minMax.first.second - minMax.first.first < smallestRange)
            {
                smallestRange = minMax.first.second - minMax.first.first;
                result = { minMax.first.first,minMax.first.second };
            }

            if (!minMax.second) break;
        }

        return result;
    }

    static pair<pair<int, int>, bool> getMinMax(vector<int> arr1, vector<int> arr2, vector<int> arr3, vector<int>& indices)
    {
        bool moveNext = true;
        int mn = min(arr1[indices[0]], min(arr2[indices[1]], arr3[indices[2]]));
        int mx = max(arr1[indices[0]], max(arr2[indices[1]], arr3[indices[2]]));
        if (mn == arr1[indices[0]]) {
            indices[0]++;
            moveNext = indices[0] < arr1.size();
        }
        else if (mn == arr2[indices[1]]) {
            indices[1]++;
            moveNext = indices[1] < arr2.size();
        }
        else {
            indices[2]++;
            moveNext = indices[2] < arr3.size();
        }

        return { {mn, mx},moveNext };
    }
};