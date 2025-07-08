# Bitset背包優化

## 🧠 Problem Statement
一共給出n個數，第i個數是xi，xi可以取[li, ri] 中任意的一個值，設 S = sum(xi^2),求S的種類數


## 💡 Idea / Approach
- 首先，由於n 在 1<=n <= 100 之間，li 和 ri 也在100之間，我們可以考慮使用背包解決
- 將每種方案數當做背包的空間，1 和 0 代表能否構成。
- dp[i][j] = dp[i - 1][j - xi^2] {xi <- {li, ri}} 
- j 的最大值是 100*100*100 = 100000
- 但是由於dp[i][j] 其實裝bool 有點浪費
- 我們可以考慮 直接把第二維 直接去掉，把他換成bitset，bitset第i個bit表示 S = i，能否被構成，若果可以 就是1
- dp[i] |= dp[i - 1] << xi^2 

- transition functions : 
```rust
use std::io::{self, BufRead};
use bitvec::prelude::*;

fn main(){
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();

    let max_sum = 1000100;
    let mut f = vec![bitvec![0; max_sum]; n+1];
    f[0].set(0, true);

    for i in 1..=n{
        let line = lines.next().unwrap().unwrap();
        let parts:Vec<_> = line.trim().split_whitespace().collect();
        let l: i32 = parts[0].parse().unwrap();
        let r: i32 = parts[1].parse().unwrap();

        for k in l..=r{
            let sq = (k * k) as usize;
            let shifted = f[i - 1].clone() << sq;
            f[i] |= &shifted;
        }
    }
    let result = f[n].count_ones();
    println!("{}", result);
}
```