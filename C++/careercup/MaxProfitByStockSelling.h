#include "../header.h"

/*
https://careercup.com/question?id=5180595304923136
30-10 + 42-30 + 20-15 + 50-20 + 25-10
Given predicted stock prices for next n days for a stock e.g : 10, 30, 42, 15, 20, 50, 10, 25 find the maximum profit that can be made with a single buy-sell
transaction. If no profit can be made return 0. In the example buying at 15 and selling at 50 gives maximum profit. Note that the two prices are neither minimum
nor maximum in the array.
*/
class MaxProfitByStockSelling {
   public:
    static void test() {
        MaxProfitByStockSelling obj;
        vector<int> arr = {10, 30, 42, 15, 20, 50, 10, 25};

        for (int i = arr.size(); i <= arr.size(); i++) {
            vector<int> newArr(arr.begin(), arr.begin() + i);

            cout << "Max profit for selling stocks for " << newArr << endl;

            cout << "Max profit by selling stoack at most once: " << obj.maxProfitBySellingStocksOnlyOnce1(newArr) << endl;
            cout << "Max profit by selling stoack at most once: " << obj.maxProfitBySellingStocksOnlyOnce2(newArr) << endl;

            cout << "Max profit by selling stoack at multiple times: " << obj.maxProfitBySellingStocksMultipleTimes1(newArr) << endl;
            cout << "Max profit by selling stoack at multiple times: " << obj.maxProfitBySellingStocksMultipleTimes2(newArr) << endl;

            cout << "Max profit by selling stoack at 2 times only: " << obj.maxProfitBySellingStocksAtMost2Times(newArr) << endl;
        }
    }

   private:
    int maxProfitBySellingStocksOnlyOnce1(vector<int>& prices) {
        int maxProfit = 0;
        int minPrice = INT_MAX;
        for (auto& price : prices) {
            if (price < minPrice) minPrice = price;
            maxProfit = max(maxProfit, price - minPrice);
        }

        return maxProfit;
    }

   private:
    // If I understand correctly, the answer for that particular example would be buying on 15 and selling on 50.
    // If that's the case and I didn't get something wrong, this is a straight-forward max sum on a 1D array (prefix sum).
    int maxProfitBySellingStocksOnlyOnce2(vector<int>& prices) {
        int best = 0, curr = 0;
        for (int i = 1; i < prices.size(); i++) {
            curr += (prices[i] - prices[i - 1]);
            curr = curr < 0 ? 0 : curr;
            best = curr > best ? curr : best;
        }

        return best;
    }

   private:
    int maxProfitBySellingStocksMultipleTimes1(vector<int>& prices) {
        int maxProfit = 0;

        int i = 0;
        while (i < prices.size()) {
            while (i + 1 < prices.size() && prices[i + 1] < prices[i]) i++;
            int s = i;

            while (i + 1 < prices.size() && prices[i + 1] > prices[i]) i++;
            int e = i;

            maxProfit += prices[e] - prices[s];

            i++;
        }

        return maxProfit;
    }

   private:
    int maxProfitBySellingStocksMultipleTimes2(vector<int>& prices) {
        int maxProfit = 0;

        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i - 1]) maxProfit += prices[i] - prices[i - 1];
        }

        return maxProfit;
    }

   private:
    int maxProfitBySellingStocksAtMost2Times(vector<int>& prices) {
        int n = prices.size();
        vector<int> profit(n, 0);

        int mxPrice = prices[n - 1];
        profit[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--) {
            mxPrice = max(mxPrice, prices[i]);
            profit[i] = max(profit[i + 1], mxPrice - prices[i]);
        }

        int mnPrice = prices[0];
        for (int i = 1; i < n; i++) {
            mnPrice = min(prices[i], mnPrice);
            profit[i] = max(profit[i - 1], profit[i] + (prices[i] - mnPrice));
        }

        return profit[n - 1];
    }

   private:
    int maxProfitWithCoolDown(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> memo(n, vector<int>(2, INT_MAX));
        return maxProfitWtithCooldownRecur(prices, 0, n, true, memo);  // start with buying first
    }

    int maxProfitWtithCooldownRecur(vector<int>& prices, int idx, int n, bool buy, vector<vector<int>>& memo) {
        if (idx >= n) return 0;
        if (memo[idx][buy] != INT_MAX) return memo[idx][buy];

        int mxProfit = 0;
        if (buy) {           // if this is buy time
            mxProfit = max(  // get max of buying on this day or skip
                maxProfitWtithCooldownRecur(prices, idx + 1, n, buy, memo),
                -prices[idx] + maxProfitWtithCooldownRecur(prices, idx + 1, n, !buy, memo));
        } else {  // if its selling day, take max of not sellig on this or selling and waiting for 1 day to buy
            mxProfit = max(
                maxProfitWtithCooldownRecur(prices, idx + 1, n, buy, memo),
                prices[idx] + maxProfitWtithCooldownRecur(prices, idx + 2, n, !buy, memo));
        }

        memo[idx][(int)buy] = mxProfit;

        return memo[idx][(int)buy];
    }
};