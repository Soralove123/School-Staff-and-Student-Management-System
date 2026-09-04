#include "linkstackstudent.h"


//0、输入密码
int get_passwordstu(char *password, int max_length) {
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
student_list_t CreateLinkedListstudent() {
    student_list_t p = (student_list_t)malloc(sizeof(student_node_t));
    if (p == NULL) {
        printf("创建错误\n");
        return NULL;
    }
    p->next = NULL;
    return p;
}

//2、求单向链表长度的函数
int LengthLinkListstudent(student_node_t* p) {
    int length = 0; // 初始化长度为0
    while (p != NULL) { // 遍历链表，直到指针为空
        length++; // 每遍历一个节点，长度加1
        p = p->next; // 移动到下一个节点
    }
    return length; // 返回链表的长度
}

//3、向单向链表的指定位置插入数据
//p保存链表的头指针post插入的位置data插入的数据
char InsertIntoPostLinkListstudent(student_list_t p, int post, const char* data) {
    int i;
    student_list_t pnew = NULL;

    // 1. 容错判断：插入位置是否有效
    if (post < 0 || post > LengthLinkListstudent(p)) {
        printf("插入错误\n");
        return -1;
    }

    // 2. 如果链表是空的，处理特殊情况
    if (p == NULL) {
        printf("链表未初始化\n");
        return -1;
    }

    // 3. 遍历到插入位置的前一个节点
    student_list_t current = p->next; // 从头节点的下一个开始遍历
    for (i = 0; i < post; i++) {
        if (current == NULL) {
            printf("插入位置超出链表范围\n");
            return -1; // 防止访问空指针
        }
        current = current->next;
    }

    // 4. 为新节点分配内存
    pnew = (student_list_t)malloc(sizeof(student_node_t));
    if (pnew == NULL) {
        printf("内存分配错误\n");
        return -1;
    }

    // 5. 分配字段内存并复制数据
    sscanf(data, "%s %s %d %s %s %f %f %f", 
           pnew->name, 
           pnew->password, 
           &pnew->student_id, 
           pnew->gender, 
           pnew->birthdate, 
           &pnew->math_score, 
           &pnew->chinese_score, 
           &pnew->english_score);
    pnew->next = NULL;

    // 6. 插入节点到链表中
    if (post == 0) { // 如果插入到头部
        pnew->next = p->next; // 新节点的下一个指向当前链表的第一个节点
        p->next = pnew;       // 头节点的下一个指向新节点
    } else {
        // 找到插入位置前一个节点
        student_list_t previous = p;
        for (i = 0; i < post - 1; i++) {
            previous = previous->next;
        }
        pnew->next = previous->next; // 新节点的下一个指向当前位置的节点
        previous->next = pnew; // 插入新节点
    }
    return 0;
}

//4、遍历单向链表
void ShowLinkListstudent(student_list_t head) {
    // 检查链表是否为空
    if (head == NULL || head->next == NULL) {
        printf("链表为空！\n");
        return;
    }

    // 从第一个有效节点开始遍历
    student_list_t current = head->next;
    while (current != NULL) {
        printf("姓名: %s\n", current->name);
        printf("密码: %s\n", current->password);
        printf("学号: %d\n", current->student_id);
        printf("性别: %s\n", current->gender);
        printf("出生日期: %s\n", current->birthdate);
        printf("数学成绩: %.2f\n", current->math_score);
        printf("语文成绩: %.2f\n", current->chinese_score);
        printf("英语成绩: %.2f\n\n", current->english_score);
        
        current = current->next; // 移动到下一个节点
    }
}


//5、删除单向链表中指定位置的数据 post代表的是删除的位置
int DeletePostLinkListstudent(student_node_t* p, int post){
    int i;
    student_list_t pdel = NULL;

    //1、容错判断
    if(post < 0 || post > LengthLinkListstudent(p)){
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
int IsEpLinkLisstudent(student_node_t* p){
    return p->next == NULL;
}

//7、修改指定位置的数据 post 被修改的位置 data 修改成的数据
char ChangePostLinkListstudent(student_list_t p, int post, int field, const char* data) {
    int i;

    // 1. 容错判断
    if (post < 0 || post >= LengthLinkListstudent(p)) {
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
            printf("学生姓名修改完毕\n");
            break;
        case 2:
            strncpy(p->password, data, sizeof(p->password) - 1);
            p->password[sizeof(p->password) - 1] = '\0';
            printf("学生密码修改完毕\n");
            break;
        case 3:
            p->student_id = atoi(data);
            printf("学生学号修改完毕\n");
            break;
        case 4:
            strncpy(p->gender, data, sizeof(p->gender) - 1);
            p->gender[sizeof(p->gender) - 1] = '\0';
            printf("学生性别修改完毕\n");
            break;
        case 5:
            strncpy(p->birthdate, data, sizeof(p->birthdate) - 1);
            p->birthdate[sizeof(p->birthdate) - 1] = '\0';
            printf("学生出生日期修改完毕\n");
            break;
        case 6:
            p->math_score = atof(data);
            printf("学生数学成绩修改完毕\n");
            break;
        case 7:
            p->chinese_score = atof(data);
            printf("学生语文成绩修改完毕\n");
            break;
        case 8:
            p->english_score = atof(data);
            printf("学生英语成绩修改完毕\n");
            break;
        default:
            printf("错误操作，请重试\n");
            return -1;
    }

    return 0;
}

//8、查找指定数据出现的位置 data被查找的数据
int SearchDataLinkListstudent(student_list_t p, const char* name) {
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
    printf("没有找到该学生\n");
    return -1; 
}

//9、删除单向链表中出现的指定数据，data代表将单向链表中出现的所有data数据删除
char DeleteDataLinkListstudent(student_list_t* head, const char* name) {
    if (head == NULL || *head == NULL) {
        printf("链表为空！\n");
        return -1;
    }

    student_list_t current = *head;
    student_list_t previous = NULL;

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
void ClearLinkListstudent(student_node_t* p){
    student_list_t pdel = NULL;
    while(p->next != NULL){
        pdel = p->next;
        p->next = pdel->next;
        free(pdel);
        pdel = NULL;
    }
}

//11、展示目标位置数据
void ShowStudentInfo(student_list_t p, const char* name) {
    int index = SearchDataLinkListstudent(p, name); // 假设有一个查找学生姓名的函数
    
    if (index == -1) {
        printf("未找到该学生\n");
        return; // 如果未找到，返回
    }

    // 遍历到指定位置
    for (int i = 0; i < index; i++) {
        p = p->next;
    }

    // 打印学生信息
    printf("姓名: %s\n", p->name);
    printf("密码: %s\n", p->password);
    printf("学号: %d\n", p->student_id);
    printf("性别: %s\n", p->gender);
    printf("出生日期: %s\n", p->birthdate);
    printf("数学成绩: %.2f\n", p->math_score);
    printf("语文成绩: %.2f\n", p->chinese_score);
    printf("英语成绩: %.2f\n", p->english_score);
}

//12、存入文件
void SaveStudentListToFile(student_list_t p, FILE* file) {
    if (file == NULL) {
        printf("文件打开失败\n");
        return;
    }

    student_list_t temp = p->next; // 从第一个学生节点开始遍历
    while (temp != NULL) {
        // 将学生节点数据写入文件
        fprintf(file, "姓名: %s\n", temp->name);
        fprintf(file, "密码: %s\n", temp->password);
        fprintf(file, "学号: %d\n", temp->student_id);
        fprintf(file, "性别: %s\n", temp->gender);
        fprintf(file, "出生日期: %s\n", temp->birthdate);
        fprintf(file, "数学成绩: %.2f\n", temp->math_score);
        fprintf(file, "语文成绩: %.2f\n", temp->chinese_score);
        fprintf(file, "英语成绩: %.2f\n", temp->english_score);
        fprintf(file, "\n");
        temp = temp->next; // 移动到下一个节点
    }

    fclose(file); // 关闭文件
}

//13、学号排序
void BubbleSortStudentList(student_list_t head) {
    student_list_t temp = CreateLinkedListstudent(); // 创建一个临时链表
    student_list_t save = NULL;

    while (head->next != NULL) {
        float max = 0;  // 初始化为 -1，确保能比较到所有分数
        student_list_t current = head->next;
        student_list_t prev = head;  // 记录前一个节点，用于删除
        student_list_t prev_max = NULL; // 记录最大分数节点的前一个节点

        // 当只有一个节点时，直接将其插入到 temp 中
        if (current->next == NULL) {
            current->next = temp->next;
            temp->next = current;
            head->next = NULL;  // 更新 head，链表已空
            break;
        }

        // 寻找当前链表中总分最高的学生
        while (current != NULL) {
            float id = current->student_id;
            if (id > max) {
                max = id;
                save = current;
                prev_max = prev;
            }
            prev = current;
            current = current->next;
        }

        // 删除最大节点，并将其插入到 temp 链表
        if (prev_max != NULL) {
            prev_max->next = save->next;  // 删除 save 节点
        }
        save->next = temp->next;  // 将 save 节点插入到 temp 链表的头部
        temp->next = save;
    }

    // 输出排序后的链表
    ShowLinkListstudent(temp);
}

//14、总分排序
void SelectionSortStudentListScoreDesc(student_list_t head) {
    student_list_t temp = CreateLinkedListstudent(); // 创建一个临时链表
    student_list_t save = NULL;

    while (head->next != NULL) {
        float max = 0x3f3f3f3f;  // 初始化为 -1，确保能比较到所有分数
        student_list_t current = head->next;
        student_list_t prev = head;  // 记录前一个节点，用于删除
        student_list_t prev_max = NULL; // 记录最大分数节点的前一个节点

        // 当只有一个节点时，直接将其插入到 temp 中
        if (current->next == NULL) {
            current->next = temp->next;
            temp->next = current;
            head->next = NULL;  // 更新 head，链表已空
            break;
        }

        // 寻找当前链表中总分最高的学生
        while (current != NULL) {
            float total_score = current->math_score + current->chinese_score + current->english_score;
            if (total_score < max) {
                max = total_score;
                save = current;
                prev_max = prev;
            }
            prev = current;
            current = current->next;
        }

        // 删除最大节点，并将其插入到 temp 链表
        if (prev_max != NULL) {
            prev_max->next = save->next;  // 删除 save 节点
        }
        save->next = temp->next;  // 将 save 节点插入到 temp 链表的头部
        temp->next = save;
    }

    // 输出排序后的链表
    ShowLinkListstudent(temp);
}







