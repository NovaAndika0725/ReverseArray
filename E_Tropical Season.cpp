#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::multiset<int> s[20];
    std::multiset<int> diff[20];
    i64 sum[20] {};
    
    auto add = [&](int x) {
        int t = std::__lg(x);
        sum[t] += x;
        auto it = s[t].insert(x);
        auto nxt = std::next(it);
        if (it != s[t].begin()) {
            diff[t].insert(x - *std::prev(it));
            if (nxt != s[t].end()) {
                diff[t].extract(*nxt - *std::prev(it));
            }
        }
        if (nxt != s[t].end()) {
            diff[t].insert(*nxt - x);
        }
    };
    
    auto del = [&](int x) {
        int t = std::__lg(x);
        sum[t] -= x;
        auto it = s[t].find(x);
        auto nxt = std::next(it);
        if (it != s[t].begin()) {
            diff[t].extract(x - *std::prev(it));
            if (nxt != s[t].end()) {
                diff[t].insert(*nxt - *std::prev(it));
            }
        }
        if (nxt != s[t].end()) {
            diff[t].extract(*nxt - x);
        }
        s[t].erase(it);
    };
    
    auto query = [&]() {
        i64 cur = 0;
        bool vis[20] {};
        
        std::vector<int> vec;
        std::priority_queue<std::array<int, 3>, std::vector<std::array<int, 3>>, std::greater<>> pq;
        for (int i = 0; i < 20; i++) {
            if (!s[i].empty()) {
                vec.push_back(i);
                int u = *s[i].begin();
                if (!diff[i].empty()) {
                    u = std::min(u, *diff[i].begin());
                }
                pq.push({u, i, i});
            }
        }
        
        auto add = [&](int i) {
            if (i <= 0 || i >= vec.size()) {
                return;
            }
            int l = vec[i - 1];
            int r = vec[i];
            pq.push({*s[r].begin() - *s[l].rbegin(), l, r});
        };
        for (int i = 0; i < vec.size(); i++) {
            add(i);
        }
        
        while (!pq.empty()) {
            auto [v, x, y] = pq.top();
            pq.pop();
            
            if (vis[x] || vis[y]) {
                continue;
            }
            
            if (v > cur) {
                break;
            }
            
            if (x == y) {
                int i = std::find(vec.begin(), vec.end(), x) - vec.begin();
                vis[x] = true;
                cur += sum[x];
                vec.erase(vec.begin() + i);
                add(i);
            } else {
                int i = std::find(vec.begin(), vec.end(), x) - vec.begin();
                assert(vec[i + 1] == y);
                vis[x] = true;
                cur += sum[x];
                vis[y] = true;
                cur += sum[y];
                vec.erase(vec.begin() + i);
                vec.erase(vec.begin() + i);
                add(i);
            }
        }
        
        int tot = 0;
        for (auto i : vec) {
            tot += s[i].size();
        }
        return tot <= 1;
    };
    
    auto answer = [&]() {
        if (query()) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    };
    
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        add(a);
    }
    
    answer();
    for (int i = 0; i < q; i++) {
        char o;
        int x;
        std::cin >> o >> x;
        
        if (o == '+') {
            add(x);
        } else {
            del(x);
        }
        answer();
    }
    
    return 0;
}


// input 1
/*
4 7
2 2 4 11
- 2
+ 4
+ 30
+ 40
- 4
+ 2
+ 2
*/


// input 2
/*
6 7
5000 1000 400 400 100 99
+ 1
- 5000
- 1
- 400
- 400
- 100
- 99
*/


