#include "../header.h"

class AggregateNumber {
   public:
    static void test() {
        vector<int> numbers = {112358, 122436, 1299111210, 112112224, 222442, 1, 12, 123, 1234};
        AggregateNumber obj;
        for (auto num : numbers) {
            auto res = obj.isAggregate(num);
            cout << format("num:{} is aggregate {}", num, res) << endl;
        }
    }

    bool isAggregate(int num) {
        string numStr = std::to_string(num);
        int n = numStr.length();

        for (int i = 1; i <= n / 2; i++) {
            for (int j = 1; j <= n / 2; j++) {
                if (isAggregate(numStr, i, j, n)) return true;
            }
        }

        return false;
    }

    bool isAggregate(string num, int i, int j, int n) {
        string first = num.substr(0, i);
        string second = num.substr(i, j);

        string cur = first + second;
        while (cur.length() < num.length()) {
            int third = stoi(first) + stoi(second);
            cur += std::to_string(third);

            first = second;
            second = std::to_string(third);
        }

        return cur.length() == num.length() && cur == num;
    }
};