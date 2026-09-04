#ifndef _TEACHER_H_
#define _TEACHER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N 10 //账号字符上限为10
#define M 15 //密码字符上限为15
int studentnum;

//0、教师系统菜单
void teachermanu();

//0、教师选择菜单
int teacherselectmanu();

//1、输入登陆账号和密码，获取权限
int loadteacher();

//2、修改登陆密码
int changetepassward();

//3、查阅自身信息
void selfmessage();

//4、添加新学生
void addnewstudent();

//5、删除学生信息
void deletestudentmessage();

//6、查看学生信息
void showstudentmessage();

//7、修改学生信息
void changestudentmessage();

//8、按学号从低到高查看所有学生信息
void showstudentwordLowtoHigh();

//9、按总分从高到低查看所有学生信息
void showstudentscoreHightoLow();

#endif