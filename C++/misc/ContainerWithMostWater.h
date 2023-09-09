#pragma once
#include "../header.h"

class ContainerWithMostWater {
public:
    static void test() {
        ContainerWithMostWater obj;
        vector<int> input = { 1,2,4,2,3,2,5,2 };
        cout << obj.mostWater(input) << endl;
    }

    int mostWater(vector<int>& input) {
        int left = 0, right = input.size() - 1;
        int mxArea = 0;
        tuple<int, int, int> position;
        while (left <= right) {
            int height = min(input[left], input[right]);
            int width = right - left;
            int curArea = height * width;
            if (curArea > mxArea) {
                mxArea = curArea;
                position = { left, right, height };
            }

            // move pointers
            if (input[left] < input[right]) left++;
            else right--;
        }
        cout << "Position = (" << std::get<1>(position) << "-" << std::get<0>(position) << ")*" << std::get<2>(position) << endl;
        return mxArea;
    }
};