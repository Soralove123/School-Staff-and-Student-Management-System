#include <stdio.h>
#include <unistd.h>
#include "administrator.h"
#include "teacher.h"
#include "student.h"
#include "linkstack.h"

//主菜单
void manumain(){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      欢迎使用学生管理系统  ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      请选择您的身份        ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      0：退出系统           ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      1：管理员             ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      2：教师               ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~      3：学生               ~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

int main(){
    printf("\033[H\033[J"); //清空控制台
    start: //程序起点标签
    manumain();
    int Identity = 0; //身份初始化
    int numad = 0; //管理员身份判断初始化
    int numte = 0; //教师身份判断初始化
    int numstu = 0; //学生身份判断初始化
    int numadsel = 0; //管理员功能选择初始化
    int numtesel = 0; //教师功能选择初始化
    int numstusel = 0; //学生功能选择初始化
    printf("您的身份是：\n"); // 身份输入，1：管理员，2：教师，3：学生，0：退出系统
    scanf("%d", &Identity);
    switch(Identity){
    case 0:
        printf("正在退出系统\n");
        sleep(2);
        printf("\033[H\033[J"); //清空控制台
        return 0;
    case 1:
        printf("管理员登陆\n");
        goto administrator;
    case 2:
        printf("教师登陆\n");
        goto teacher;
        break;
    case 3:
        printf("学生登陆\n");
        goto student;
        break;
    default:
        printf("身份选择错误，请等待重新登陆\n");
        sleep(2); //等待2s重启
        printf("\033[H\033[J"); //清空控制台
        goto start; //重启回到程序开头位置
    }

    administrator: //管理员程序开始标签
    printf("\033[H\033[J"); //清空控制台
    printf("您已经使用管理员登陆\n");
    numad = loadadministrator();
    sleep(2);
    printf("\033[H\033[J"); //清空控制台

    administratorchoose: //功能选择开始标签
    //选择管理员功能
    if(numad == 1){
        administratormanu();
        scanf("%d", &numadsel);
        switch(numadsel){
        case 0:
            printf("\033[H\033[J"); //清空控制台
            printf("正在退出系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 1:   
            printf("\033[H\033[J"); //清空控制台
            printf("修改自身登陆密码\n");
            changeadpassward();
            if(administratorselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto administratorchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 2:
            printf("\033[H\033[J"); //清空控制台
            printf("添加新教师\n");
            addnewteacher();
            printf("\033[H\033[J"); //清空控制台
            printf("添加成功\n");
            if(administratorselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto administratorchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 3:
            printf("\033[H\033[J"); //清空控制台
            printf("查看教师信息\n\n");
            showteachermessage();
            if(administratorselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto administratorchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 4:
            printf("\033[H\033[J"); //清空控制台
            printf("删除教师\n");
            deleteteachermessage();
            printf("\033[H\033[J"); //清空控制台
            printf("删除成功\n");
            if(administratorselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto administratorchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 5:
            printf("\033[H\033[J"); //清空控制台
            printf("修改教师信息\n");
            changeteachermessage();
            printf("\033[H\033[J"); //清空控制台
            printf("修改成功\n");
            if(administratorselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto administratorchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        }
    }

    teacher: //教师程序开始标签
    printf("\033[H\033[J"); //清空控制台
    printf("您已经使用教师登陆\n");
    numte = loadteacher();
    sleep(2);
    printf("\033[H\033[J"); //清空控制台
    if(numte == 0){
        printf("教师登陆失败，请重新开始\n");
        goto start;
    }

    teacherchoose: //功能选择开始标签
    //选择教师功能
    if(numte == 1){
        teachermanu();
        scanf("%d", &numtesel);
        switch(numtesel){
        case 0:
            printf("\033[H\033[J"); //清空控制台
            printf("正在退出系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 1:   
            printf("\033[H\033[J"); //清空控制台
            printf("修改自身登陆密码\n");
            changetepassward();
            if(teacherselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto teacherchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 2:
            printf("\033[H\033[J"); //清空控制台
            printf("查阅自身信息\n");
            selfmessage();
            if(teacherselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto teacherchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 3:
            printf("\033[H\033[J"); //清空控制台
            printf("添加新学生\n\n");
            addnewstudent();
            if(teacherselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto teacherchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 4:
            printf("\033[H\033[J"); //清空控制台
            printf("删除学生信息\n");
            deletestudentmessage();
            if(teacherselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto teacherchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 5:
            printf("\033[H\033[J"); //清空控制台
            printf("查看学生信息\n");
            showstudentmessage();
            if(teacherselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto teacherchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 6:
            printf("\033[H\033[J"); //清空控制台
            printf("修改学生信息\n");
            changestudentmessage();
            if(teacherselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto teacherchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 7:
            printf("\033[H\033[J"); //清空控制台
            printf("按学号从低到高查看所有学生信息\n");
            showstudentwordLowtoHigh();
            if(teacherselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto teacherchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 8:
            printf("\033[H\033[J"); //清空控制台
            printf("按总分从高到低查看所有学生信息\n");
            showstudentscoreHightoLow();
            if(teacherselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto teacherchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        }
    }
    student: //学生程序开始标签
    printf("\033[H\033[J"); //清空控制台
    printf("您已经使用学生登陆\n");
    numstu = loadstudent();
    sleep(2);
    printf("\033[H\033[J"); //清空控制台
    if(numstu == 0){
        printf("学生登陆失败，请重新开始\n");
        goto start;
    }

    studentchoose: //功能选择开始标签
    //选择学生功能
    if(numstu == 1){
        studentmanu();
        scanf("%d", &numstusel);
        switch(numstusel){
        case 0:
            printf("\033[H\033[J"); //清空控制台
            printf("正在退出系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 1:   
            printf("\033[H\033[J"); //清空控制台
            printf("修改自身登陆密码\n");
            changestupassward();
            if(studentselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto studentchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        case 2:
            printf("\033[H\033[J"); //清空控制台
            printf("查阅自身信息\n");
            stuselfmessage();
            if(studentselectmanu() == 1){
                printf("\033[H\033[J"); //清空控制台
                goto studentchoose;
            }
            printf("\033[H\033[J"); //清空控制台
            printf("退出管理系统\n");
            sleep(2);
            printf("\033[H\033[J"); //清空控制台
            return 0;
        }
    }
    return 0;
}