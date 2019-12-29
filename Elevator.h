#pragma once
#include<iostream>
#include"LinkedQueue.h"
#include"LinkedStack.h"
#include<time.h>
#include<cstdlib>
#include<windows.h>

using namespace std;
#define MAXPSG 13//最大乘客数
#define TIME 100
#define MAXHEIGHT 9//最高楼层数
#define  MAXWAITTIEM 100//最长等待时间为150t



/**************全局变量**********/
enum status //电梯的三个状态
{
    up,     //上升
    down,   //下降
    idle    //空闲
};
status nowstate = idle;//电梯当前状态

int nowfloor = 1;//电梯当前所在楼层

int req_up[MAXHEIGHT+1];      //用来标志有向上请求的楼层
int req_down[MAXHEIGHT+1];    //用来标志由向下请求的楼层
int req_floor[MAXHEIGHT+1];   //标志哪层楼有人要出电梯

//int SlowDownFlag = 1;

long timesum;
long delay;         //输入延时
long sum = 1;         //共出现多少名乘客
long nexttime;      //下一个乘客出现的时刻
long now_stop;      //静止开始的时间
int moved;           //电梯的动作
int next_psg_time;  //下一个人出现的时间间隔
int psg_num;            //电梯内的人数
LinkedStack<int> time_save;//用于对时间的暂存




/******************************************************************************
****************类的设计**********
*****************************************************************************/

/***************时间类***************/
class Time
{
public:
    int wait(long t);//等待的时间的操作
    void TimePause();//暂停计时
    void TimeResume();//恢复计时
};


/*****************乘客类****************/
class Psg
{
public:
    int New_Psg();  /**/  //新增乘客
    int Psg_Infm();//记录乘客信息
public:
    int ID;//乘客编号
    int infloor;//进入电梯的楼层
    int outfloor;//出电梯的楼层
    int waitBegin;//等待开始的时刻
public:
    void InElevator();//乘客进入电梯
    void onwait();//乘客等待电梯
    void OutElevator();//乘客走出电梯
public:
    void PsgGaveUp();//乘客因等待时间过长而放弃

    friend ostream& operator << (ostream& output, Psg& c)
    {
        output << c.ID << "号 ";
        return output;
    }
};


//等待队列
//LinkedQueue<Psg> wait_psg[MAXHEIGHT];//保存要在对应楼层上电梯的等待的乘客的信息
LinkedQueue<Psg> wait_up_psg[MAXHEIGHT];
LinkedQueue<Psg> wait_down_psg[MAXHEIGHT];
//电梯栈
LinkedStack<Psg> elv_psg[MAXHEIGHT];//保存要在对应楼层出电梯的乘客的信息


/****************电梯类******************/
class Elevator
{
public:
    int Elv_OpenDoor();//电梯开门
    int Elv_CloseDoor();//电梯关门
    int Elv_Test();//电梯测试
    int Elv_PsgIn();//乘客进电梯
    int Elv_PsgOut();//乘客出电梯
    int Elv_Up();//电梯上升
    int Elv_Down();//电梯下降
    int Elv_SpendUp();//电梯加速
    int Up_SlowDown();//上升过程中减速
    int Down_SlowDown();//下降过程中减速
    int Elv_Stop();//电梯静止
    int Elv_Work();//电梯工作
    int Elv_Statues();//显示电梯状态
    int Elv_Control();//电梯控制
};


