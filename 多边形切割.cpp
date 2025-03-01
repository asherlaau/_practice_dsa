#include<iostream>
#include<vector>
using namespace std;
// 递归打印 __int128 数字，处理 a == 0 的情况
void print(__int128 x){
    if(x == 0){
        putchar('0');
        return;
    }
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
 
int main(){
    int n;
    cin >> n;
    vector<__int128> arr;
    for(int i = 0; i < n; i++){
        int t;cin >> t;
        arr.push_back(t);
    }
    vector<vector<__int128>> dp(n + 2, vector<__int128>(n + 2, 0));
    for(int len = 2; len < n; len++){
        for(int i = 0; i + len< n; i++){
            int j = i + len;
            dp[i][j] = dp[i][i + 1] + dp[i + 1][j] + arr[i] * arr[i + 1] * arr[j];
            for(int k = i + 1; k < j; k++){
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + arr[i] * arr[k] * arr[j]);
            }
        }
    }
    print(dp[0][n - 1]);   
}