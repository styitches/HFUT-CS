#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int M; //进程总数
int N; //资源总数
int ALL_RESOURCES[MAX_RESOURCES]; //各种资源的数目总和
int MAX[MAX_PROCESSES][MAX_RESOURCES]; //M个进程对N类资源最大资源需求量
int AVAILABLE[MAX_RESOURCES]; //系统可用资源数
int ALLOCATION[MAX_PROCESSES][MAX_RESOURCES]; //M个进程已得到N类资源的资源量
int NEED[MAX_PROCESSES][MAX_RESOURCES]; //M个进程还需要N类资源的资源量
int Request[MAX_RESOURCES]; //请求资源个数

int safeSequence[MAX_PROCESSES]; // 用于存储安全执行序列的数组

// 检查系统是否处于安全状态的函数
int checkSafety() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    int find, p;

    // 初始化工作向量和完成数组
    for (int i = 0; i < N; i++)
        work[i] = AVAILABLE[i];  //分配完之后可用资源

    for (int i = 0; i < M; i++)
        finish[i] = FALSE;

    // 主循环以检查安全序列
    int count = 0; // 已完成进程计数
    while (count < M) {
        find = FALSE;
        for (p = 0; p < M; p++) {  //循环进程
            if (finish[p] == FALSE) {
                int j;
                for (j = 0; j < N; j++) //循环资源
                    if (NEED[p][j] > work[j])//某个进程的需求资源仍然大于这个可用资源，就跳出循环进入下一个进程判断
                        break;

                if (j == N) {  //如果这个进程需要的几种资源都可满足，就返还资源然后继续判断下一个进程
                    for (int k = 0; k < N; k++)   //返还资源
                        work[k] += ALLOCATION[p][k];
                    finish[p] = TRUE;
                    safeSequence[count++] = p; // 将进程 p 加入安全序列
                    find = TRUE;
                }
            }
        }

        if (find == FALSE)
            break;
    }

    // 如果所有进程都完成，打印安全序列
    if (count == M) {
        printf("安全序列：");
        for (int i = 0; i < M; i++) {
            printf("%d", safeSequence[i]);
            if (i < M - 1)
                printf(" -> ");
        }
        printf("\n");
    }
    else {
        printf("系统处于不安全状态\n");
        return -1; // 返回 -1 表示不安全状态
    }

    return 0; // 返回 0 表示安全状态
}
//将资源分配给进程
void distributeResources(int processNumber) {
    for (int j = 0; j < N; j++) {
        AVAILABLE[j] -= Request[j];
        ALLOCATION[processNumber][j] += Request[j];
        NEED[processNumber][j] -= Request[j];
    }
}

//从进程中恢复资源
void restoreResources(int processNumber) {
    for (int j = 0; j < N; j++) {
        AVAILABLE[j] += Request[j];
        ALLOCATION[processNumber][j] -= Request[j];
        NEED[processNumber][j] += Request[j];
    }
}
