作为有多年 Java 经验的开发者，你已经掌握了面向对象、基础数据结构和算法时间复杂度分析。转到算法竞赛（CP）方向的 C++ **实际上非常快，通常只需 1~2 天**。

你**不需要**去学复杂的现代 C++ 模板元编程、智能指针或多线程，只需要掌握 **“带 STL 的 C 语言”（C with STL）** 这一子集即可。

以下是为你量身定制的 **Java 转 C++ 算法极速入门指南**：

---

### 一、 极简 C++ 算法模板

在 Codeforces 刷题，新建一个 `.cpp` 文件，直接套用下面这个骨架：

```cpp
#include <bits/stdc++.h> // 万能头文件，包含了所有标准库（CF 完美支持）
using namespace std;    // 省略 std:: 前缀

void solve() {
    // 这里写单组测试数据的逻辑
    int n;
    if (!(cin >> n)) return;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    // 业务逻辑...
    cout << "ans\n";
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
```

---

### 二、 Java vs C++ 核心容器与语法对照表

算法中常用的数据结构，映射关系非常直接：

| 场景 / 数据结构 | Java 写法 | C++ 写法 | 关键区别与注意点 |
| :--- | :--- | :--- | :--- |
| **64位整数** | `long` | `long long` | C++ 中 `long` 可能是 32 位，**防溢出必须用 `long long`** |
| **动态数组** | `ArrayList<Integer>` | `vector<int> a;` | 支持 `a.push_back(x)`，直接通过 `a[i]` 随机访问 |
| **可变字符串** | `StringBuilder` / `String` | `string s;` | C++ `string` 本身就是可变的，支持 `s += 'a'`, `s[i]` |
| **哈希集合** | `HashSet<Integer>` | `unordered_set<int>` | 平均 $O(1)$，基于哈希表 |
| **有序集合** | `TreeSet<Integer>` | `set<int>` | $O(\log N)$，基于红黑树，自带排序和去重 |
| **哈希映射** | `HashMap<K, V>` | `unordered_map<K, V>` | 访问 `mp[key]`，如果 key 不存在会自动插入默认值 |
| **有序映射** | `TreeMap<K, V>` | `map<K, V>` | 按 Key 升序排列的红黑树 |
| **优先队列（堆）** | `PriorityQueue<Integer>` | `priority_queue<int>` | ⚠️ **注意：C++ 默认是“大顶堆”，Java 默认是“小顶堆”** |
| **双端队列** | `ArrayDeque<Integer>` | `deque<int>` | 支持首尾 $O(1)$ 插入弹出（`push_back`, `pop_front`） |
| **排序** | `Collections.sort(list)` | `sort(a.begin(), a.end())` | 底层为内省排序（快排+堆排），不会退化为 $O(N^2)$ |

---

### 三、 Java 程序员最容易踩的 4 个 C++ 坑

#### 坑 1：函数传参的“值拷贝”（极易导致超时 TLE / 内存爆掉）
* **Java**：传递对象（如 `ArrayList`）默认传引用。
* **C++**：默认是**全量深拷贝**！如果向函数传递 `vector<int>`，会把整个数组复制一遍，在递归（如 DFS）中会导致性能骤降。
* **正确做法**：**加 `&`（引用传递）**。
  ```cpp
  // 错误：每次调用都会完整复制数组 O(N)
  void dfs(int u, vector<int> adj) { ... }

  // 正确：传递引用 O(1)，如果不修改可以加 const
  void dfs(int u, const vector<int>& adj) { ... }
  ```

#### 坑 2：优先队列（堆）的极性相反
* Java 的 `new PriorityQueue<>()` 默认是**小根堆**（顶部是最小值）。
* C++ 的 `priority_queue<int>` 默认是**大根堆**（顶部是最大值）。
  * 声明小根堆的写法：`priority_queue<int, vector<int>, greater<int>> pq;`
  * 偷懒写法：存入负数 `-x`，取出时再取反 `-pq.top()`。

#### 坑 3：使用 `unordered_map` 被人 Hack（CF 特有机制）
* 在 CF 比赛中，由于 C++ 标准库的 `unordered_map` 哈希函数固定，容易被其他选手构造极端测试数据把复杂度卡成 $O(N^2)$（导致 Time Limit Exceeded）。
* **经验法则**：如果不卡常，优先用自带红黑树的 **`map` / `set`**；如果必须用哈希表且数据量极大，直接用数组模拟或者自定义 Hash。

#### 坑 4：全局数组不用频繁释放与分配
* 在 Java 中你习惯在方法内 `new int[n]`。
* 在 C++ 算法中，对于固定范围的数据，经常直接开**全局大数组**（存放在静态区，不会爆栈），省去频繁分配内存的开销：
  ```cpp
  const int N = 200005;
  int a[N]; // 全局变量默认自动初始化为 0
  ```

---

### 四、 常用 STL 算法函数速查（秒杀繁琐逻辑）

这些内置函数都在 `<algorithm>`（已被 `bits/stdc++.h` 包含）中：

```cpp
vector<int> a = {3, 1, 4, 1, 5, 9};

// 1. 排序与翻转
sort(a.begin(), a.end());               // 升序: [1, 1, 3, 4, 5, 9]
sort(a.begin(), a.end(), greater<int>());// 降序
reverse(a.begin(), a.end());            // 翻转

// 2. 二分查找（要求序列已排序）
// lower_bound: 查找第一个 >= val 的迭代器（位置）
auto it1 = lower_bound(a.begin(), a.end(), 4);
int index = it1 - a.begin(); // 获取下标
// upper_bound: 查找第一个 > val 的迭代器

// 3. 最大/最小值与累加
int mx = *max_element(a.begin(), a.end());
int mn = *min_element(a.begin(), a.end());
long long sum = accumulate(a.begin(), a.end(), 0LL); // 0LL 防止溢出

// 4. 最大公约数 (GCD)
int g = __gcd(12, 18); // 结果为 6
```

---

### 五、 快速上手实操建议

1. **今天**：直接打开 Codeforces，挑 3~5 道你在 Java 中闭着眼睛都能写出的题目（比如 Rating 800 的 [4A - Watermelon](https://codeforces.com/problemset/problem/4/A)、[71A - Way Too Long Words](https://codeforces.com/problemset/problem/71/A)）。
2. **用 C++ 模板手打一遍**：重点感受 `cin/cout`、`vector` 和 `string` 的操作。
3. **完成过渡**：一旦你熟悉了 `vector`、`sort` 和 `&` 引用传参，你会发现 C++ 刷题比 Java 更加轻巧、爽快。
