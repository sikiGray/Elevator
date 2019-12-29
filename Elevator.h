#pragma once
#include<iostream>
#include"LinkedQueue.h"
#include"LinkedStack.h"
#include<time.h>
#include<cstdlib>
#include<windows.h>

using namespace std;
#define MAXPSG 13//���˿���
#define TIME 100
#define MAXHEIGHT 9//���¥����
#define  MAXWAITTIEM 100//��ȴ�ʱ��Ϊ150t



/**************ȫ�ֱ���**********/
enum status //���ݵ�����״̬
{
    up,     //����
    down,   //�½�
    idle    //����
};
status nowstate = idle;//���ݵ�ǰ״̬

int nowfloor = 1;//���ݵ�ǰ����¥��

int req_up[MAXHEIGHT+1];      //������־�����������¥��
int req_down[MAXHEIGHT+1];    //������־�����������¥��
int req_floor[MAXHEIGHT+1];   //��־�Ĳ�¥����Ҫ������

//int SlowDownFlag = 1;

long timesum;
long delay;         //������ʱ
long sum = 1;         //�����ֶ������˿�
long nexttime;      //��һ���˿ͳ��ֵ�ʱ��
long now_stop;      //��ֹ��ʼ��ʱ��
int moved;           //���ݵĶ���
int next_psg_time;  //��һ���˳��ֵ�ʱ����
int psg_num;            //�����ڵ�����
LinkedStack<int> time_save;//���ڶ�ʱ����ݴ�




/******************************************************************************
****************������**********
*****************************************************************************/

/***************ʱ����***************/
class Time
{
public:
    int wait(long t);//�ȴ���ʱ��Ĳ���
    void TimePause();//��ͣ��ʱ
    void TimeResume();//�ָ���ʱ
};


/*****************�˿���****************/
class Psg
{
public:
    int New_Psg();  /**/  //�����˿�
    int Psg_Infm();//��¼�˿���Ϣ
public:
    int ID;//�˿ͱ��
    int infloor;//������ݵ�¥��
    int outfloor;//�����ݵ�¥��
    int waitBegin;//�ȴ���ʼ��ʱ��
public:
    void InElevator();//�˿ͽ������
    void onwait();//�˿͵ȴ�����
    void OutElevator();//�˿��߳�����
public:
    void PsgGaveUp();//�˿���ȴ�ʱ�����������

    friend ostream& operator << (ostream& output, Psg& c)
    {
        output << c.ID << "�� ";
        return output;
    }
};


//�ȴ�����
//LinkedQueue<Psg> wait_psg[MAXHEIGHT];//����Ҫ�ڶ�Ӧ¥���ϵ��ݵĵȴ��ĳ˿͵���Ϣ
LinkedQueue<Psg> wait_up_psg[MAXHEIGHT];
LinkedQueue<Psg> wait_down_psg[MAXHEIGHT];
//����ջ
LinkedStack<Psg> elv_psg[MAXHEIGHT];//����Ҫ�ڶ�Ӧ¥������ݵĳ˿͵���Ϣ


/****************������******************/
class Elevator
{
public:
    int Elv_OpenDoor();//���ݿ���
    int Elv_CloseDoor();//���ݹ���
    int Elv_Test();//���ݲ���
    int Elv_PsgIn();//�˿ͽ�����
    int Elv_PsgOut();//�˿ͳ�����
    int Elv_Up();//��������
    int Elv_Down();//�����½�
    int Elv_SpendUp();//���ݼ���
    int Up_SlowDown();//���������м���
    int Down_SlowDown();//�½������м���
    int Elv_Stop();//���ݾ�ֹ
    int Elv_Work();//���ݹ���
    int Elv_Statues();//��ʾ����״̬
    int Elv_Control();//���ݿ���
};


