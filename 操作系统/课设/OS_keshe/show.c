#include "core.h"

//将当前状态存入文件
void saveToFile() {
    FILE* outputFile;
    if (fopen_s(&outputFile, "D:\\Progress\\VS2019\\OS_keshe\\system_state.txt", "w") != 0) {
        printf("无法将系统状态写入文件！\n");
        return;
    }

    //将系统状态写入文件
    fprintf(outputFile, "%d %d\n", M, N);
    for (int i = 0; i < N; i++)
        fprintf(outputFile, "%d ", ALL_RESOURCES[i]);
    fprintf(outputFile, "\n");

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fprintf(outputFile, "%d ", MAX[i][j]);
        fprintf(outputFile, "\n");
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fprintf(outputFile, "%d ", ALLOCATION[i][j]);
        fprintf(outputFile, "\n");
    }

    for (int j = 0; j < N; j++)
        fprintf(outputFile, "%d ", AVAILABLE[j]);
    fprintf(outputFile, "\n");

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fprintf(outputFile, "%d ", NEED[i][j]);
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);
    printf("系统状态已写入'system_state.txt'\n");
}

//将文件中系统状态加载入内存
void loadFromFile() {
    FILE* inputFile;
    if (fopen_s(&inputFile, "D:\\Progress\\VS2019\\OS_keshe\\system_state.txt", "r") != 0) {
        printf("无法从文件读取系统状态\n");
        return;
    }

    //逐行从文件读取系统状态
    fscanf_s(inputFile, "%d %d", &M, &N);
    for (int i = 0; i < N; i++)
        fscanf_s(inputFile, "%d", &ALL_RESOURCES[i]);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fscanf_s(inputFile, "%d", &MAX[i][j]);
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fscanf_s(inputFile, "%d", &ALLOCATION[i][j]);
    }

    for (int j = 0; j < N; j++)
        fscanf_s(inputFile, "%d", &AVAILABLE[j]);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fscanf_s(inputFile, "%d", &NEED[i][j]);
    }

    fclose(inputFile);
    printf("系统状态已从'system_state.txt'加载至内存\n");
}

//处理来自进程的资源请求
void requestResources(int processNumber) {
    printf("输入请求资源的进程号 %d:\n", processNumber);
    for (int i = 0; i < N; i++) {
        printf("资源 %d： ", i);
        scanf_s("%d", &Request[i]);
        while (Request[i] > ALL_RESOURCES[i]) {
            printf("请重新输入：");
            scanf_s("%d", &Request[i]);
        }
            
    }

    //从core代码调用函数处理请求
    distributeResources(processNumber);
    if (checkSafety() == -1) {
        printf("无法授予资源，因为它会导致不安全状态！\n");
        restoreResources(processNumber);
    }
    else {
        printf("请求已被批准\n");
    }
}

void displaySystemState() {
    printf("\n━━━━━━━━━━━━━━━━━━\n");
    printf("总体资源：\n");
    for (int j = 0; j < N; j++)
        printf(" 资源%d： %d", j, ALL_RESOURCES[j]);
    printf("\n\n");

    printf("━━━━━━━━━━━━━━━━━━\n");
    printf("可用资源：\n");
    for (int j = 0; j < N; j++)
        printf(" 资源%d: %d", j, AVAILABLE[j]);
    printf("\n\n");

    printf("━━━━━━━━━━━━━━━━━━\n");
    printf("分配给进程的资源: \n\n");
    for (int j = 0; j < N; j++)
        printf("       资源%d", j);
    printf("\n");

    for (int i = 0; i < M; i++) {
        printf("进程%d：   ", i);
        for (int j = 0; j < N; j++)
            printf("%d           ", ALLOCATION[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("━━━━━━━━━━━━━━━━━━\n");
    printf("仍需资源:\n\n");
    for (int j = 0; j < N; j++)
        printf("       资源%d", j);
    printf("\n");

    for (int i = 0; i < M; i++) {
        printf("进程%d：   ", i);
        for (int j = 0; j < N; j++)
            printf("%d           ", NEED[i][j]);
        printf("\n");
    }
    printf("\n");
}



int main() {
    // 初始化系统状态
    printf("加载初始化资源中...\n");
    loadFromFile();

    // 显示初始系统状态
    displaySystemState();

    char choice;
    do {
        // 提问用户是否要请求资源
        printf("\n是否要请求资源? (Y/N): ");
        scanf_s(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            int processNumber;
            printf("输入请求资源的进程号: ");
            scanf_s("%d", &processNumber);

            // 处理资源请求
            requestResources(processNumber);

            // 显示系统状态更新
            displaySystemState();
        }

        // 询问用户是否要保存当前系统状态
        printf("\n是否要保存当前系统状态? (Y/N): ");
        scanf_s(" %c", &choice);
        if (choice == 'Y' || choice == 'y') {
            saveToFile();
        }

        // 询问用户是否要继续
        printf("\n是否继续? (Y/N): ");
        scanf_s(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    return 0;
}
