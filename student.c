#include "student.h"
#include "linkstackstudent.h"

// 0、学生菜单
void studentmanu(){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      欢迎使用学生系统                  ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      请选择功能                        ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      0：退出系统                       ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      1：修改自身登陆密码               ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      2：查阅自身信息                   ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

//0、学生选择菜单
int studentselectmanu(){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~   是否返回学生菜单     ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~     1: 是   2: 否      ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
    int i = 0; //初始化选择
    scanf("%d", &i);
    return i;
}
//1、学生登陆
int loadstudent() {
    char *name = (char *)malloc(sizeof(char) * (N + 1)); // 分配账号内存
    char *password = (char *)malloc(sizeof(char) * (M + 1)); // 分配密码内存
    int attempts = 5; // 初始化容错计数（5次机会）
    getchar(); //消除换行

    if (!name || !password) {
        printf("内存分配失败\n");
        return -1; // 内存分配失败
    }

    FILE *fileload = fopen("./stu/student.txt", "r");
    if (!fileload) {
        perror("打开文件失败");
        free(name);
        free(password);
        return -1; // 文件打开失败
    }

    student_list_t B = CreateLinkedListstudent();
    int readnum = 0;

     // 定义用于存储数据的变量
    char namesave[100];
    char passwardsave[100];
    char student_id[100];
    char gender[100];
    char birthdate[100];
    char math_score[100];
    char chinese_score[100];
    char english_score[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(fileload, "\n姓名: %s\n密码: %s\n学号: %s\n性别: %s\n出生日期: %s\n数学成绩: %s\n语文成绩: %s\n英语成绩: %s\n", 
                  namesave, passwardsave, student_id, gender, birthdate, math_score, chinese_score, english_score) == 8) {
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s %s %s %s", namesave, passwardsave, student_id, gender, birthdate, math_score, chinese_score, english_score);

        // 插入链表
        InsertIntoPostLinkListstudent(B, readnum, data);
        readnum++;
    }

    fclose(fileload); // 关闭文件
    B = B->next;

    // 学生账号（姓名）输入
    while (attempts > 0) {
        printf("请输入账号（姓名）(十个字符以内): ");
        fgets(name, N + 1, stdin);
        name[strcspn(name, "\n")] = 0; // 去除末端换行符

        if (strlen(name) > N) {
            printf("超过账号输入上限，请新输入（10个字符以内）\n");
            continue; // 超过上限，重新输入
        }

        // 学生密码输入
        printf("请输入密码: ");
        get_passwordstu(password, M + 1);

        // 判断账号密码是否正确
        student_list_t current = B; // 保存当前链表头
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                // 找到匹配的姓名，检查密码
                if (strcmp(current->password, password) == 0) {
                    printf("登录成功！\n");
                    free(name);
                    free(password);
                    return 1; // 成功登录
                } 
                else {
                    attempts--;
                    printf("输入的密码有误，请重新输入(还有%d次机会)\n", attempts);
                    break; // 密码错误，重新输入
                }
            }
            current = current->next; // 移动到下一个节点
        }

        // 如果遍历完链表后没有找到姓名
        if (current == NULL) {
            attempts--;
            printf("输入的账号有误，请重新输入(还有%d次机会)\n", attempts);
        }
    }

    free(name);
    free(password);
    return 0; // 返回结果
}

//2、修改登陆密码
int changestupassward(){
    char *name = (char *)malloc(sizeof(char) * (N + 1)); // 分配账号内存
    char *password = (char *)malloc(sizeof(char) * (M + 1)); // 分配密码内存
    int attempts = 5; // 初始化容错计数（5次机会）
    int position = 0; //初始化修改位置
    char newpassward[M + 1]; //定义新密码
    getchar(); //消除换行

    if (!name || !password) {
        printf("内存分配失败\n");
        return -1; // 内存分配失败
    }

    FILE *fileload = fopen("./stu/student.txt", "r");
    if (!fileload) {
        perror("打开文件失败");
        free(name);
        free(password);
        return -1; // 文件打开失败
    }

    student_list_t B = CreateLinkedListstudent();
    int readnum = 0;

    // 定义用于存储数据的变量
    char namesave[100];
    char passwardsave[100];
    char student_id[100];
    char gender[100];
    char birthdate[100];
    char math_score[100];
    char chinese_score[100];
    char english_score[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(fileload, "\n姓名: %s\n密码: %s\n学号: %s\n性别: %s\n出生日期: %s\n数学成绩: %s\n语文成绩: %s\n英语成绩: %s\n", 
                  namesave, passwardsave, student_id, gender, birthdate, math_score, chinese_score, english_score) == 8) {
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s %s %s %s", namesave, passwardsave, student_id, gender, birthdate, math_score, chinese_score, english_score);

        // 插入链表
        InsertIntoPostLinkListstudent(B, readnum, data);
        readnum++;
    }

    fclose(fileload); // 关闭文件
    ShowLinkListstudent(B);

    FILE *filechange = fopen("./stu/student.txt", "w");

    // 学生账号（姓名）输入
    printf("\033[H\033[J"); //清空控制台
    printf("检验用户操作\n");
    while (attempts > 0) {
        printf("请输入账号（姓名）(十个字符以内): ");
        fgets(name, N + 1, stdin);
        name[strcspn(name, "\n")] = 0; // 去除末端换行符

        if (strlen(name) > N) {
            printf("\033[H\033[J"); //清空控制台
            printf("超过账号输入上限，请新输入（10个字符以内）\n");
            continue; // 超过上限，重新输入
        }

        // 学生密码输入
        printf("\033[H\033[J"); //清空控制台
        printf("请输入旧密码: ");
        get_passwordstu(password, M + 1);

        // 判断账号密码是否正确
        student_list_t current = B; // 保存当前链表头
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                // 找到匹配的姓名，检查密码
                if (strcmp(current->password, password) == 0) {
                    printf("\033[H\033[J"); //清空控制台
                    printf("密码正确！正在进行密码修改\n");
                    sleep(2);
                    free(name);
                    free(password);
                    goto changepassward;
                }
                else {
                    attempts--;
                    printf("\033[H\033[J"); //清空控制台
                    printf("输入的密码有误，请重新输入(还有%d次机会)\n", attempts);
                    break; // 密码错误，重新输入
                }
            }
            current = current->next; // 移动到下一个节点
            position++;
        }
    // 如果遍历完链表后没有找到姓名
        if (current == NULL) {
            attempts--;
            printf("\033[H\033[J"); //清空控制台
            printf("输入的账号有误，请重新输入(还有%d次机会)\n", attempts);
        }
    }
    free(name);
    free(password);
    printf("\033[H\033[J"); //清空控制台
    printf("账户验证失败\n");
    return 0;

    changepassward:
    while(1){
        printf("\033[H\033[J"); //清空控制台
        printf("请输入新密码(15位以内): ");
        fgets(newpassward, M + 1, stdin);
        newpassward[strcspn(newpassward, "\n")] = 0; // 去除末端换行符
        if(strlen(password) > M) {
            printf("\033[H\033[J"); //清空控制台
            printf("超过密码输入上限，请新输入（15个字符以内）\n");
            continue; // 超过上限，重新输入
        }
        else{
            printf("\033[H\033[J"); //清空控制台
            printf("密码修改成功\n");
            break;
        }
    }
    ChangePostLinkListstudent(B, position, 2, newpassward);
    ShowLinkListstudent(B);
    SaveStudentListToFile(B, filechange);
    return 0;
}

//3、查阅自身信息
void stuselfmessage(){
    char *name = (char *)malloc(sizeof(char) * (N + 1)); // 分配账号内存
    char *password = (char *)malloc(sizeof(char) * (M + 1)); // 分配密码内存
    int attempts = 5; // 初始化容错计数（5次机会）
    int position = 0; //初始化修改位置
    getchar(); //消除换行

    if (!name || !password) {
        printf("内存分配失败\n");
        return; // 内存分配失败
    }

    FILE *fileload = fopen("./stu/student.txt", "r");
    if (!fileload) {
        perror("打开文件失败");
        free(name);
        free(password);
        return; // 文件打开失败
    }

    student_list_t B = CreateLinkedListstudent();
    int readnum = 0;

    // 定义用于存储数据的变量
    char namesave[100];
    char passwardsave[100];
    char student_id[100];
    char gender[100];
    char birthdate[100];
    char math_score[100];
    char chinese_score[100];
    char english_score[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(fileload, "\n姓名: %s\n密码: %s\n学号: %s\n性别: %s\n出生日期: %s\n数学成绩: %s\n语文成绩: %s\n英语成绩: %s\n", 
                  namesave, passwardsave, student_id, gender, birthdate, math_score, chinese_score, english_score) == 8) {
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s %s %s %s", namesave, passwardsave, student_id, gender, birthdate, math_score, chinese_score, english_score);

        // 插入链表
        InsertIntoPostLinkListstudent(B, readnum, data);
        readnum++;
    }

    fclose(fileload); // 关闭文件
    ShowLinkListstudent(B);

    // 学生账号（姓名）输入
    printf("\033[H\033[J"); //清空控制台
    printf("检验用户操作\n");
    while (attempts > 0) {
        printf("请输入账号（姓名）(十个字符以内): ");
        fgets(name, N + 1, stdin);
        name[strcspn(name, "\n")] = 0; // 去除末端换行符

        if (strlen(name) > N) {
            printf("\033[H\033[J"); //清空控制台
            printf("超过账号输入上限，请新输入（10个字符以内）\n");
            continue; // 超过上限，重新输入
        }

        // 学生密码输入
        printf("\033[H\033[J"); //清空控制台
        printf("请输密码: ");
        get_passwordstu(password, M + 1);
        // 判断账号密码是否正确
        student_list_t current = B; // 保存当前链表头
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                // 找到匹配的姓名，检查密码
                if (strcmp(current->password, password) == 0) {
                    printf("\033[H\033[J"); //清空控制台
                    printf("密码正确！正在查阅学生信息\n");
                    sleep(2);
                    printf("\033[H\033[J"); //清空控制台
                    ShowStudentInfo(B, name);
                    free(name);
                    free(password);
                    return;
                }
                else {
                    attempts--;
                    printf("\033[H\033[J"); //清空控制台
                    printf("输入的密码有误，请重新输入(还有%d次机会)\n", attempts);
                    break; // 密码错误，重新输入
                }
            }
            current = current->next; // 移动到下一个节点
            position++;
        }
    // 如果遍历完链表后没有找到姓名
        if (current == NULL) {
            attempts--;
            printf("\033[H\033[J"); //清空控制台
            printf("输入的账号有误，请重新输入(还有%d次机会)\n", attempts);
        }
    }
    free(name);
    free(password);
    printf("\033[H\033[J"); //清空控制台
    printf("账户验证失败\n");
    return;
}