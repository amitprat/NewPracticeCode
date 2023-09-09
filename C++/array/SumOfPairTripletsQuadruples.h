#pragma once
#include "../header.h"
using namespace std;

class SumOfPairTripletsQuadruples
{
public:
    static void test(vector<int> arr, int k)
    {
        SumOfPairTripletsQuadruples obj;

        cout << "Pair Sum:: ";
        auto res1 = obj.pairSumUsingMap(arr, k);
        cout << "Output: ";
        cout << res1.first << " " << res1.second << endl;

        cout << "Triplet Sum:: ";
        auto res2 = obj.tripletSumUsingMap(arr, k);
        cout << "Output: ";
        cout << get<0>(res2) << " " << get<1>(res2) << " " << get<2>(res2) << endl;

        cout << "Quadruple Sum:: ";
        auto res3 = obj.quadrupleSum(arr, k);
        cout << "Output: ";
        cout << get<0>(res3) << " " << get<1>(res3) << " " << get<2>(res3) << " " << get<3>(res3) << endl;
    }

    pair<int, int> pairSum(vector<int> v, int sum)
    {
        sort(v.begin(), v.end());
        int i = 0, j = v.size() - 1;
        while (i < j) {
            if (v[i] + v[j] == sum) return { v[i],v[j] };
            else if (v[i] + v[j] < sum) i++;
            else j--;
        }
    }

    pair<int, int> pairSumUsingMap(vector<int> v, int sum)
    {
        unordered_map<int, int> m;
        for (int i = 0; i < v.size(); i++) {
            int rsum = sum - v[i];
            if (m.find(rsum) == m.end()) {
                m[v[i]] = i;
            }
            else {
                auto j = m[rsum];
                if (i != j) {
                    return { v[i],v[j] };
                }
            }
        }
    }

    tuple<int, int, int> tripletSum(vector<int> v, int sum)
    {
        sort(v.begin(), v.end());
        for (int i = 0; i < v.size() - 1; i++) {
            int j = i + 1;
            int k = v.size() - 1;

            while (j < k) {
                if (v[i] + v[j] + v[k] == sum) return { v[i],v[j],v[k] };
                else if (v[i] + v[j] + v[k] < sum) j++;
                else k--;
            }
        }
    }

    tuple<int, int, int> tripletSumUsingMap(vector<int> v, int sum)
    {
        unordered_map<int, int> m;
        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                int tsum = v[i] + v[j];
                int rsum = sum - tsum;
                if (m.find(rsum) == m.end()) {
                    m[v[i]] = i;
                    m[v[j]] = j;
                }
                else {
                    auto k = m[rsum];
                    if (i != k && j != k) {
                        return { v[i],v[j],v[k] };
                    }
                }
            }
        }
    }

    tuple<int, int, int, int> quadrupleSum(vector<int> v, int sum)
    {
        unordered_map<int, pair<int, int>> pairSumMap;
        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                int tsum = v[i] + v[j];
                int rsum = sum - tsum;
                if (pairSumMap.find(rsum) == pairSumMap.end()) {
                    pairSumMap[tsum] = { i,j };
                }
                else {
                    auto vsum = pairSumMap[rsum];
                    if (vsum.first != i && vsum.second != i && vsum.first != j && vsum.second != j) {
                        return { v[i],v[j],v[vsum.first], v[vsum.second] };
                    }
                }
            }
        }
    }
};