#include "../header.h"

class TaskSchedulingWithCooldown {
   public:
    static void test() {
        TaskSchedulingWithCooldown obj;
        vector<char> tasks = {'A', 'A', 'A', 'A', 'A', 'A', 'B'};  //, 'C', 'D', 'E', 'F', 'G'};
        auto res = obj.leastInterval(6, 5, tasks);
        cout << res << endl;
    }

   private:
    int leastInterval(int N, int K, vector<char>& tasks) {
        using P = pair<int, int>;
        auto comparator = [](const auto& f, const auto& s) { return f.second < s.second; };
        priority_queue<P, vector<P>, decltype(comparator)> pq;

        unordered_map<char, int> freqMap;
        for (auto& task : tasks) freqMap[task]++;

        for (auto& e : freqMap) pq.push({e.first, e.second});

        int period = 0;
        while (!pq.empty()) {
            vector<char> curTasks;

            // add current task to list
            auto cur = pq.top();
            pq.pop();
            curTasks.push_back(cur.first);
            period++;

            // calculate cooldown period
            int cooldown = 0;
            if (pq.size() < K) cooldown = K - pq.size();  // cooldown period

            // reduce frequency of rest of element
            int mn = min((int)pq.size(), K);
            period += mn;
            while (mn--) {
                auto rest = pq.top();
                pq.pop();
                rest.second--;
                if (rest.second) pq.push(rest);
                curTasks.push_back(rest.first);
            }

            // reduce frequency of cur element and add it back to queue
            cur.second--;
            if (cur.second) pq.push(cur);

            // add the remaining cooldown period
            if (pq.size()) {
                period += cooldown;
                vector<char> coolDownTasks(cooldown, '_');
                curTasks.insert(curTasks.end(), coolDownTasks.begin(), coolDownTasks.end());
            }

            cout << curTasks << endl;
        }

        return period;
    }

   private:
    int leastInterval2(int N, int K, vector<char>& tasks) {
        // code here
        int freq[26] = {0};
        int maxF = 0;

        for (auto i : tasks) {
            freq[i - 'A']++;
            maxF = max(maxF, freq[i - 'A']);
        }

        int maxFcount = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] == maxF) maxFcount++;
        }

        int time = (maxF - 1) * (K + 1) + maxFcount;

        return max(time, N);
    }
};