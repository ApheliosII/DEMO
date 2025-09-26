#include <iostream>
#include <thread>

#define SUCCESS 0
#define FAIL -1

unsigned int balance = 100; // 全局变量，初始余额为100

int T_alipay_withdraw(int amount) {
    if (balance >= amount) {
        // 模拟一个潜在的操作间隔，增加竞态条件发生的概率
        std::this_thread::sleep_for(std::chrono::microseconds(50));
        balance -= amount;
        return SUCCESS;
    } else {
        return FAIL;
    }
}

void text_01() {
    int result1, result2;

    // 创建两个线程并发支付
    std::thread t1([&result1]() { result1 = T_alipay_withdraw(100); });
    std::thread t2([&result2]() { result2 = T_alipay_withdraw(100); });

    t1.join();
    t2.join();

    std::cout << "线程1支付结果: " << (result1 == SUCCESS ? "成功" : "失败") << std::endl;
    std::cout << "线程2支付结果: " << (result2 == SUCCESS ? "成功" : "失败") << std::endl;
    std::cout << "最终余额: " << balance << std::endl;
}

#define N 100000000
long sum = 0;

void T_sum() { for (int i = 0; i < N; i++) sum++; }

void test_02() {
    // create(T_sum);
    // create(T_sum);
    // join();
    std::thread t1(T_sum);
    std::thread t2(T_sum);
    t1.join();
    t2.join();
    printf("sum = %ld\n", sum);
}

int x = 0, y = 0;

void T1() {
    x = 1; int t = y; // Store(x); Load(y)
    __sync_synchronize();
    printf("%d", t);
}

void T2() {
    y = 1; int t = x; // Store(y); Load(x)
    __sync_synchronize();
    printf("%d", t);
}

int main() {
    // text_01();
    // test_02();
    T1();
    T2();
    
    T2();
    T1();

    T2();

    return 0;
}

// 线程1支付结果: 成功
// 线程2支付结果: 成功
// 最终余额: 4294967196
// sum = 113599742
// sum = 119598579
// sum = 116387581
