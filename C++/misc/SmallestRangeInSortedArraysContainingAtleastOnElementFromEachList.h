#pragma once
#include "../Header.h"
using namespace std;

class SmallestRangeInSortedArraysContainingAtleastOnElementFromEachList
{
    class Minheap
    {
    private:
        vector<pair<int, int>> arr;
        int sz = 0;
        int left(int index) { return 2 * index + 1; }
        int right(int index) { return 2 * index + 2; }
        int parent(int index) { return (index - 1) / 2; }

        void heapify(int index) {
            int smallest = index;
            int l = left(index);
            int r = right(index);

            auto item = arr[index];
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

public:
    static void test()
    {
        SmallestRangeInSortedArraysContainingAtleastOnElementFromEachList obj;
        vector<vector<int>> input = {
            {4, 7, 9, 12, 15},
            {0, 8, 10, 14, 20},
            {6, 12, 16, 30, 50}
        };

        pair<int, int> res1 = obj.findRange(input);
        pair<int, int> res2 = obj.findRangeUsingSTL(input);
        pair<int, int> res3 = obj.findRangeUsingSTLOptimized(input);
        assert(res1 == res2);
        assert(res1 == res3);

        cout << format("Smallest range convering atleast one element from each list: {}", to_string(res1)) << endl;

        input = {
            {4, 7},
            {1,2},
            {20, 40}
        };

        res1 = obj.findRange(input);
        res2 = obj.findRangeUsingSTL(input);
        res3 = obj.findRangeUsingSTLOptimized(input);
        assert(res1 == res2);
        assert(res1 == res3);

        cout << format("Smallest range convering atleast one element from each list: {}", to_string(res1)) << endl;
    }

    pair<int, int> findRange(vector<vector<int>>& input)
    {
        Minheap heap;
        pair<int, int> range = { INT_MAX, INT_MIN };
        vector<int> indices;

        // insert first element of each array
        for (int index = 0; index < input.size(); index++) {
            if (input[index].empty()) return range; // if any of array is empty, no point of moving forward

            heap.insert({ input[index][0], index });
            indices.push_back(0);
        }

        while (true) {
            auto newRange = getRange(input, indices);

            if (range.first == INT_MAX || newRange.second - newRange.first < range.second - range.first) {
                range = newRange;
            }

            auto elem = heap.pop();
            int arrIdx = elem.second;

            // consider new element
            indices[arrIdx]++;

            if (indices[arrIdx] >= input[arrIdx].size()) break; // if any of array gets empty, no point of moving forward
            else {
                int next = input[arrIdx][indices[arrIdx]];
                heap.insert({ next, arrIdx });
            }
        }

        return range;
    }

    pair<int, int> findRangeUsingSTL(vector<vector<int>>& input)
    {
        using P = pair<int, int>;
        priority_queue<P, vector<P>, greater<P>> minHeap;
        pair<int, int> range = { INT_MAX, INT_MIN };
        vector<int> indices;

        // insert first element of each array
        for (int index = 0; index < input.size(); index++) {
            if (input[index].empty()) return range; // if any of array is empty, no point of moving forward

            minHeap.push({ input[index][0], index });
            indices.push_back(0);
        }

        while (true) {
            auto elem = minHeap.top(); minHeap.pop();
            int arrIdx = elem.second;

            auto newRange = getRange(input, indices);

            if (range.first == INT_MAX || newRange.second - newRange.first < range.second - range.first) {
                range = newRange;
            }

            indices[arrIdx]++; // consider next element

            if (indices[arrIdx] >= input[arrIdx].size()) break; // if any of array gets empty, no point of moving forward
            else {
                int next = input[arrIdx][indices[arrIdx]];
                minHeap.push({ next, arrIdx });
            }
        }

        return range;
    }

    pair<int, int> findRangeUsingSTLOptimized(vector<vector<int>>& arrs) {
        using  p = pair<int, pair<int, int>>;
        using v = vector<pair<int, pair<int, int>>>;
        priority_queue<p, v, std::greater<p>> pq;

        int mn = INT_MAX, mx = INT_MIN;

        for (int i = 0; i < arrs.size(); i++) {
            pq.push({ arrs[i][0], {i,0} });
            mn = min(mn, arrs[i][0]);
            mx = max(mx, arrs[i][0]);
        }

        pair<int, int> result = { mn, mx };

        while (true) {
            auto f = pq.top(); pq.pop();
            mn = f.first; // this is smallest element of range

            if (mx - mn < result.second - result.first) {
                result = { mn, mx };
            }

            int arrIdx = f.second.first;
            int arrPos = f.second.second;
            if (arrPos + 1 < arrs[arrIdx].size()) {
                arrPos++;
                pq.push({ arrs[arrIdx][arrPos], {arrIdx, arrPos} });

                mx = max(arrs[arrIdx][arrPos], mx); // keep updating mx value always
            }
            else {
                // if any of the arrays end, exist it.
                break;
            }
        }

        return result;
    }

    pair<int, int> getRange(vector<vector<int>>& input, vector<int>& indices)
    {
        int mn = INT_MAX, mx = INT_MIN;
        for (int j = 0; j < input.size(); j++) {
            if (input[j][indices[j]] < mn) mn = input[j][indices[j]];
            if (input[j][indices[j]] > mx) mx = input[j][indices[j]];
        }

        return { mn, mx };
    }
};