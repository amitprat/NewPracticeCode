#pragma once
#include "../Header.h"

class MostProfit {
public:
    static void test() {
        MostProfit obj;
        int price[] = { 2, 30, 15, 10, 8, 25, 80 };
        int n = sizeof(price) / sizeof(price[0]);
        cout << "Maximum Profit = " << obj.maxProfit(price, 0, n - 1) << endl;
        cout << "Maximum Profit = " << obj.maxProfitDP(price, n) << endl;
    }

    int maxProfitOne(int price[], int l, int r) {
        if (l >= r) return 0;
        int mn = price[l];
        int mx = price[l];
        for (int i = l + 1; i <= r; i++) {
            mn = min(mn, price[i]);
            mx = max(mx, price[i]);
        }
        return mx - mn;
    }
    int maxProfit(int price[], int l, int r) {
        if (l >= r) return 0;
        if (l + 1 == r) return price[r] - price[l];

        int mx = 0;
        for (int i = l + 1; i < r; i++) {
            int left = price[i] - price[l];
            int right = price[r] - price[i];
            left = left > 0 ? left : 0;
            right = right > 0 ? right : 0;
            int first = right + maxProfitOne(price, l, i - 1);
            int second = left + maxProfitOne(price, i + 1, r);
            int curMax = max(first, second);
            mx = max(mx, curMax);
        }
        return mx;
    }

    int maxProfitDP(int price[], int n) {
        int* profit = new int[n];
        profit[n - 1] = 0;
        int mxPrice = price[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            mxPrice = max(mxPrice, price[i]);
            profit[i] = max(profit[i + 1], mxPrice - price[i]);
        }

        int mnPrice = price[0];
        for (int i = 1; i < n; i++) {
            mnPrice = min(mnPrice, price[i]);
            profit[i] = max(profit[i - 1], profit[i] + (price[i] - mnPrice));
        }

        return profit[n - 1];
    }
};