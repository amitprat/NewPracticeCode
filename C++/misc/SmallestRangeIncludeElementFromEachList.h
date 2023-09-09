#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Minheap
{
private:
    vector<pair<int, int>> arr;
    int sz = 0;
    int left(int index) { return 2 * index + 1; }
    int right(int index) { return 2 * index + 2; }
    int parent(int index) { return index / 2; }

    void heapify(int index) {
        int l = left(index);
        int r = right(index);
        auto item = arr[index];
        int smallest = index;

        if (l < sz && arr[l].first < item.first) smallest = l;
        if (r < sz && arr[r].first < item.first) smallest = r;
        if (smallest != index) {
            swap(arr[smallest], arr[index]);
            heapify(smallest);
        }
    }
public:
    void insert(pair<int, int> e)
    {
        arr.push_back(e); sz++;
        heapify(0);
    }

    pair<int, int> pop()
    {
        auto item = arr[0];
        arr[0] = arr[sz - 1];
        sz--;
        arr.pop_back();

        heapify(0);

        return item;
    }
};

class SmallestRange
{
public:
    static void test(vector<vector<int>> input)
    {
        SmallestRange obj;
        pair<int, int> res = obj.findRange(input);
        cout << res.first << ", " << res.second << endl;
    }

    pair<int, int> findRange(vector<vector<int>> input)
    {
        Minheap heap;
        pair<int, int> range = { INT_MAX, INT_MIN };
        vector<int> indices;

        for (int index = 0; index < input.size(); index++) {
            heap.insert({ input[index][0], index });
            indices.push_back(0);
        }
        range = UpdateRange(input, indices);

        while (true) {
            auto elem = heap.pop();
            int arrIdx = elem.second;
            indices[arrIdx]++;
            if (indices[arrIdx] >= input[arrIdx].size()) break;
            else {
                int e = input[arrIdx][indices[arrIdx]];
                heap.insert({ e, arrIdx });
                range = UpdateRange(input, indices);
            }
        }

        return range;
    }

    pair<int, int> UpdateRange(vector<vector<int>> input, vector<int> indices)
    {
        int mn = INT_MAX, mx = INT_MIN;
        for (int j = 0; j < input.size(); j++) {
            if (input[j][indices[j]] < mn) mn = input[j][indices[j]];
            if (input[j][indices[j]] > mx) mx = input[j][indices[j]];
        }

        return { mn, mx };
    }
};