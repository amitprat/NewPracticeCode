#include "../Header.h"

/*
Given a string (for example: "a?bc?def?g"), write a program to generate all the possible strings by replacing ? with 0 and 1.
Example:
Input : a?b?c?
Output: a0b0c0, a0b0c1, a0b1c0, a0b1c1, a1b0c0, a1b0c1, a1b1c0, a1b1c1.
*/

/*
No Recursion needed.

Complexity: O(n) * no of combinations

The simplest way to solve this is to consider the number of diff combinations (num_of_comb) and representing that in binary starting from 0 to (num_of_comb - 1).

Ex a?b?c? has 8 comb. i.e 2^3 . i.e. 2 power no of '?'s. Obviously the possible combinations are 000, 001, 010, ..... 110, 111.

Complexity: O(n) * no of combinations.
O(n) to find no of '?'s.

Down below is the complete working code with minor description along. Comment if you can improvise further.
*/

#include <iostream>
#include <cmath>
using namespace std;

void stringReplace(char *str)
{
    char *temp = str;
    int count = 0, num_of_comb = 0, value = 0;

    while (*temp)
    {
        if (*temp == '?')
            count++;
        temp++;
    }
    temp = str;

    num_of_comb = pow(2, count); // count the num of combinations
    cout << "There are " << num_of_comb << " different possible combinations";

    while (value < num_of_comb)
    {
        cout << endl;
        int calc = value;

        /* use the standard Math to convert num to its binary form, modify its output to the present context" */
        while (*temp)
        {
            if (*temp == '?')
            {
                char ch = (calc % 2) ? '1' : '0';
                calc /= 2;
                cout << ch << flush; // do use 'flush' instead of unwanted 'newline' on Linux console to flush the buffer
            }

            else
                cout << *temp << flush;

            temp++;
        }

        temp = str;
        value++;
    }
}

int main()
{
    char A[] = "????"; // makes it easy to see the combinations. You could obviously add letters
    stringReplace(A);
    while (1)
        ;
}

// Mine is below

void generatePattern(string str, int index, int n, string cur)
{
    if (index == n)
    {
        cout << cur << endl;
        return;
    }

    if (str[index] != '?')
        generatePattern(str, index + 1, n, cur + str[index]);
    else
    {
        generatePattern(str, index + 1, n, cur + '0');
        generatePattern(str, index + 1, n, cur + '1');
    }
}

void generatePattern(string str)
{
    queue<string> q;
    q.push("");
    int index = 0;

    while (!q.empty() && index < str.length())
    {
        queue<string> next;
        int sz = q.size();
        while (sz--)
        {
            auto f = q.front();
            q.pop();
            if (str[index] == '?')
            {
                next.push(f + '0');
                next.push(f + '1');
            }
            else
            {
                next.push(f + str[index]);
            }
        }
        index++;
        swap(q, next);
    }

    while (!q.empty())
    {
        cout << q.front() << endl;
        q.pop();
    }
}

int main()
{
    string str = "a?b?c?";
    generatePattern(str);

    return 0;
}
