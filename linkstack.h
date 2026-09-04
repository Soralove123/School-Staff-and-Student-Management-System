#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

typedef char datatype;
typedef struct node_t{
    datatype name[100]; //姓名数据域
    datatype password[100]; //密码域
    datatype teacherword[100]; //工号或学号
    datatype gender[10]; //性别
    datatype birthdate[20]; //生日域
    struct node_t* next; //指针域，指向自身结构体的指针
}link_node_t, *link_list_t;

//0、输入密码
int get_password(char *password, int max_length);

//1、创建一个空的单向链表(有头单向链表)
link_list_t CreateEpLinklist();

//2、求单向链表长度的函数
int LengthLinkList(link_node_t* p);

//3、向单向链表的指定位置插入数据
//p保存链表的头指针post插入的位置data插入的数据
char InsertIntoPostLinkList(link_list_t p, int post, const char* data);

//4、遍历单向链表
void ShowLinkList(link_node_t* p);

//5、删除单向链表中指定位置的数据 post代表的是删除的位置
int DeletePostLinkList(link_node_t* p, int post);

//6、判断单向链表是否为空 1代表为空 0代表非空
int IsEpLinkList(link_node_t* p);

//7、修改指定位置的数据 post 被修改的位置 data 修改成的数据
char ChangePostLinkList(link_list_t p, int post, int field, const char* data);

//8、查找指定数据出现的位置 data被查找的数据

int SearchDataLinkList(link_node_t* p, const char* name);

//9、删除单向链表中出现的指定数据，data代表将单向链表中出现的所有data数据删除
char DeleteDataLinkList(link_list_t* head, const char* name);

//10、清空单向链表
void ClearLinkList(link_node_t* p);

//11、展示目标位置
void Showaim (link_node_t* p, const char* name);

//12、存入文件
void SaveLinkListToFile(link_list_t p, FILE* file);

#endif