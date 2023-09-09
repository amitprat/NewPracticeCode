#pragma once
#include "../header.h"

class LongestSubstrWithKUniqueChars
{
public:
    static void test() {
        LongestSubstrWithKUniqueChars obj;
        string str = "abcbbbbcccbdddadacb";
        vector<pair<pair<string, int>, string>> tests{
            {{"",2},""},
            {{"a",1},"a"},
            {{"ab",1},"a"},
            {{"ab",2},"ab"},
            {{"aaaaaaab",2},"aaaaaaab"},
            {{"abbbbbbb",2},"abbbbbbb"},
            {{"caaaaaaab",2},"caaaaaaa"},
            {{"caaaaaaab",1},"aaaaaaa"},
            {{"abcbbbbcccbdddadacb",3},"bcbbbbcccbddd"},
            {{"abcbbbbcccbcbaadacb",3},"abcbbbbcccbcbaa"},
            {{"abcbbbbcccbdddadacb",1},"bbbb"},
            {{"abcbbbbcccbcbaadacb",2},"bcbbbbcccbcb"},
            {{"abcbbbbcccbcbaadacb",4},"abcbbbbcccbcbaadacb"}
        };
        for (auto& test : tests) {
            auto res = obj.longest(test.first.first, test.first.second);
            cout << "Longest Unique string :" << res << endl;
            assert(test.second == res);
        }
    }

    string longest(string str, int k) {
        unordered_map<char, int> map;
        vector<int> positions;
        int start = 0;
        int startPositionOffset = 0;
        string res;
        for (int index = 0; index < str.length(); index++) {
            char curChar = str[index];
            if (map.find(curChar) == map.end()) {
                positions.push_back(index);
                map[curChar] = positions.size() - 1;
            }
            else {
                auto posIndex = map[curChar];
                positions[posIndex] = index;
            }

            if (map.size() > k) {
                if (index - start > res.length()) res = str.substr(start, index - start);
                auto startChar = str[positions[startPositionOffset]];
                map.erase(startChar);
                start = positions[startPositionOffset++] + 1;
            }
        }

        if (map.size() == k) {
            if (str.length() - start > res.length()) res = str.substr(start);
        }

        return res;
    }
};