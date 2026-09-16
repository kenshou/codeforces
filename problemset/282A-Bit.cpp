#include <bits/stdc++.h> // 万能头文件，包含了所有标准库（CF 完美支持）
using namespace std;    // 省略 std:: 前缀

void solve() {
    // 这里写单组测试数据的逻辑
    int n;
    if (!(cin >> n)) return;
    vector<int> a(n);
    string s;
    int x=0;
    for (int i = 0; i < n; i++) {
        cin >> s;
        if (s[1]=='+'){
            x++;
        }else{
            x--;
        }
    }
    // 业务逻辑...
    cout <<x;
}

int main() {
    // 核心：解除 cin/cout 与 C 标准流的同步，加速 I/O，防止 TLE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // 如果题目有多组测试用例（如 CF 常见的 t 组输入），取消下行注释：
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
