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

int main()
{
    solution().getResult();

    return 0;
}

// #include <bits/stdc++.h>
// #include <mutex>
// #include <thread>
// #include <condition_variable>
// #include <unistd.h>
// #include <cstdlib>

// std::mutex __mutex;                //互斥锁
// std::condition_variable __condVal; //条件变量
// bool flag = true;
// int i = 1;

// void printfA()
// {
//     while (i < 100)
//     {
//         // 休息1秒
//         // std::this_thread::sleep_for(std::chrono::seconds(1));
//         std::unique_lock<std::mutex> lck(__mutex);
//         __condVal.wait(lck, []
//                       { return flag; }); //等待flag=true才打印奇数
//         std::cout << "A " << i++ << std::endl;
//         flag = false;
//         __condVal.notify_one();
//     }
// }

// void printfB()
// {
//     while (i < 100)
//     {
//         std::unique_lock<std::mutex> lck(__mutex);
//         __condVal.wait(lck, []
//                       { return !flag; }); //等待flag=false才打印偶数
//         std::cout << "B " << i++ << std::endl;
//         flag = true;
//         __condVal.notify_one();
//     }
// }
// int main()
// {
//     // freopen("in.txt","r",stdin);
//     std::thread tA(printfA);
//     std::thread tB(printfB);
//     tA.join();
//     tB.join();
//     // tA.detach();
//     // tB.detach();
//     // sleep(2);

//     return 0;
// }