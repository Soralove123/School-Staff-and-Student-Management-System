#include "teacher.h"
#include "linkstack.h"
#include "linkstackstudent.h"


//0、教师系统菜单
void teachermanu(){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      欢迎使用教师系统                  ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      请选择功能                        ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      0：退出系统                       ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      1：修改自身登陆密码               ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      2：查阅自身信息                   ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      3：添加学生                       ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      4：删除学生                       ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      5：查阅指定学生信息               ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      6：修改学生信息                   ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      7：按学号从低到高查看所有学生信息 ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      8：按总分从低到高查看所有学生信息 ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

//0、教师选择菜单
int teacherselectmanu(){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~   是否返回教师菜单     ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~     1: 是   2: 否      ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
    int i = 0; //初始化选择
    scanf("%d", &i);
    return i;
}

//1、输入登陆账号和密码，获取权限
int loadteacher() {
    char *name = (char *)malloc(sizeof(char) * (N + 1)); // 分配账号内存
    char *password = (char *)malloc(sizeof(char) * (M + 1)); // 分配密码内存
    int attempts = 5; // 初始化容错计数（5次机会）
    getchar(); //消除换行

    if (!name || !password) {
        printf("内存分配失败\n");
        return -1; // 内存分配失败
    }

    FILE *fileload = fopen("./teacher/teacher.txt", "r");
    if (!fileload) {
        perror("打开文件失败");
        free(name);
        free(password);
        return -1; // 文件打开失败
    }

    link_list_t B = CreateEpLinklist();
    int readnum = 0;

    // 定义用于存储数据的变量
    char namesave[100];
    char passwardsave[100];
    char teacherwordsave[100];
    char gendersave[100];
    char birthdatesave[100];
        while (fscanf(fileload, "\n姓名: %s\n密码: %s\n工号: %s\n性别: %s\n出生日期: %s\n", 
                  namesave, passwardsave, teacherwordsave, gendersave, birthdatesave) == 5){
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s", namesave, passwardsave, teacherwordsave, gendersave, birthdatesave);
        InsertIntoPostLinkList(B, readnum, data);
        readnum++;
    }
    fclose(fileload); // 关闭文件
    B = B->next;

    // 教师账号（姓名）输入
    while (attempts > 0) {
        printf("请输入账号（姓名）(十个字符以内): ");
        fgets(name, N + 1, stdin);
        name[strcspn(name, "\n")] = 0; // 去除末端换行符

        if (strlen(name) > N) {
            printf("超过账号输入上限，请新输入（10个字符以内）\n");
            continue; // 超过上限，重新输入
        }

        // 教师密码输入
        printf("请输入密码: ");
        get_password(password, M + 1);
        // 判断账号密码是否正确
        link_list_t current = B; // 保存当前链表头
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
int changetepassward(){
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

    FILE *fileload = fopen("./teacher/teacher.txt", "r");
    if (!fileload) {
        perror("打开文件失败");
        free(name);
        free(password);
        return -1; // 文件打开失败
    }

    link_list_t B = CreateEpLinklist();
    int readnum = 0;

    // 定义用于存储数据的变量
    char namesave[100];
    char passwardsave[100];
    char teacherwordsave[100];
    char gendersave[100];
    char birthdatesave[100];
        while (fscanf(fileload, "\n姓名: %s\n密码: %s\n工号: %s\n性别: %s\n出生日期: %s\n", 
                  namesave, passwardsave, teacherwordsave, gendersave, birthdatesave) == 5){
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s", namesave, passwardsave, teacherwordsave, gendersave, birthdatesave);
        InsertIntoPostLinkList(B, readnum, data);
        readnum++;
    }
    fclose(fileload); // 关闭文件
    ShowLinkList(B);

    FILE *filechange = fopen("./teacher/teacher.txt", "w");

    // 教师账号（姓名）输入
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

        // 教师密码输入
        printf("\033[H\033[J"); //清空控制台
        printf("请输入旧密码: ");
        get_password(password, M + 1);
        // 判断账号密码是否正确
        link_list_t current = B; // 保存当前链表头
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
            break;
        }
    }
    ChangePostLinkList(B, position, 2, newpassward);
    SaveLinkListToFile(B, filechange);
    return 0;
}

//3、查阅自身信息
void selfmessage(){
    getchar();
    int attempts = 5;
    char *name = (char *)malloc(sizeof(char) * (N + 1)); // 分配账号内存
    char *password = (char *)malloc(sizeof(char) * (M + 1)); // 分配密码内存
    FILE *fileload = fopen("./teacher/teacher.txt", "r");
    if (!fileload) {
        perror("打开文件失败");
        return; // 文件打开失败
    }

    link_list_t B = CreateEpLinklist();
    int readnum = 0;

    // 定义用于存储数据的变量
    char namesave[100];
    char passwardsave[100];
    char teacherwordsave[100];
    char gendersave[100];
    char birthdatesave[100];
        while (fscanf(fileload, "\n姓名: %s\n密码: %s\n工号: %s\n性别: %s\n出生日期: %s\n", 
                  namesave, passwardsave, teacherwordsave, gendersave, birthdatesave) == 5){
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s", namesave, passwardsave, teacherwordsave, gendersave, birthdatesave);
        InsertIntoPostLinkList(B, readnum, data);
        readnum++;
    }
    fclose(fileload); // 关闭文件
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

        // 教师密码输入
        printf("\033[H\033[J"); //清空控制台
        printf("请输入密码: ");
        fgets(password, M + 1, stdin);
        printf("\033[H\033[J"); //清空控制台
        password[strcspn(password, "\n")] = 0; // 去除末端换行符

        if (strlen(password) > M) {
            printf("\033[H\033[J"); //清空控制台
            printf("超过密码输入上限，请新输入（15个字符以内）\n");
            continue; // 超过上限，重新输入
        }

        // 判断账号密码是否正确
        link_list_t current = B; // 保存当前链表头
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                // 找到匹配的姓名，检查密码
                if (strcmp(current->password, password) == 0) {
                    printf("检验成功！正在访问用户信息\n");
                    sleep(2);
                    printf("\033[H\033[J"); //清空控制台
                    Showaim(B, name);
                    free(name);
                    free(password);
                    return; // 检验成功
                } 
                else {
                    attempts--;
                    printf("\033[H\033[J"); //清空控制台
                    printf("输入的密码有误，请重新输入(还有%d次机会)\n", attempts);
                    break; // 密码错误，重新输入
                }
            }
            current = current->next; // 移动到下一个节点
        }
        free(password);
        free(name);
        return; // 返回结果
    }
}

//4、添加新学生
void addnewstudent(){
    char *message = (char*)malloc(sizeof(char) * 100);
    getchar();
    FILE* file = fopen("./stu/student.txt", "a+");

    student_list_t A = CreateLinkedListstudent(); // 确保该函数正确实现并返回一个有效的链表

    printf("请输入新学生的姓名，密码，学号，性别，出生日期，数学成绩，语文成绩，英语成绩:\n");
    fgets(message, 100, stdin);
    message[strcspn(message, "\n")] = 0;  // 去除换行符

    InsertIntoPostLinkListstudent(A, studentnum, message);

    // 将链表数据保存到文件
    SaveStudentListToFile(A, file);
    printf("添加新学生成功\n");
    free(message);
    return;

}

//5、删除学生信息
void deletestudentmessage(){
    getchar();
     FILE *file = fopen("./stu/student.txt", "r");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    student_list_t B = CreateLinkedListstudent();
    int readnum = 0;

    // 定义用于存储数据的变量
    char name[100];
    char passward[100];
    char student_id[100];
    char gender[100];
    char birthdate[100];
    char math_score[100];
    char chinese_score[100];
    char english_score[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(file, "\n姓名: %s\n密码: %s\n学号: %s\n性别: %s\n出生日期: %s\n数学成绩: %s\n语文成绩: %s\n英语成绩: %s\n", 
                  name, passward, student_id, gender, birthdate, math_score, chinese_score, english_score) == 8) {
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s %s %s %s", name, passward, student_id, gender, birthdate, math_score, chinese_score, english_score);

        // 插入链表
        InsertIntoPostLinkListstudent(B, readnum, data);
        readnum++;
    }

    fclose(file); // 关闭文件
     FILE *file2 = fopen("./stu/student.txt", "w");
    char* namedel = (char*)malloc(sizeof(char) * 100);
    printf("请输入要删除学生的名字: ");
    fgets(namedel, 100, stdin);
    namedel[strcspn(namedel, "\n")] = 0;  // 去除换行符
    DeleteDataLinkListstudent(&B, namedel);
    SaveStudentListToFile(B, file2);
    free(namedel);
    namedel = NULL;
}

//6、查看学生信息
void showstudentmessage(){
    char* aimname = (char*)malloc(sizeof(char) * 100);
    getchar();
     FILE *file = fopen("./stu/student.txt", "r");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    student_list_t B = CreateLinkedListstudent();
    int readnum = 0;

    // 定义用于存储数据的变量
    char name[100];
    char passward[100];
    char student_id[100];
    char gender[100];
    char birthdate[100];
    char math_score[100];
    char chinese_score[100];
    char english_score[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(file, "\n姓名: %s\n密码: %s\n学号: %s\n性别: %s\n出生日期: %s\n数学成绩: %s\n语文成绩: %s\n英语成绩: %s\n", 
                  name, passward, student_id, gender, birthdate, math_score, chinese_score, english_score) == 8) {
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s %s %s %s", name, passward, student_id, gender, birthdate, math_score, chinese_score, english_score);

        // 插入链表
        InsertIntoPostLinkListstudent(B, readnum, data);
        readnum++;
    }

    fclose(file); // 关闭文件

    printf("请输入要查找的学生的姓名: ");
    fgets(aimname, 100, stdin);
    aimname[strcspn(aimname, "\n")] = 0;
    ShowStudentInfo(B, aimname);
    free(aimname);
}

//7、修改学生信息
void changestudentmessage(){
    getchar();
     FILE *file = fopen("./stu/student.txt", "r");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    student_list_t B = CreateLinkedListstudent();
    int readnum = 0;

    // 定义用于存储数据的变量
    char name[100];
    char passward[100];
    char student_id[100];
    char gender[100];
    char birthdate[100];
    char math_score[100];
    char chinese_score[100];
    char english_score[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(file, "\n姓名: %s\n密码: %s\n学号: %s\n性别: %s\n出生日期: %s\n数学成绩: %s\n语文成绩: %s\n英语成绩: %s\n", 
                  name, passward, student_id, gender, birthdate, math_score, chinese_score, english_score) == 8) {
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s %s %s %s", name, passward, student_id, gender, birthdate, math_score, chinese_score, english_score);

        // 插入链表
        InsertIntoPostLinkListstudent(B, readnum, data);
        readnum++;
    }

    fclose(file); // 关闭文件

    int position = 0;
     FILE *file2 = fopen("./stu/student.txt", "w");
    char* namechange = (char*)malloc(sizeof(char) * 100);
    printf("请输入要修改信息的学生的名字: ");
    fgets(namechange, 100, stdin);
    namechange[strcspn(namechange, "\n")] = 0;  // 去除换行符
    position = SearchDataLinkListstudent(B,  namechange);
    if(position == -1){
        return;
    }
    int k = 0;
    printf("\033[H\033[J"); //清空控制台
    printf("正在进入%s学生的信息库控制系统\n", namechange);
    sleep(2);
    printf("\033[H\033[J"); //清空控制台
    //修改操作菜单
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~正在使用%s学生的信息修改系统~~\n", namechange);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      请选择功能             ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      0：退出系统            ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      1：修改学生登陆姓名    ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      2：修改学生登陆密码    ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      3：修改学生学号        ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      4：修改学生性别        ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      5：修改学生出生日期    ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      6：修改学生数学成绩    ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      7：修改学生语文成绩    ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      5：修改学生英语成绩    ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    scanf("%d", &k);
    getchar();
    if(k == 0){
        printf("\033[H\033[J"); //清空控制台
        printf("正在退出学生信息修改系统\n");
        SaveStudentListToFile(B, file2);
        sleep(2);
        printf("\033[H\033[J"); //清空控制台
        return;
    }
    printf("\033[H\033[J"); //清空控制台
    char* changemessage =(char*)malloc(sizeof(char) * 100);
    printf("输入修改的内容: ");
    fgets(changemessage, 100, stdin);
    printf("\033[H\033[J"); //清空控制台
    changemessage[strcspn(changemessage, "\n")] = 0;  // 去除换行符

    ChangePostLinkListstudent(B, position, k, changemessage);
    SaveStudentListToFile(B, file2);
    printf("修改成功\n");
    free(changemessage);
    free(namechange);
    changemessage = NULL;
    namechange = NULL;


}

//8、按学号从低到高查看所有学生信息
void showstudentwordLowtoHigh(){
    getchar();
    FILE *file = fopen("./stu/student.txt", "r");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    student_list_t B = CreateLinkedListstudent();
    int readnum = 0;

    // 定义用于存储数据的变量
    char name[100];
    char passward[100];
    char student_id[100];
    char gender[100];
    char birthdate[100];
    char math_score[100];
    char chinese_score[100];
    char english_score[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(file, "\n姓名: %s\n密码: %s\n学号: %s\n性别: %s\n出生日期: %s\n数学成绩: %s\n语文成绩: %s\n英语成绩: %s\n", 
                  name, passward, student_id, gender, birthdate, math_score, chinese_score, english_score) == 8) {
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s %s %s %s", name, passward, student_id, gender, birthdate, math_score, chinese_score, english_score);

        // 插入链表
        InsertIntoPostLinkListstudent(B, readnum, data);
        readnum++;
    }

    fclose(file); // 关闭文件
    BubbleSortStudentList(B);
}

//9、按总分从高到低查看所有学生信息
void showstudentscoreHightoLow(){
    getchar();
    FILE *file = fopen("./stu/student.txt", "r");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    student_list_t B = CreateLinkedListstudent();
    int readnum = 0;

    // 定义用于存储数据的变量
    char name[100];
    char passward[100];
    char student_id[100];
    char gender[100];
    char birthdate[100];
    char math_score[100];
    char chinese_score[100];
    char english_score[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(file, "\n姓名: %s\n密码: %s\n学号: %s\n性别: %s\n出生日期: %s\n数学成绩: %s\n语文成绩: %s\n英语成绩: %s\n", 
                  name, passward, student_id, gender, birthdate, math_score, chinese_score, english_score) == 8) {
        // 插入链表
        char data[500];
        snprintf(data, sizeof(data), "%s %s %d %s %s %f %f %f", 
                 name, passward, atoi(student_id), gender, birthdate, atof(math_score), atof(chinese_score), atof(english_score));

        InsertIntoPostLinkListstudent(B, readnum, data);
        readnum++;
    }

    fclose(file); // 关闭文件
    SelectionSortStudentListScoreDesc(B);
}