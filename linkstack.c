#include "linkstack.h"

//0、输入密码（隐藏用户输入的密码，提高安全性）
int get_password(char *password, int max_length) {
    struct termios oldt, newt;
    int i = 0;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // 关闭回显
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (i < max_length - 1) {
        ch = getchar();
        if(i >= max_length -1){
            printf("超过密码上限，请重新修改\n");
            return 1;
        }
        if (ch == '\n') { // 回车键
            break;
        }
        password[i] = ch;
        putchar('*'); // 显示 *
        i++;
    }
    password[i] = '\0'; // 字符串结束
    putchar('\n'); // 换行

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 恢复原来的设置
    return 0;
}

//1、创建一个空的单向链表(有头单向链表)
link_list_t CreateEpLinklist(){
    link_list_t p = (link_list_t)malloc(sizeof(link_node_t));
    if(p == NULL){
        printf("创建错误\n");
        return NULL;
    }
    p->next = NULL;
    return p;
}

//2、求单向链表长度的函数
int LengthLinkList(link_node_t* p){
    int length;
    while(p->next != NULL){
        p = p->next;
        length++;
    }
    return length;
}

//3、向单向链表的指定位置插入数据
//p保存链表的头指针post插入的位置data插入的数据
char InsertIntoPostLinkList(link_list_t p, int post, const char* data) {
    int i;
    link_list_t pnew = NULL;

    // 1. 容错判断：插入位置是否有效
    if (post < 0 || post > LengthLinkList(p)) {
        printf("插入错误\n");
        return -1;
    }

    // 2. 如果链表是空的，处理特殊情况
    if (p == NULL) {
        printf("链表未初始化\n");
        return -1;
    }

    // 3. 遍历到插入位置的前一个节点
    link_list_t current = p; // 使用一个新的指针遍历
    for (i = 0; i < post; i++) {
        current = current->next;
    }

    // 4. 为新节点分配内存
    pnew = (link_list_t)malloc(sizeof(link_node_t));
    if (pnew == NULL) {
        printf("内存分配错误\n");
        return -1;
    }

    // 5. 分配字段内存并复制数据
    sscanf(data, "%s %s %s %s %s", pnew->name, pnew->password, pnew->teacherword, pnew->gender, pnew->birthdate);
    pnew->next = NULL;

    // 6. 插入节点到链表中
    if (post == 0) { // 如果插入到头部
        pnew->next = p->next; // 新节点的下一个指向当前链表的第一个节点
        p->next = pnew;       // 头节点的下一个指向新节点
    } else {
        pnew->next = current; // 新节点的下一个指向当前节点
        // 找到插入位置前一个节点
        link_list_t previous = p;
        for (i = 0; i < post - 1; i++) {
            previous = previous->next;
        }
        previous->next = pnew; // 插入新节点
    }
    return 0;
}

//4、遍历单向链表
void ShowLinkList(link_node_t* p){
    while(p->next != NULL){
        p = p->next;
        printf("姓名: %s\n", p->name);
        printf("密码: %s\n", p->password);
        printf("工号: %s\n", p->teacherword);
        printf("性别: %s\n", p->gender);
        printf("出生日期: %s\n\n", p->birthdate);
    }
}

//5、删除单向链表中指定位置的数据 post代表的是删除的位置
int DeletePostLinkList(link_node_t* p, int post){
    int i;
    link_list_t pdel = NULL;

    //1、容错判断
    if(post < 0 || post > LengthLinkList(p)){
        printf("删除错误\n");
        return -1;
    }

    //2、遍历到删除位置前一个节点处
    for(i = 0; i < post; i++){
        p = p->next;
    }

    //3、删除
    pdel = p->next;
    p->next = pdel->next;
    free(pdel);
    pdel = NULL;
    return 0;
}

//6、判断单向链表是否为空 1代表为空 0代表非空
int IsEpLinkList(link_node_t* p){
    return p->next == NULL;
}

//7、修改指定位置的数据 post 被修改的位置 data 修改成的数据
char ChangePostLinkList(link_list_t p, int post, int field, const char* data) {
    int i;

    // 1. 容错判断
    if (post < 0 || post >= LengthLinkList(p)) {
        printf("修改错误: 位置无效\n");
        return -1;
    }

    // 2. 遍历到指定位置
    for (i = 0; i < post; i++) {
        p = p->next;
    }

    // 3. 根据指定数据域进行修改
    switch (field) {
        case 1:
            strncpy(p->name, data, sizeof(p->name) - 1);
            p->name[sizeof(p->name) - 1] = '\0'; // 确保字符串结束
            printf("教师姓名修改完毕\n");
            break;
        case 2:
            strncpy(p->password, data, sizeof(p->password) - 1);
            p->password[sizeof(p->password) - 1] = '\0';
            printf("教师密码修改完毕\n");
            break;
        case 3:
            strncpy(p->teacherword, data, sizeof(p->teacherword) - 1);
            p->teacherword[sizeof(p->teacherword) - 1] = '\0';
            printf("教师工号修改完毕\n");
            break;
        case 4:
            strncpy(p->gender, data, sizeof(p->gender) - 1);
            p->gender[sizeof(p->gender) - 1] = '\0';
            printf("教师性别修改完毕\n");
            break;
        case 5:
            strncpy(p->birthdate, data, sizeof(p->birthdate) - 1);
            p->birthdate[sizeof(p->birthdate) - 1] = '\0';
            printf("教师出生日期修改完毕\n");
            break;
        default:
            printf("错误操作，请重试\n");
            return -1;
    }

    return 0;
}


//8、查找指定数据出现的位置 data被查找的数据
int SearchDataLinkList(link_list_t p, const char* name) {
    int post = 0;  // 初始化索引

    // 检查链表是否为空
    if (p == NULL) {
        printf("链表为空！\n");
        return -1;
    }

    // 遍历链表，查找指定的姓名
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) {  // 根据姓名字段进行比较
            return post;  // 找到则返回索引
        }
        p = p->next;  // 移动到下一个节点
        post++;       // 增加索引
    }
    printf("没有找到该教师\n");
    return -1; 
}


//9、删除单向链表中出现的指定数据，data代表将单向链表中出现的所有data数据删除
char DeleteDataLinkList(link_list_t* head, const char* name) {
    if (head == NULL || *head == NULL) {
        printf("链表为空！\n");
        return -1;
    }

    link_list_t current = *head;
    link_list_t previous = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {  // 根据姓名进行比较
            if (previous == NULL) {
                // 删除头节点
                *head = current->next;
            } else {
                // 删除中间或尾节点
                previous->next = current->next;
            }
            free(current);
            current = NULL;
            return 0; 
        }
        previous = current;
        current = current->next;
    }

    printf("未找到要删除的节点\n");
    return -1;
}


//10、清空单向链表
void ClearLinkList(link_node_t* p){
    link_list_t pdel = NULL;
    while(p->next != NULL){
        pdel = p->next;
        p->next = pdel->next;
        free(pdel);
        pdel = NULL;
    }
}

//11、展示目标位置数据
void Showaim (link_node_t* p, const char* name){
    int i;
    int h;
    h = SearchDataLinkList(p, name);
    for(i = 0; i < h; i++){
        p = p->next;
    }
        printf("姓名: %s\n", p->name);
        printf("密码: %s\n", p->password);
        printf("工号: %s\n", p->teacherword);
        printf("性别: %s\n", p->gender);
        printf("出生日期: %s\n", p->birthdate);
}

//12、存入文件
void SaveLinkListToFile(link_list_t p, FILE* file) {
    link_list_t temp = p;
    while(temp->next != NULL){
        temp = temp->next;
        // 将节点数据写入文件，格式可以根据实际需要调整
        fprintf(file, "姓名: %s\n", temp->name);
        fprintf(file, "密码: %s\n", temp->password);
        fprintf(file, "工号: %s\n", temp->teacherword);
        fprintf(file, "性别: %s\n", temp->gender);
        fprintf(file, "出生日期: %s\n", temp->birthdate);
        fprintf(file, "\n");
        }
    fclose(file);
}
