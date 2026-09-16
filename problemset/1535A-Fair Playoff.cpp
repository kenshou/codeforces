#include <bits/stdc++.h> // 万能头文件，包含了所有标准库（CF 完美支持）
#include <iostream>
using namespace std;    // 省略 std:: 前缀

void solve() {
    // 这里写单组测试数据的逻辑
    int a[2],b[2];
    cin>>a[0]>>a[1]>>b[0]>>b[1];
    int ia=0;
    if(a[1]>a[0]){
        ia=1;
    }
    int ib=0;
    if(b[1]>b[0]){
        ib=1;
    }
    if(a[ia]<b[(ib+1)%2]){
        cout<<"NO\n";
        return;
    }
    if(b[ib]<a[(ia+1)%2]){
        cout<<"NO\n";
        return;
    }
    cout<<"YES\n";
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
