#include <bits/stdc++.h> // 万能头文件，包含了所有标准库（CF 完美支持）
#include <cstdio>
using namespace std;    // 省略 std:: 前缀

void solve() {
    // 这里写单组测试数据的逻辑
    long long n;
    cin>>n;
    long long m=n%2;
    //奇数肯定存在
    if(m==1){
        cout<<"YES\n";
        return;
    }else {
        while((m==0)&&(n>2)){
            n/=2;
            m=n%2;
        }
        if(m==1){
            cout<<"YES\n";
            return;
        }else{
            cout<<"NO\n";
            return;
        }
    }
}

int main() {
    // 核心：解除 cin/cout 与 C 标准流的同步，加速 I/O，防止 TLE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t ;
    // 如果题目有多组测试用例（如 CF 常见的 t 组输入），取消下行注释：
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
