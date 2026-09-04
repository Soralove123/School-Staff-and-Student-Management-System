#ifndef _LINKSTACKSTUDENT_H_
#define _LINKSTACKSTUDENT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

typedef char datatype;

typedef struct student_node {
    datatype name[100];         // 姓名
    datatype password[100];     // 密码
    int student_id;   // 学生学号
    datatype gender[10];        // 性别
    datatype birthdate[20];     // 出生日期
    float math_score;           // 数学成绩
    float chinese_score;        // 语文成绩
    float english_score;        // 英语成绩
    struct student_node* next;  // 指向下一个节点的指针
} student_node_t, *student_list_t;

//0、输入密码
int get_passwordstu(char *password, int max_length);

//1、创建一个空的单向链表(有头单向链表)
student_list_t CreateLinkedListstudent();

//2、求单向链表长度的函数
int LengthLinkListstudent(student_node_t* p);

//3、向单向链表的指定位置插入数据
//p保存链表的头指针post插入的位置data插入的数据
char InsertIntoPostLinkListstudent(student_list_t p, int post, const char* data);

//4、遍历单向链表
void ShowLinkListstudent(student_node_t* p);

//5、删除单向链表中指定位置的数据 post代表的是删除的位置
int DeletePostLinkListstudent(student_node_t* p, int post);

//6、判断单向链表是否为空 1代表为空 0代表非空
int IsEpLinkLisstudent(student_node_t* p);

//7、修改指定位置的数据 post 被修改的位置 data 修改成的数据
char ChangePostLinkListstudent(student_list_t p, int post, int field, const char* data);

//8、查找指定数据出现的位置 data被查找的数据
int SearchDataLinkListstudent(student_list_t p, const char* name);

//9、删除单向链表中出现的指定数据，data代表将单向链表中出现的所有data数据删除
char DeleteDataLinkListstudent(student_list_t* head, const char* name);

//10、清空单向链表
void ClearLinkListstudent(student_node_t* p);

//11、展示目标位置数据
void ShowStudentInfo(student_list_t p, const char* name);

//12、存入文件
//void SaveStudentListToFile(student_list_t p, FILE* file);
void SaveStudentListToFile(FILE* file, student_list_t p);

//13、学号排序(冒泡排序法)
void BubbleSortStudentList(student_list_t head);

//14、总分排序
void SelectionSortStudentListScoreDesc(student_list_t head);

#endif

