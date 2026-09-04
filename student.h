#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N 10 //账号字符上限为10
#define M 15 //密码字符上限为15

// 0、学生菜单
void studentmanu();

//0、学生选择菜单
int studentselectmanu();

//1、学生登陆
int loadstudent();

//2、修改登陆密码
int changestupassward();

//3、查阅自身信息
void stuselfmessage();

#endif