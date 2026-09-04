#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N 10 //账号字符上限为10
#define M 15 //密码字符上限为15
int teachernum;

//0、管理员系统菜单
void administratormanu();

//0、管理员选择菜单
int administratorselectmanu();

//1、输入登陆账号和密码，获取权限
int loadadministrator();

//2、修改登陆密码
void changeadpassward();

//3、添加新教师
void addnewteacher();

//4、查看所有教师
void showteachermessage();

//5、删除教师信息
void deleteteachermessage();

//6、修改教师信息
void changeteachermessage();

#endif