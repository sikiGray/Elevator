#include<iostream>
#include"Elevator.h"

using namespace std;

Time T;
Psg P;
Elevator E;

Psg m, n;

void Init()
{
    for (int i = 1;i <= MAXHEIGHT;++i)
    {
        req_up[i] = 0;
        req_down[i] = 0;
        req_floor[i] = 0;
    }
}

/*********ʱ����ĺ����Ķ���********/


//�ڵȴ�ʱ���ڵĲ���
int Time::wait(long t)
{
    clock_t end;
    end = clock() - delay;
    while (clock() < end + delay + t * TIME)
    {
        if ((clock() - delay >= nexttime))//�ڵȴ�ʱ�����г˿͵���
        {
            cout << (clock() - delay) / TIME << "," << nexttime / TIME << "������״̬��" << "״̬������..." << endl;
            P.New_Psg();//�����˿�
        }
            
    }
    return 0;
}

//��ͣ��ʱ�������ȴ��û����룩
void Time::TimePause()
{
    time_save.Push(clock());//����������е����ھ�����ʱ��
    timesum = clock();//��¼�������е����ھ�������ʱ��
}

//�ָ���ʱ����
void Time::TimeResume()
{
    delay += clock() - time_save.Pop();//�������뵼�µ���ʱ
    //time_save.pop();
}



/********************�˿���ĺ�������*******************/

//�˿ͽ������
void Psg::InElevator()
{
    elv_psg[outfloor - 1].Push(*this);//���ó˿�ѹ�������¥��ĵ���ջ��
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "���˿͡�" << ID << "�ų˿ʹ�" << infloor << "¥������ݡ�" << endl;
    req_floor[outfloor] = 1;//��־Ҫ��¥���������
}

//�˿�������¥��ȴ�
void Psg::onwait()
{
    //wait_psg[infloor - 1].EnQueue(*this);
    if (this->infloor > this->outfloor)
        wait_down_psg[infloor - 1].EnQueue(*this);
    else
        wait_up_psg[infloor - 1].EnQueue(*this);
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "���˿͡�" << ID << "�ų˿ͽ���" << infloor << "¥�ĵȴ����С�" << endl;
}

//�˿ͳ�����
void Psg::OutElevator()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "���˿͡�" << ID << "�ų˿ͳ����ݡ�" << endl;
}

//�˿���ȴ�ʱ�����������
void Psg::PsgGaveUp()
{
    clock_t now = clock();
    //cout << now << endl;
    //T.TimePause();
    for (int i = 0;i < MAXHEIGHT;++i)
    {
        while (!wait_up_psg[i].QueueIsEmpty())
        {
            if ((now-delay - wait_up_psg[i].Front().waitBegin)/TIME > MAXWAITTIEM)
            {
                //cout << (now -delay- wait_psg[i].Front().waitBegin) / TIME << endl;
                //cout << wait_psg[i].Front().waitBegin << endl;
                n=wait_up_psg[i].DeQueue();
                cout << (now - delay) / TIME << "," << nexttime / TIME << "���˿͡�" << n.ID << "�ų˿���ȴ�ʱ������뿪�ȴ�����" << endl;
                T.TimePause();
                T.wait(20);
                T.TimeResume();
                //system("pause");
            }
            else
                break;
        }
        while (!wait_down_psg[i].QueueIsEmpty())
        {
            if ((now - delay - wait_down_psg[i].Front().waitBegin) / TIME > MAXWAITTIEM)
            {
                //cout << (now -delay- wait_psg[i].Front().waitBegin) / TIME << endl;
                //cout << wait_psg[i].Front().waitBegin << endl;
                n = wait_down_psg[i].DeQueue();
                cout << (now - delay) / TIME << "," << nexttime / TIME << "���˿͡�" << n.ID << "�ų˿���ȴ�ʱ������뿪�ȴ�����" << endl;
                T.TimePause();
                T.wait(20);
                T.TimeResume();
                //system("pause");
            }
            else
                break;
        }
    }
    //T.TimeResume();
}

//�˿���Ϣ������
int Psg::Psg_Infm()
{
    clock_t now = clock();
    //cout << now << endl;
    int timeflag = 0;//ʱ��ָ��ı�־
    cout << "�������˿͡������룺����¥�㡢Ŀ��¥�㡢��һ�˿͵�����ʱ����" << endl;
    if (timeflag == 0)
        T.TimePause();//��ͣ��ʱ
    timeflag = 1;
    while (cin >> m.infloor >> m.outfloor >> next_psg_time)
    {
        /***???***/
        if (m.infloor == 0 && m.outfloor == 0 && next_psg_time == 0)
        {
            int nowdelay = delay;
            cout << " " << endl;
            E.Elv_Statues();
            P.Psg_Infm();
        }
        //�������ĺϷ���
        if (m.infloor >= MAXHEIGHT+1 || m.infloor <= 0 || m.outfloor >= MAXHEIGHT+1 || m.outfloor <= 0 || m.infloor == m.outfloor)
        {
            cout << (clock() - delay) / TIME << "," << nexttime / TIME << "����������" << "����¥���������������" << endl;
            continue;
        }
        else
        {
            //if(!time_save.StackIsEmpty())
                //m.waitBegin = time_save.Top();
            m.waitBegin = now;
            //cout << m.waitBegin << endl;
            //system("pause");
            break;
        }
            
    }

    if (timeflag != 0)
        T.TimeResume();//�ָ���ʱ
    timeflag = 0;
    return 0;
}

//����һ���˿�     
int Psg::New_Psg()
{
    m.ID = sum;
    sum++;
    P.Psg_Infm();//��¼�˿���Ϣ
    
    //if (nexttime > clock() - delay)
    //{
        /***?????????????????????***/
     //   nexttime += nexttime + next_psg_time * TIME;
    //}
    //else//������һ���˿͵�����ʱ��
   // {
        nexttime = clock() - delay + next_psg_time * TIME;
    //}
    //�жϳ˿���Ҫ��¥������¥
    if (m.infloor > m.outfloor)//��¥
    {
        req_down[m.infloor] = 1;//��¼������¥�����¥��
    }
    else//��¥
    {
        req_up[m.infloor] = 1;//��¼������¥�����¥��
    }
    m.onwait();//�˿ͽ���ȴ�����
    //cout << wait_psg[0].Front().waitBegin << endl;
    //system("pause");
    return 0;
}


/*********************������ĺ�������****************/
//��ʾ����״̬����
int Elevator::Elv_Statues()
{
    int i;

    cout << "******************************** ����״̬��Ϣ *********************************" << endl;
    cout << "**********************-----------------------------------**********************" << endl;
    cout << "************-------------------- �ִ�¥�㣺" << nowfloor << " --------------------**************" << endl;

    cout << "                            ح------------------ح                             " << endl;
    cout << "                            ح ǰ����¥��ĳ˿� ح                             " << endl;
    cout << "                            ح------------------ح                             " << endl;
    for (i = MAXHEIGHT;i >= 1;i--)
    {
        cout << "                            ح";
        if (i == nowfloor)
            cout << "  ��";
        else
            cout << "    ";
        cout << " ��" << i << "�㣺";

        /**-------------------------**/
        elv_psg[i - 1].StackTranverse();//�����������ջ
        /**-------------------------**/
        cout << "      ح"<<endl;
        
    }
    cout << endl;
    cout << "                            ح------------------ح                             " << endl;
    cout << "                            ح ��¥��ȴ��ĳ˿� ح                             " << endl;
    cout << "                            ح------------------ح                             " << endl;
    for (i = MAXHEIGHT;i >= 1;i--)
    {
        cout << "                            ح";
        if (i == nowfloor)
            cout << "  ��";
        else
            cout << "    ";
        cout << " ��" << i << "�㣺";
        /**-------------------------**/
        wait_up_psg[i - 1].QueueTranverse();//�������¥��ĵȴ�����
        wait_down_psg[i - 1].QueueTranverse();
        /**-------------------------**/
        cout << "      ح" << endl;
    }
    cout << "-------------------------------------------------------------------------------" << endl;
    return 0;
}

//���ݿ���
int Elevator::Elv_OpenDoor()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����������С�" << "���ڿ���..." << endl;
    T.wait(20);
    return 0;
}

//���ݹ���
int Elevator::Elv_CloseDoor()
{
    
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����������С�" << "���ڹ���..." << endl;
    T.wait(20);
    return 0;
}

//���ݲ���
int Elevator::Elv_Test()
{
        
        cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����������С�" << "���ڵȴ�..." << endl;
        T.wait(40);
        return 0;
}

//�˿ͽ������
int Elevator::Elv_PsgIn()
{
    if (nowstate == idle || nowstate == up)
    {
        //��ǰ¥��ĵȴ����в�Ϊ�գ��ҵ���δ��
        while (!wait_up_psg[nowfloor - 1].QueueIsEmpty() && psg_num < MAXPSG)
        {
            n = wait_up_psg[nowfloor - 1].DeQueue();//ȡ��ͷ
            T.wait(25);//һ���˽�����Ҫ25t
            n.InElevator();//�˿ͽ�����ݣ�ͬʱ���˿�ѹ�����ջ
            psg_num++;
        }
    }
    else
    {
        while (!wait_down_psg[nowfloor - 1].QueueIsEmpty() && psg_num < MAXPSG)
        {
            n = wait_down_psg[nowfloor - 1].DeQueue();//ȡ��ͷ
            T.wait(25);//һ���˽�����Ҫ25t
            n.InElevator();//�˿ͽ�����ݣ�ͬʱ���˿�ѹ�����ջ
            psg_num++;
        }
    }

    return 0;
}

//�˿ͳ�����
int Elevator::Elv_PsgOut()
{
    //����ջ��Ϊ��
    while (!elv_psg[nowfloor - 1].StackIsEmpty())
    {
        n = elv_psg[nowfloor - 1].Pop();
        T.wait(25);//ÿ���˳�����Ҫ25t
        n.OutElevator();
        psg_num--;
    }
    return 0;
}

//��������
int Elevator::Elv_Up()
{

    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����������С�" << "��������..." << endl;
    T.wait(51);//����������Ҫ51t
    req_floor[nowfloor] = 0;//�ò�¥�ĳ����������Ѵ�����ϣ�����־��Ϊ0
    nowfloor++;

    req_up[nowfloor - 1] = 0;//���������Ѵ������

    /*if (SlowDownFlag == 1)
    {
        if (nowstate == up)
            E.Up_SlowDown();
        else if (nowstate == down)
            E.Down_SlowDown();
    }*/

    system("cls");
    E.Elv_Statues();
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����������С�" << "������������" << nowfloor << "��" << endl;
   
    //req_floor[nowfloor] = 0;

    moved= 1;
    return 0;
}

//�����½�
int Elevator::Elv_Down()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����������С�" << "�����½�..." << endl;
    T.wait(61);//�½���Ҫ61t
    req_floor[nowfloor] = 0;
    nowfloor--;

    req_down[nowfloor + 1] = 0;//�½������Ѵ������

    /*if (SlowDownFlag == 1)
    {
        if (nowstate == up)
            E.Up_SlowDown();
        else if (nowstate == down)
            E.Down_SlowDown();
    }*/

    system("cls");
    E.Elv_Statues();
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����������С�" << "�����½����˵�" << nowfloor << "��" << endl;

    //req_floor[nowfloor] = 0;
    moved= 1;
    return 0;
}
//���ݼ���
int Elevator::Elv_SpendUp()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����������С�" << "���ڼ���..." << endl;
    T.wait(15);//���ݼ�����Ҫ15t
    return 0;
}

//���������м���
int Elevator::Up_SlowDown()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����������С�" << "���ڼ���..." << endl;
    T.wait(14);//��������������Ҫ14t
    return 0;
}

//�½������м���
int Elevator::Down_SlowDown()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����������С�" << "���ڼ���..." << endl;
    T.wait(23);//�����½�������Ҫ23t
    return 0;
}

//���ݾ�ֹ
int Elevator::Elv_Stop()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "�����ݾ�ֹ��" << "����������¥���ǣ�" << nowfloor << endl;
    if (moved)
    {
        now_stop = clock();//���ݾ�ֹ��ʼ��ʱ��
    }
    moved = 0;
    return 0;
}

//���ݹ���״̬�ı仯
int Elevator::Elv_Work()
{
    system("cls");//����
    E.Elv_Statues();//��ʾ����״̬

    int upflag = 0;//���������ı�־
    int downflag = 0;//�����½��ı�־
    int nowflag = nowfloor;//��������¥��

    if (req_up[nowflag] == 1)//��ǰ¥�������������
        upflag = 1;
    else//�ж������¥���Ƿ�������
    {
        for (nowflag = nowfloor + 1;nowflag <= MAXHEIGHT;nowflag++)
        {
            if (req_floor[nowflag] == 1 || req_up[nowflag] == 1 || req_down[nowflag] == 1 || (elv_psg[nowflag - 1].StackIsEmpty() == 0) || wait_up_psg[nowflag-1].QueueIsEmpty() == 0||wait_down_psg[nowflag-1].QueueIsEmpty()==0)
            {
                upflag = 1;
                break;
            }
        }
    }

    nowflag = nowfloor;
    if (req_down[nowflag] == 1)//��ǰ¥�������������
        downflag = 1;
    else
    {
        //�жϵ�ǰ¥����²�¥���Ƿ��������
        for (nowflag = nowfloor - 1;nowflag >= 1;nowflag--)
        {
            if (req_floor[nowflag] == 1 || req_up[nowflag] == 1 || req_down[nowflag] == 1 || (elv_psg[nowflag - 1].StackIsEmpty() == 0) || wait_up_psg[nowflag - 1].QueueIsEmpty() == 0 || wait_down_psg[nowflag - 1].QueueIsEmpty() == 0)
            {
                downflag = 1;
                break;
            }
        }
    }

    //��������״̬�ĵ��ݵĹ���״̬�Ŀ��ܱ仯
    if (nowstate == up)//��������������״̬
    {
        
        if (nowfloor == MAXHEIGHT || (upflag == 0 && downflag == 1))//����תΪ����״̬������
        {
            if (nowfloor == MAXHEIGHT && downflag == 0)
                E.Elv_Stop();//������߲㣬��û������������ֹ
            else
            {
                nowstate = down;
                E.Elv_SpendUp();
                E.Elv_Down();//���ݿ�ʼ�½�
            }
        }
        else//���ݲ���Ҫ�ı䷽��
        {
            if (downflag == 0 && upflag == 0)//���ݾ�ֹ����
            {
                E.Elv_Stop();
                nowstate = idle;
            }
            else
                E.Elv_Up();//���ݼ�������
        }
    }
    else if (nowstate == down)//���ݴ����½�״̬
    {
        if (nowfloor == 1 || (downflag == 0 && upflag == 1))//�ı�״̬
        {
            if (downflag == 0 && upflag == 0)
                E.Elv_Stop();
            else
            {
                nowstate = up;
                E.Elv_SpendUp();
                E.Elv_Up();
            }
        }
        else//���ı䷽��
        {
            if (downflag == 0 && upflag == 0)
            {
                Elv_Stop();
                nowstate = idle;//���ݿ���
            }
            else
                E.Elv_Down();
        }
    }
    else//���ݴ��ڿ���״̬
    {
        if (upflag == 0 && downflag == 0)
        {
            nowstate = idle;
            E.Elv_Stop();
        }
        else
        {
            if (upflag == 1)
            {
                nowstate = up;
                E.Elv_SpendUp();//���ݼ���
                E.Elv_Up();
            }
            else
            {
                nowstate = down;
                E.Elv_SpendUp();//���ݼ���
                E.Elv_Down();
            }
        }
    }
    return 0;
}

//���ݿ��ƺ���
int Elevator::Elv_Control()
{

    P.PsgGaveUp();

    //���ݿ�������
    if ((req_floor[nowfloor] != 0) || req_up[nowfloor] != 0 || req_down[nowfloor] != 0 || (elv_psg[nowfloor - 1].StackIsEmpty() == 0) || wait_up_psg[nowfloor - 1].QueueIsEmpty() == 0 || wait_down_psg[nowfloor - 1].QueueIsEmpty() == 0)
    {
        if ((psg_num == MAXPSG) && (elv_psg[nowfloor - 1].StackIsEmpty() == 1))//���ݵ������Ѵ�����Ҹò�û����Ҫ�����ݣ��򲻿���
        {
            //SlowDownFlag = 0;
            E.Elv_Work();
            //SlowDownFlag = 1;
        }
        else if ((nowstate == up && wait_up_psg[nowfloor - 1].QueueIsEmpty() == 1&&req_floor[nowfloor]==0) || (nowstate == down && wait_down_psg[nowfloor - 1].QueueIsEmpty() == 1&&req_floor[nowfloor]==0))//û��ͬ�����������迪��
        {
            E.Elv_Work();
        }
        else//����
        {
            //SlowDownFlag = 1;
            system("cls");
            E.Elv_Statues();

            if (nowstate == up)
                E.Up_SlowDown();
            else if(nowstate==down)
                E.Down_SlowDown();

            E.Elv_OpenDoor();//���ݿ���
            
            E.Elv_PsgOut();//�˿ͳ�����
            E.Elv_PsgIn();//�˿ͽ������

            E.Elv_Test();//���ݵȴ�40t

            E.Elv_CloseDoor();//���ݹ���
            //E.Elv_SpendUp();//���ݼ���
            E.Elv_Work();//���ݿ�ʼ����
            //if (nowstate == up || nowstate == down)
                //E.Elv_SpendUp();
            //SlowDownFlag = 0;
            
        }
    }
    else//���迪��
    {
        //E.Elv_SpendUp();//���ݼ���
        E.Elv_Work();
    }
        

    //���ݴ��ھ�ֹ״̬
    if (moved == 0)
    {
        req_floor[nowfloor] = 0;
        if ((clock() - now_stop) >= 300 * TIME)//���ݵȴ�ʱ�䳬��300t�����ص�һ��
        {
            if (nowfloor != 1)
            {
                req_floor[1] = 1;
            }
        }
    }
    /*
    if ((elv_psg[nowfloor - 1].StackIsEmpty() == 1) || wait_up_psg[nowfloor - 1].QueueIsEmpty() == 1 || wait_down_psg[nowfloor - 1].QueueIsEmpty() == 1)
    {
        req_up[nowfloor] = 0;
        req_down[nowfloor] = 0;
    }*/
    return 0;
}

int main(void)
{
    timesum=clock();
    //cout << timesum << endl;
    //system("pause");
    Init();
    while(1)
    {
        system("cls");
        E.Elv_Statues();
        while((clock()-delay)<nexttime)
        {
            if(next_psg_time>10)
                T.wait(10);
            E.Elv_Control();
        }
        system("cls");
        E.Elv_Statues();
        P.New_Psg();
    }
    return 0;
}
