# rooks 

# problem 
You're on the right track thinking in terms of state compression DP — that's the most efficient and scalable way to handle this problem where:

You place n rooks on an n×n board

Some cells are forbidden

Rooks must not attack each other (i.e., no two in the same row or column)

# idea 
we can use bitmask to mark downt he column being used or not, and as n is not large,
we can loop through all the possbilities, 2^20 is need. and n is 20, so the time complexity would be n*2^n, dp[i][state] = the number of ways the first i row can get state. we will loop through the state, and fill the dp one by one.

# transition dp

```
f[i][st] = number of ways to place rooks in the first i rows, 
           with current columns used encoded in bitmask `st`

(st' & (1 << (j - 1))) == 0
```

# solutions 

``` C++
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    const int N = 20;
    vector<string> grid(N);
    
    for (int i = 0; i < N; ++i) {
        cin >> grid[i]; // each line has 20 chars: '0' or 'x'
    }

    int size = 1 << N;
    vector<long long> dp(size, 0);
    dp[0] = 1; // base case: no rooks placed yet

    for (int mask = 0; mask < size; ++mask) {
        int row = __builtin_popcount(mask); // how many rows have been filled

        if (row >= N) continue; // safety check

        for (int col = 0; col < N; ++col) {
            if ((mask & (1 << col)) == 0 && grid[row][col] == '0') {
                dp[mask | (1 << col)] += dp[mask];
            }
        }
    }

    cout << dp[size - 1] << endl; // full mask: all 20 columns used
    return 0;
}

```