# CF510D

## 🧠 Problem Statement
给出N个不同的数，取第i个数的代价为c[i]，求去除若干个数，是他们的gcd = 1， 的最小代价

## 💡 Idea / Approach

经典背包问题，dp[i][j] = 取第i个数或者不取第i个数的gcd 为j的最小代价



- transition functions : 
```rust
    dp[i][j] = max(dp[i - 1][k] + c[i], dp[i - 1][j]) 
    j = gcd(a[i], k) 
```
## 🦀 Rust Code

```rust
use std::collections::{HashMap, HashSet};

fn max_treasures(treasures: &HashSet<usize>, d: usize) -> i32 {
    const MAX_POS: usize = 30000;
    const OFFSET_BOUND: i32 = 250;

    // dp[i][offset] = max treasures to reach position i with jump = d + offset
    let mut dp: Vec<HashMap<i32, i32>> = vec![HashMap::new(); MAX_POS + 1];

    let mut result = 0;

    // initialize the first jump
    if d <= MAX_POS {
        let init_val = if treasures.contains(&d) { 1 } else { 0 };
        dp[d].insert(0, init_val);
        result = init_val;
    }

    for i in d..=MAX_POS {
        for (&offset, &val) in &dp[i] {
            let jump = (d as i32) + offset;
            if jump <= 0 {
                continue;
            }

            for delta in -1..=1 {
                let next_jump = jump + delta;
                if next_jump <= 0 {
                    continue;
                }

                let next_pos = i as i32 + next_jump;
                if next_pos > MAX_POS as i32 {
                    continue;
                }

                let next_offset = offset + delta;
                let next_pos = next_pos as usize;
                let next_val = val + if treasures.contains(&next_pos) { 1 } else { 0 };

                let entry = dp[next_pos].entry(next_offset).or_insert(0);
                if next_val > *entry {
                    *entry = next_val;
                    result = result.max(next_val);
                }
            }
        }
    }

    result
}

fn main() {
    // Example usage:
    // Suppose treasure is at positions [5, 9, 12, 17, 20]
    let treasure_positions = vec![5, 9, 12, 17, 20];
    let treasures: HashSet<usize> = treasure_positions.into_iter().collect();
    
    let initial_jump_d = 3;

    let max = max_treasures(&treasures, initial_jump_d);
    println!("Maximum treasures collectable: {}", max);
}

```

```C++
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

int max_treasures(const unordered_set<int>& treasures, int d) {
    const int MAX_POS = 30000;
    const int OFFSET_BOUND = 250;

    // dp[i][offset] = max treasure collected to reach position i with jump = d + offset
    vector<unordered_map<int, int>> dp(MAX_POS + 1);

    int result = 0;

    if (d <= MAX_POS) {
        int init_val = treasures.count(d) ? 1 : 0;
        dp[d][0] = init_val;
        result = init_val;
    }

    for (int i = d; i <= MAX_POS; ++i) {
        for (auto& [offset, val] : dp[i]) {
            int jump = d + offset;
            if (jump <= 0) continue;

            for (int delta = -1; delta <= 1; ++delta) {
                int next_jump = jump + delta;
                if (next_jump <= 0) continue;

                int next_pos = i + next_jump;
                if (next_pos > MAX_POS) continue;

                int next_offset = offset + delta;
                int next_val = val + (treasures.count(next_pos) ? 1 : 0);

                auto& entry = dp[next_pos][next_offset];
                if (next_val > entry) {
                    entry = next_val;
                    result = max(result, next_val);
                }
            }
        }
    }

    return result;
}

int main() {
    // Example: treasures at positions 5, 9, 12, 17, 20
    unordered_set<int> treasures = {5, 9, 12, 17, 20};
    int initial_jump_d = 3;

    int max_collect = max_treasures(treasures, initial_jump_d);
    cout << "Maximum treasures collectable: " << max_collect << endl;

    return 0;
}

```