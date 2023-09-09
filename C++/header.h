#pragma once

#include <ctype.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <exception>
#include <format>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ds/Tree.h"
using namespace std;

// template <typename T>
// void print(string text = "", const vector<T> &arr = {})
// {
//     if (!text.empty())
//         cout << text << " : ";
//     std::ranges::copy(path, std::ostream_iterator<char>(std::cout, " "));
//     cout << endl;
// }

template <typename T>
std::ostream &operator<<(std::ostream &out, const vector<T> &v) {
    if (!v.empty()) {
        out << '[';
        std::ranges::copy(v, std::ostream_iterator<T>(out, ", "));
        out << "]";
        // out << '\b' << '\b' << ']';  // use two ANSI backspace characters '\b' to overwrite final ", "
    }
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const vector<pair<T, T>> &arr) {
    for (auto &val : arr) {
        out << val << ", ";
    }

    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const pair<T, T> &v) {
    out << "{" << v.first << "," << v.second << "}";
    return out;
}

template <typename U, typename V>
std::ostream &operator<<(std::ostream &out, const map<U, V> &v) {
    out << "[";
    bool prev = false;
    for (auto &e : v) {
        if (prev)
            out << ", ";
        out << "{" << e.first << "," << e.second << "}";

        prev = true;
    }
    out << "]";

    return out;
}

std::ostream &operator<<(std::ostream &out, Tree::Node *root) {
    Tree::prettyPrintTree(root, out);
    return out;
}

template <typename U, typename V>
std::ostream &operator<<(std::ostream &out, const unordered_map<U, V> &v) {
    if (!v.empty()) {
        out << '[';
        for (auto &p : v) {
            out << "{" << p.first << ":" << p.second << "}, ";
        }
        out << ']';
    }
    return out;
}

template <class T>
std::ostream &operator<<(std::ostream &out, vector<vector<T>> &matrix) {
    int N = matrix.size();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            out << matrix[i][j] << "\t";
        cout << endl;
    }

    return out;
}

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    string to_string() const {
        stringstream ss;
        ss << "{" << x << "," << y << "}";

        return ss.str();
    }

    bool operator==(const Point &that) {
        return this->x == that.x && this->y == that.y;
    }

    bool operator!=(const Point &that) {
        return (this->x != that.x || this->y != that.y);
    }

#define START_METHOD() \
    auto startTime = chrono::high_resolution_clock::now();

#define END_METHOD()                                              \
    auto endTime = chrono::high_resolution_clock::now();          \
    std::chrono::duration<double> duration = endTime - startTime; \
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
};

struct Interval {
    int start = 0, end = 0;
    string to_string() {
        stringstream ss;
        ss << "{" << start << "," << end << "}";
        return ss.str();
    }

    bool operator==(const Interval &that) {
        return this->start == that.start && this->end == that.end;
    }
};