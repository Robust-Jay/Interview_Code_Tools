#### 字符串split
```cpp {.line-numbers}
void split(const string &s, vector<string> &tokens, const string &delemiters = " ")
{
    string::size_type lastPos = s.find_first_not_of(delemiters, 0);
    string::size_type pos = s.find_first_of(delemiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.emplace_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delemiters, pos);
        pos = s.find_first_of(delemiters, lastPos);
    }
} 
```

#### 字符串与数字相互转换
```cpp {.line-numbers}
// 数字转字符串
string to_string (int val);
string to_string (long val);
string to_string (long long val);
string to_string (unsigned val);
string to_string (unsigned long val);
string to_string (unsigned long long val);
string to_string (float val);
string to_string (double val);
string to_string (long double val);

// 字符串转数字
stoi; stol; stoll; stof; stod; stold;

// 浮点数输出
#include<iomanip>
cout << setiosflags(ios::fixed);   // 用一般的方式输出，而不是科学记数法
cout << setprecision(2);           // 保留两位有效数字
cout << setiosflags(ios::showpos); // 强制显示符号
```

#### 取整与四舍五入
```cpp {.line-numbers}
floor; // 向下取整
ceil;  // 向上取整
round; // 仅仅对小数点后一位四舍五入

// 如果要保留有效小数数位，可以先乘后除
double x = 1.5684;
double y = round(x * 100) / 100;  // 保留两位有效数字
```
<div STYLE="page-break-after: always;"></div>

#### cctype
```cpp {.line-numbers}
isalnum(); // 判断一个字符是不是alphanumeric，即大小写英文字母或是数字
isalpha(); // 判断一个字符是不是alphabetic，即英文字母
isdigit(); // 判断一个字符是不是数字
tolower(); // 将大写转换为小写
toupper(); // 将小写转换为大写
```

#### 下一个排列
```cpp {.line-numbers}
void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }
    if (i >= 0) {
        int j = nums.size() - 1;
        while (j >= 0 && nums[i] >= nums[j]) {
            j--;
        }
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
}
```

#### 堆
```cpp {.line-numbers}
vector<int> vec = {1, 4, 2, 3, 5};
make_heap(vec.begin(), vec.end(), greater<int>()); // 小顶堆

// 插入元素
vec.emplace_back(20);
push_heap(vec.begin(), vec.end(), greater<int>());

// 删除元素
int val = vec[0]; // 堆顶元素
pop_heap(vec.begin(), vec.end(), greater<int>());
vec.pop_back();

// tag：大顶堆只需要将greater<int>()改为less<int>()，也可以自定义规则
```

<div STYLE="page-break-after: always;"></div>

#### 优先队列
```cpp {.line-numbers}
struct Node
{
    int _x;
    int _y;
    Node(int x, int y) : _x(x), _y(y) {}
};

struct cmp1 // 大根堆排序规则
{
    bool operator()(const Node &lhs, const Node &rhs)
    {
        return lhs._x < rhs._x || (lhs._x == rhs._x && lhs._y < rhs._y);
    }
};

struct cmp2 // 小根堆排序规则
{
    bool operator()(const Node &lhs, const Node &rhs)
    {
        return lhs.__x > rhs.__x || (lhs._x == rhs._x && lhs._y > rhs._y);
    }
};

priority_queue<int, vector<int>, less<int>> q1;    // 大根堆
priority_queue<int, vector<int>, greater<int>> q2; // 小根堆
priority_queue<Node, vector<Node>, cmp1> q3;       // 结构体大根堆
priority_queue<Node, vector<Node>, cmp2> q4;       // 结构体小根堆
```

<div STYLE="page-break-after: always;"></div>

#### STL sort
```cpp {.line-numbers}
struct Node
{
    int _x;
    int _y;
    Node(int x, int y) : _x(x), _y(y) {}
};

struct cmp1
{
    bool operator()(const Node &lhs, const Node &rhs)
    {
        return lhs._x < rhs._x || (lhs._x == rhs._x && lhs._y < rhs._y);
    }
};

struct cmp2
{
    bool operator()(const Node &lhs, const Node &rhs)
    {
        return lhs._x > rhs._x || (lhs._x == rhs._x && lhs._y > rhs._y);
    }
};

vector<int> vec = {1, 4, 2, 3, 5};
sort(vec.begin(), vec.end(), less<int>());    // 升序排序
sort(vec.begin(), vec.end(), greater<int>()); // 降序排序

vector<Node> vecNode = {{1, 2}, {1, 1}, {2, 3}, {2, 2}};
sort(vecNode.begin(), vecNode.end(), cmp1()); // 升序排序
sort(vecNode.begin(), vecNode.end(), cmp2()); // 降序排序

// 升序排序
sort(vecNode.begin(), vecNode.end(), [&](const Node &lhs, const Node &rhs)
    { return lhs._x < rhs._x || (lhs._x == rhs._x && lhs._y < rhs._y); });

// 降序排序
sort(vecNode.begin(), vecNode.end(), [&](const Node &lhs, const Node &rhs)
    { return lhs._x > rhs._x || (lhs._x == rhs._x && lhs._y > rhs._y); });
```

<div STYLE="page-break-after: always;"></div>

#### 线程A和B交替打印奇数和偶数
```cpp {.line-numbers}
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <iostream>

class solution
{
public:
    void getResult()
    {
        flag = true;
        i = 1;

        std::thread tA(std::bind(&solution::funcA, this));
        std::thread tB(std::bind(&solution::funcB, this));

        tA.join();
        tB.join();
    }

private:
    int i;
    std::mutex __mutex;                // 互斥锁
    std::condition_variable __condVal; // 条件变量
    bool flag;

    void funcA()
    {
        while (i < 100)
        {
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            std::unique_lock<std::mutex> lck(__mutex);
            __condVal.wait(lck, [&]
                           { return flag; }); // 当flag=true时打印奇数
            std::cout << "A: " << i++ << std::endl;
            flag = false;
            __condVal.notify_one();
        }
    }

    void funcB()
    {
        while (i < 100)
        {
            std::unique_lock<std::mutex> lck(__mutex);
            __condVal.wait(lck, [&]
                           { return !flag; }); // 当flag=false时打印偶数
            std::cout << "B: " << i++ << std::endl;
            flag = true;
            __condVal.notify_one();
        }
    }
};
```