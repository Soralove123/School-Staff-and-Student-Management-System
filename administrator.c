#include "administrator.h"
#include "linkstack.h"

//0、管理员系统菜单
void administratormanu(){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      欢迎使用管理员系统    ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      请选择功能            ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      0：退出系统           ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      1：修改自身登陆密码   ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      2：添加新教师         ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      3：查看教师信息       ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      4：删除教师           ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      5：修改教师           ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

//0、管理员选择菜单
int administratorselectmanu(){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~   是否返回管理员菜单   ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~     1: 是   2: 否      ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
    int i = 0; //初始化选择
    scanf("%d", &i);
    return i;
}

//1、输入账号和密码获得管理员权限
int loadadministrator(){
    char *name = (char*)malloc(sizeof(char)*(N+1)); //分配账号内存
    char *passward = (char*)malloc(sizeof(char)*(M+1)); //分配密码内存
    char *fileload_name = (char*)malloc(sizeof(char)*(N + 1)); //分配系统设定账户内存
    char *fileload_passward = (char*)malloc(sizeof(char)*(M + 1)); //分配系统设定密码内存
    int i = 5; //初始化容错计数（5次机会）
    int j = 0; //初使化账号位数
    FILE *fileload = fopen("./administratormassage", "r+");
    //读取系统存入的账户和密码
    fscanf(fileload, "%s\n%s", fileload_name, fileload_passward);
    getchar(); //去除回车影响
    startname: //管理员账号输入开始标签
    j = 0; //重置账号位数
    printf("请输入账号(十个字符以内): "); //输入管理员账号
    while(1){
        char pch;
        scanf("%c", &pch);
        if(pch == '\n'){
            name[j] = '\0'; //去除末端换行符
            //超过上限重新进入
            if(j >= N){
                printf("超过账号输入上限，请新输入（10个字符以内）\n");
                goto startname; //超过上限，重新进入
            }
            goto startpassward;
        }
        name[j] = pch;
        j++;
    }

    printf("\033[H\033[J"); //清空控制台
    // 密码输入
    startpassward: //管理员密码输入开始标签
    printf("请输入密码(十五个字符以内): ");
    get_password(passward, M + 1);

    //判断账号密码是否正确
    if(strcmp(name, fileload_name) != 0){
        i--;
        if(i == 0){
        printf("次数已用完，请重启动程序\n");
        return 0;
        }
        printf("输入的账号有误，请重新输入(还有%d次机会)\n", i);
        sleep(2);
        printf("\033[H\033[J"); //清空控制台
        goto startname;
    }

    if(strcmp(passward, fileload_passward) != 0){
        i--;
        if(i == 0){
        printf("次数已用完，请重启动程序\n");
        return 0;
        }
        printf("输入的密码有误，请重新输入(还有%d次机会)\n", i);
        goto startpassward;
    }
    printf("\033[H\033[J"); //清空控制台
    printf("管理者正在登陆\n");
    free(name);
    free(passward);
    free(fileload_name);
    free(fileload_passward);
    fclose(fileload);
    return 1;
}
//代码总结：1、分配了账号与密码输入的内存
//                      2、从管理员文件中读取系统设定的管理员账号和密码
//                      3、账号输入，用户输入管理员账号，限制十个字符以内(可能没必要)，若超出则重新输入
//                      4、密码输入，限制十五个字符以内。
//                      5、账号和密码的验证，比较用户输入与系统存储的账号以及密码，若不匹配则清屏后重新输入，共5次机会，用完后强制退出管理系统。
//                      6、登陆成功，账号密码正确后，清空控制台并提示登陆成功
//                      7、资源释放，释放内存并关闭文件

//代码特点：1、使用goto进行流程控制，进行处理输入错误重试的流程
//                      2、清屏操作改善用户体验

//2、 修改登陆密码
void changeadpassward(){
    char *passward = (char*)malloc(sizeof(char)*(M+1)); //分配密码内存
    char *oldpassward = (char*)malloc(sizeof(char)*(M + 1)); //分配系统设定密码内存
    char *newpassward = (char*)malloc(sizeof(char)*(M + 1)); //分配新密码内存
    char filecontent[10][100]; //分配修改文件内存
    char *line = (char*)malloc(sizeof(char)*(M + 1)); //分配文件每一行内存
    int lineNumber = 0; //初始化读取行
    int lines = 0; //初始化写入行
    getchar();//去除换行符干扰
    FILE *filechange = fopen("./administratormassage", "r+");

    //读取密码行
    while (fgets(passward, M, filechange)) {
        lineNumber++;
        if (lineNumber == 2) {
            break; //取出密码行  
        }
    }
    passward[strcspn(passward, "\n")] = 0;

    fclose(filechange);
    startconfirmpassward: //密码确认开始标签
    printf("请输入旧密码: ");
    get_password(oldpassward, M + 1);
    printf("\033[H\033[J"); //清空控制台
    if(strcmp(oldpassward, passward) == 0){
        printf("密码输入正确\n");
    }
    else{
        printf("密码输入错误，请重新输入\n");
        goto startconfirmpassward;
    }

    FILE *filechange2 = fopen("./administratormassage", "r+");
    //读取文件的每一行并存储到filecontent数组中
    while(fgets(line, sizeof(line), filechange2)){
        strcpy(filecontent[lines], line);   //保存每行内容
        lines++;
    }

    fclose(filechange2);

    filechange = fopen("./administratormassage", "w");

    // 新密码输入
    startnewpassward: //管理员密码输入开始标签
    printf("请输入新的密码: ");
    fgets(newpassward, M + 1, stdin);
    newpassward[strcspn(newpassward, "\n")] = 0; // 去除末端换行符
    if(strlen(newpassward) > M) {
        printf("\033[H\033[J"); //清空控制台
        printf("超过密码输入上限，请新输入（15个字符以内）\n");
        goto startnewpassward;
    }
    snprintf(filecontent[1], M + 1, "%s\n", newpassward);
    for(int i = 0; i < 2; i++){
        fputs(filecontent[i], filechange);
    }
    fclose(filechange);
    printf("\033[H\033[J"); //清空控制台
    printf("密码修改成功\n");
    
    free(passward);
    free(oldpassward);
    free(newpassward);
    free(line);
}
//代码总结：1、内存分配，为旧密码，新密码，文件行内容等分配内存空间
//                      2、读取文件中的旧密码行并去除换行符
//                      3、密码验证，用户输入旧密码进行密码验证，匹配正确后继续进行后续操作，错误则重新输入
//                      4、通过行读取文件中的内容，保存到数组中，用于后续修改
//                      5、新密码输入，限制15个字符，超出则重新输入
//                      6、将新密码替换到文件相应位置，写回文件
//                      7、操作成功后清空屏幕，提示密码修改成功
//                      8、资源释放并关闭文件

//代码特点：1、密码逐步验证与更新，确保用户安全
//                      2、涉及文件的读取，修改和覆盖

//3、添加新教师
void addnewteacher(){
    char *message = (char*)malloc(sizeof(char) * 100);
    getchar();
    FILE* file = fopen("./teacher/teacher.txt", "a+");

    link_list_t A = CreateEpLinklist(); // 确保该函数正确实现并返回一个有效的链表

    printf("请输入新教师的姓名，密码，工号，性别，出生日期:\n");
    fgets(message, 100, stdin);
    message[strcspn(message, "\n")] = 0;  // 去除换行符

    InsertIntoPostLinkList(A, teachernum, message);

    // 将链表数据保存到文件
    SaveLinkListToFile(A, file);

    free(message);
}
//代码总结：1、内存分配，用于存储教师信息
//                      2、文件打开，用追加模式打开教师信息文件，用于保存新添加的教师数据
//                      3、创建教师信息链表，用于添加教师信息
//                      4、输入教师信息，通过fgets()读取教师详细信息，并去除末尾的换行符
//                      5、插入链表，将新教师的信息插入到链表中
//                      6、保存链表，将链表中所有数据保存到教师文件中，以确保教师信息持久化
//                      7、释放资源，关闭教师文件

//代码特点：1、通过链表组织教师信息，支持后续的批量操作
//                      2、文件保存确保教师信息持久保存

//4、查看全部教师信息
void showteachermessage() {
    FILE *file = fopen("./teacher/teacher.txt", "r");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    link_list_t A = CreateEpLinklist();
    int readnum = 0;

    // 定义用于存储数据的变量
    char name[100];
    char passward[100];
    char teacherword[100];
    char gender[100];
    char birthdate[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(file, "\n姓名: %s\n密码: %s\n工号: %s\n性别: %s\n出生日期: %s\n", 
                  name, passward, teacherword, gender, birthdate) == 5) {
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s", name, passward, teacherword, gender, birthdate);

        // 插入链表
        InsertIntoPostLinkList(A, readnum, data);
        readnum++;
    }

    fclose(file); // 关闭文件
    ShowLinkList(A); // 显示链表内容
    printf("\n");
}
//代码特点：1、文件只读模式打开，防止文件被修改，如果文件无法打开则输出错误信息并退出
//                      2、创建链表，用于存储教师文件中的信息
//                      3、文件读取，使用fscanf()循环读取文件中的教师信息，每次读取姓名，密码，工号，性别，出生日期。格式要求严格，确保文件中的数据与fscanf格式匹配
//                      4、初始化变量，定义了name、passward等字符串变量，用于存储读取的教师数据
//                      5、数据插入链表，将读取的数据组合为单个字符串，并插入到链表中。
//                      6、关闭文件，释放内存
//                      7、显示链表实现对全部教师信息的查看

//代码特点：1、能够从文件中读取多条教师信息并按顺序存储到链表中
//                      2、使用链表组织数据，使后续操作更加方便
//                      3、文件读取和链表插入结合，实现数据的持久化读取和操作



//5、删除教师信息
void deleteteachermessage(){
    getchar();
     FILE *file = fopen("./teacher/teacher.txt", "r");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    link_list_t B = CreateEpLinklist();
    int readnum = 0;

    // 定义用于存储数据的变量
    char name[100];
    char passward[100];
    char teacherword[100];
    char gender[100];
    char birthdate[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(file, "\n姓名: %s\n密码: %s\n工号: %s\n性别: %s\n出生日期: %s\n", 
                  name, passward, teacherword, gender, birthdate) == 5) {
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s", name, passward, teacherword, gender, birthdate);

        // 插入链表
        InsertIntoPostLinkList(B, readnum, data);
        readnum++;
    }

    fclose(file); // 关闭文件
     FILE *file2 = fopen("./teacher/teacher.txt", "w");
    char* namedel = (char*)malloc(sizeof(char) * 100);
    printf("请输入要删除教师的名字: ");
    fgets(namedel, 100, stdin);
    namedel[strcspn(namedel, "\n")] = 0;  // 去除换行符
    DeleteDataLinkList(&B, namedel);
    SaveLinkListToFile(B, file2);
    free(namedel);
    namedel = NULL;
}
//代码总结：1、文件打开，只读模式打开将所有教师信息，有报错判断
//                      2、创建链表B，用于存储教师信息
//                      3、循环读取教师信息并组合成一个字符串插入链表
//                      4、关闭读取文件
//                      5、以写模式打开文件，准备将更新后的链表写入文件
//                      6、获取要删除教师的姓名，通过fgets()获取，并去除换行符
//                      7、通过教师姓名删除对应教师节点
//                      8、保存更新后的链表，覆盖原文件内容
//                      9、释放资源，关闭文件

//代码特点：1、通过链表管理教师信息，使得删除操作简单高效
//                      2、先读取文件内容到链表中，删除操作在链表上完成，再将修改后的链表写回文件，确保文件内容的一致性
//                      3、结合文件读写操作和链表操作，实现了教师信息的动态管理               


//6、修改教师信息
void changeteachermessage(){
    getchar();
     FILE *file = fopen("./teacher/teacher.txt", "r");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    link_list_t B = CreateEpLinklist();
    int readnum = 0;

    // 定义用于存储数据的变量
    char name[100];
    char passward[100];
    char teacherword[100];
    char gender[100];
    char birthdate[100];

    // 循环读取文件，直到到达文件末尾
    while (fscanf(file, "\n姓名: %s\n密码: %s\n工号: %s\n性别: %s\n出生日期: %s\n", 
                  name, passward, teacherword, gender, birthdate) == 5) {
        // 将读取的数据格式化为单个字符串
        char data[500];
        snprintf(data, sizeof(data), "%s %s %s %s %s", name, passward, teacherword, gender, birthdate);

        // 插入链表
        InsertIntoPostLinkList(B, readnum, data);
        readnum++;
    }

    fclose(file); // 关闭文件

    int position = 0;
     FILE *file2 = fopen("./teacher/teacher.txt", "w");
    char* namechange = (char*)malloc(sizeof(char) * 100);
    printf("请输入要修改信息的教师的名字: ");
    fgets(namechange, 100, stdin);
    namechange[strcspn(namechange, "\n")] = 0;  // 去除换行符
    position = SearchDataLinkList(B,  namechange);
    if(position == -1){
        return;
    }
    int k = 0;
    printf("\033[H\033[J"); //清空控制台
    printf("正在进入%s老师的信息库控制系统\n", namechange);
    sleep(2);
    printf("\033[H\033[J"); //清空控制台
    //修改操作菜单
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~正在使用%s老师的信息修改系统~~\n", namechange);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      请选择功能             ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      0：退出系统            ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      1：修改教师登陆姓名    ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      2：修改教师登陆密码    ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      3：修改教师工号        ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      4：修改教师性别        ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      5：修改教师出生日期    ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    scanf("%d", &k);
    getchar();
    if(k == 0){
        printf("\033[H\033[J"); //清空控制台
        printf("正在退出教师信息修改\n");
        SaveLinkListToFile(B, file2);
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

    ChangePostLinkList(B, position, k, changemessage);
    SaveLinkListToFile(B, file2);
    free(changemessage);
    free(namechange);
    changemessage = NULL;
    namechange = NULL;
}
//代码总结：1、文件打开（读取模式）存入链表
//                      2、读取文件内容
//                      3、关闭读取文件
//                      4、用户输入修改对象，通过输入要修改信息教师的姓名，查找教师再链表中的位置，若没找到则退出
//                      5、修改菜单显示，显示一个菜单供用户选择需要修改的项目
//                      6、修改内容输入，根据用户选择，提示输入修改后的信息，并将修改后的数据更新到链表中
//                      7、保存修改：修改完成后，重新以写模式打开教师文件，将更新后的链表数据写回文件中，覆盖旧教师信息
//                      8、释放资源，关闭文件

//代码特点：1、交互性强：通过菜单提供不同的修改选项，用户可以直观选择需要修改的教师的信息项
//                      2、链表操作，读取、修改和保存教师信息均通过链表操作进行，方便后续的扩展和维护
//                      3、文件覆盖更新，确保信息更新后的数据持久化。