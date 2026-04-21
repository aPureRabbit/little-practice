#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

static int counter = 0; // 共享变量
// 无同步机制的进程A和B的执行情况可以这样模拟（C语言）：
void process_a_no_sync()
{
    printf("进程A开始使用共享变量 (counter = %d)...\n", counter);

    // 模拟执行到一半
    printf("进程A执行操作：counter++\n");
    counter++;
    printf("现在 counter = %d\n", counter);
    sleep(1); // 模拟执行到一半暂停

    // 尝试执行进程B
    printf("\n--- 尝试执行进程B ---\n");
    printf("进程B尝试访问共享变量...\n");
    printf("进程B进入临界区，counter = %d\n", counter);
    printf("进程B执行操作：counter--\n");
    counter--;
    printf("现在 counter = %d\n", counter);
    printf("进程B离开临界区\n");

    // 继续执行进程A
    printf("\n--- 继续执行进程A ---\n");
    printf("进程A继续执行操作：counter++\n");
    counter++;
    printf("现在 counter = %d\n", counter);
    printf("进程A完成使用共享变量\n");
}
void process_Test_and_Set()
{
    static bool lock = false;
    printf("进程A开始使用共享变量 (counter = %d)...\n", counter);
    lock = true; // 进程A获取锁
    // 模拟执行到一半
    printf("进程A执行操作：counter++\n");
    counter++;
    printf("现在 counter = %d\n", counter);
    sleep(1); // 模拟执行到一半暂停

    // 尝试执行进程B
    printf("\n--- 尝试执行进程B ---\n");
    printf("进程B尝试访问共享变量...\n");
    printf("检查锁，lock = %d\n", lock);
    if (lock)
    {
        printf("进程B发现锁已被占用，等待...\n");
        sleep(1);
        printf("进程B进入临界区，counter = %d\n", counter);
        printf("进程A继续执行操作：counter++\n");
        counter++;
        printf("现在 counter = %d\n", counter);
        printf("进程A完成使用共享变量\n");
        lock = false; // 进程A释放锁
    }
    else
    {
        printf("锁未被占用，进程B获取锁\n");
        printf("进程B进入临界区，counter = %d\n", counter);
        printf("进程B执行操作：counter--\n");
        counter--;
        printf("现在 counter = %d\n", counter);
        printf("进程B离开临界区\n");
        // 继续执行进程A
        printf("\n--- 继续执行进程A ---\n");
        printf("进程A继续执行操作：counter++\n");
        counter++;
        printf("现在 counter = %d\n", counter);
        printf("进程A完成使用共享变量\n");
    }
}
void process_Swap()
{
    printf("进程A开始使用共享变量 (counter = %d)...\n", counter);
    int keyA = 1;
    printf("进程A尝试获取锁，当前 keyA = %d\n", keyA);

    // 模拟执行到一半
    printf("进程A执行操作：counter++\n");
    counter++;
    printf("现在 counter = %d\n", counter);
    sleep(1); // 模拟执行到一半暂停

    // 尝试执行进程B
    printf("\n--- 尝试执行进程B ---\n");
    int keyB = 0;
    printf("进程B尝试获取锁，当前 keyB = %d\n", keyB);

    int temp = keyA;
    keyA = keyB;
    keyB = temp;
    printf("交换后，keyA = %d, keyB = %d\n", keyA, keyB);

    if (keyB == 1)
    {

        printf("进程B发现锁已被占用，等待...\n");
        printf("进程A继续执行操作：counter++\n");
        counter++;
        printf("现在 counter = %d\n", counter);
        printf("进程A完成使用共享变量\n");
        
    }
    else
    {
        printf("进程B进入临界区，counter = %d\n", counter);
        printf("进程B执行操作：counter--\n");
        counter--;
        printf("现在 counter = %d\n", counter);
        printf("进程B离开临界区\n");

        // 继续执行进程A
        printf("\n--- 继续执行进程A ---\n");
        printf("进程A继续执行操作：counter++\n");
        counter++;
        printf("现在 counter = %d\n", counter);
        printf("进程A完成使用共享变量\n");
    }
}
void process_Semaphores()
{
    int semaphore = 1; // 二值信号量，初始值为1
    printf("进程A开始使用共享变量 (counter = %d)...\n", counter);

    // P操作（等待）
    if (semaphore > 0)
    {
        semaphore--;
        printf("进程A获取信号量，semaphore = %d\n", semaphore);

        // 模拟执行到一半
        printf("进程A执行操作：counter++\n");
        counter++;
        printf("现在 counter = %d\n", counter);
        sleep(1); // 模拟执行到一半暂停

        // 尝试执行进程B
        printf("\n--- 尝试执行进程B ---\n");
        printf("进程B尝试访问共享变量...\n");

        // P操作（等待）
        if (semaphore > 0)
        {
            semaphore--;
            printf("进程B获取信号量，semaphore = %d\n", semaphore);
            printf("进程B进入临界区，counter = %d\n", counter);
            printf("进程B执行操作：counter--\n");
            counter--;
            printf("现在 counter = %d\n", counter);
            printf("进程B离开临界区\n");

            // V操作（释放）
            semaphore++;
            printf("进程B释放信号量，semaphore = %d\n", semaphore);
        }
        else
        {
            printf("进程B发现信号量为0，等待...\n");
            sleep(1); // 模拟等待
            printf("进程A继续执行操作：counter++\n");
            counter++;
            printf("现在 counter = %d\n", counter);
            printf("进程A完成使用共享变量\n");
        }
    }
}
int main()
{
    while (1)
    {
        counter = 0;
        printf("========================\n");
        printf("选择模拟方式\n");
        printf("1. 无同步机制\n2. Test-and-Set锁\n3. Swap锁\n4. 信号量\n");
        printf("请输入选项 (1-4): ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            process_a_no_sync();
            break;
        case 2:
            process_Test_and_Set();
            break;
        case 3:
            process_Swap();
            break;
        case 4:
            process_Semaphores();
            break;
        default:
            printf("无效选项，请选择 1-4 之间的数字。\n");
            continue;
        }
        printf("\n最终 counter = %d\n", counter);
    }
    return 0;
}