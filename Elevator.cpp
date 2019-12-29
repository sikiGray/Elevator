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

/*********时间类的函数的定义********/


//在等待时间内的操作
int Time::wait(long t)
{
    clock_t end;
    end = clock() - delay;
    while (clock() < end + delay + t * TIME)
    {
        if ((clock() - delay >= nexttime))//在等待时间内有乘客到来
        {
            cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯状态】" << "状态持续中..." << endl;
            P.New_Psg();//新增乘客
        }
            
    }
    return 0;
}

//暂停计时函数（等待用户输入）
void Time::TimePause()
{
    time_save.Push(clock());//保存程序运行到现在经历的时间
    timesum = clock();//记录程序运行到现在经历过的时间
}

//恢复计时函数
void Time::TimeResume()
{
    delay += clock() - time_save.Pop();//计算输入导致的延时
    //time_save.pop();
}



/********************乘客类的函数定义*******************/

//乘客进入电梯
void Psg::InElevator()
{
    elv_psg[outfloor - 1].Push(*this);//将该乘客压入出电梯楼层的电梯栈中
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【乘客】" << ID << "号乘客从" << infloor << "楼进入电梯。" << endl;
    req_floor[outfloor] = 1;//标志要出楼层存在请求
}

//乘客在所在楼层等待
void Psg::onwait()
{
    //wait_psg[infloor - 1].EnQueue(*this);
    if (this->infloor > this->outfloor)
        wait_down_psg[infloor - 1].EnQueue(*this);
    else
        wait_up_psg[infloor - 1].EnQueue(*this);
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【乘客】" << ID << "号乘客进入" << infloor << "楼的等待队列。" << endl;
}

//乘客出电梯
void Psg::OutElevator()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【乘客】" << ID << "号乘客出电梯。" << endl;
}

//乘客因等待时间过长而放弃
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
                cout << (now - delay) / TIME << "," << nexttime / TIME << "【乘客】" << n.ID << "号乘客因等待时间过长离开等待队列" << endl;
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
                cout << (now - delay) / TIME << "," << nexttime / TIME << "【乘客】" << n.ID << "号乘客因等待时间过长离开等待队列" << endl;
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

//乘客信息的输入
int Psg::Psg_Infm()
{
    clock_t now = clock();
    //cout << now << endl;
    int timeflag = 0;//时间恢复的标志
    cout << "【新增乘客】请输入：所在楼层、目标楼层、下一乘客到来的时间间隔" << endl;
    if (timeflag == 0)
        T.TimePause();//暂停计时
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
        //检测输入的合法性
        if (m.infloor >= MAXHEIGHT+1 || m.infloor <= 0 || m.outfloor >= MAXHEIGHT+1 || m.outfloor <= 0 || m.infloor == m.outfloor)
        {
            cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【输入有误】" << "输入楼层错误！请重新输入" << endl;
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
        T.TimeResume();//恢复计时
    timeflag = 0;
    return 0;
}

//新增一名乘客     
int Psg::New_Psg()
{
    m.ID = sum;
    sum++;
    P.Psg_Infm();//记录乘客信息
    
    //if (nexttime > clock() - delay)
    //{
        /***?????????????????????***/
     //   nexttime += nexttime + next_psg_time * TIME;
    //}
    //else//计算下一个乘客到来的时刻
   // {
        nexttime = clock() - delay + next_psg_time * TIME;
    //}
    //判断乘客是要上楼还是下楼
    if (m.infloor > m.outfloor)//下楼
    {
        req_down[m.infloor] = 1;//记录存在下楼请求的楼层
    }
    else//上楼
    {
        req_up[m.infloor] = 1;//记录存在上楼请求的楼层
    }
    m.onwait();//乘客进入等待队列
    //cout << wait_psg[0].Front().waitBegin << endl;
    //system("pause");
    return 0;
}


/*********************电梯类的函数定义****************/
//显示电梯状态函数
int Elevator::Elv_Statues()
{
    int i;

    cout << "******************************** 电梯状态信息 *********************************" << endl;
    cout << "**********************-----------------------------------**********************" << endl;
    cout << "************-------------------- 现处楼层：" << nowfloor << " --------------------**************" << endl;

    cout << "                            丨------------------丨                             " << endl;
    cout << "                            丨 前往各楼层的乘客 丨                             " << endl;
    cout << "                            丨------------------丨                             " << endl;
    for (i = MAXHEIGHT;i >= 1;i--)
    {
        cout << "                            丨";
        if (i == nowfloor)
            cout << "  ◆";
        else
            cout << "    ";
        cout << " 第" << i << "层：";

        /**-------------------------**/
        elv_psg[i - 1].StackTranverse();//遍历输出电梯栈
        /**-------------------------**/
        cout << "      丨"<<endl;
        
    }
    cout << endl;
    cout << "                            丨------------------丨                             " << endl;
    cout << "                            丨 各楼层等待的乘客 丨                             " << endl;
    cout << "                            丨------------------丨                             " << endl;
    for (i = MAXHEIGHT;i >= 1;i--)
    {
        cout << "                            丨";
        if (i == nowfloor)
            cout << "  ◆";
        else
            cout << "    ";
        cout << " 第" << i << "层：";
        /**-------------------------**/
        wait_up_psg[i - 1].QueueTranverse();//遍历输出楼层的等待队列
        wait_down_psg[i - 1].QueueTranverse();
        /**-------------------------**/
        cout << "      丨" << endl;
    }
    cout << "-------------------------------------------------------------------------------" << endl;
    return 0;
}

//电梯开门
int Elevator::Elv_OpenDoor()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯运行中】" << "正在开门..." << endl;
    T.wait(20);
    return 0;
}

//电梯关门
int Elevator::Elv_CloseDoor()
{
    
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯运行中】" << "正在关门..." << endl;
    T.wait(20);
    return 0;
}

//电梯测试
int Elevator::Elv_Test()
{
        
        cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯运行中】" << "正在等待..." << endl;
        T.wait(40);
        return 0;
}

//乘客进入电梯
int Elevator::Elv_PsgIn()
{
    if (nowstate == idle || nowstate == up)
    {
        //当前楼层的等待队列不为空，且电梯未满
        while (!wait_up_psg[nowfloor - 1].QueueIsEmpty() && psg_num < MAXPSG)
        {
            n = wait_up_psg[nowfloor - 1].DeQueue();//取队头
            T.wait(25);//一个人进入需要25t
            n.InElevator();//乘客进入电梯，同时将乘客压入电梯栈
            psg_num++;
        }
    }
    else
    {
        while (!wait_down_psg[nowfloor - 1].QueueIsEmpty() && psg_num < MAXPSG)
        {
            n = wait_down_psg[nowfloor - 1].DeQueue();//取队头
            T.wait(25);//一个人进入需要25t
            n.InElevator();//乘客进入电梯，同时将乘客压入电梯栈
            psg_num++;
        }
    }

    return 0;
}

//乘客出电梯
int Elevator::Elv_PsgOut()
{
    //电梯栈不为空
    while (!elv_psg[nowfloor - 1].StackIsEmpty())
    {
        n = elv_psg[nowfloor - 1].Pop();
        T.wait(25);//每个人出电梯要25t
        n.OutElevator();
        psg_num--;
    }
    return 0;
}

//电梯上升
int Elevator::Elv_Up()
{

    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯运行中】" << "正在上升..." << endl;
    T.wait(51);//电梯上升需要51t
    req_floor[nowfloor] = 0;//该层楼的出电梯请求已处理完毕，将标志置为0
    nowfloor++;

    req_up[nowfloor - 1] = 0;//上升请求已处理完毕

    /*if (SlowDownFlag == 1)
    {
        if (nowstate == up)
            E.Up_SlowDown();
        else if (nowstate == down)
            E.Down_SlowDown();
    }*/

    system("cls");
    E.Elv_Statues();
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯运行中】" << "现在上升到第" << nowfloor << "层" << endl;
   
    //req_floor[nowfloor] = 0;

    moved= 1;
    return 0;
}

//电梯下降
int Elevator::Elv_Down()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯运行中】" << "正在下降..." << endl;
    T.wait(61);//下降需要61t
    req_floor[nowfloor] = 0;
    nowfloor--;

    req_down[nowfloor + 1] = 0;//下降请求已处理完毕

    /*if (SlowDownFlag == 1)
    {
        if (nowstate == up)
            E.Up_SlowDown();
        else if (nowstate == down)
            E.Down_SlowDown();
    }*/

    system("cls");
    E.Elv_Statues();
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯运行中】" << "现在下降到了第" << nowfloor << "层" << endl;

    //req_floor[nowfloor] = 0;
    moved= 1;
    return 0;
}
//电梯加速
int Elevator::Elv_SpendUp()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯运行中】" << "正在加速..." << endl;
    T.wait(15);//电梯加速需要15t
    return 0;
}

//上升过程中减速
int Elevator::Up_SlowDown()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯运行中】" << "正在减速..." << endl;
    T.wait(14);//电梯上升减速需要14t
    return 0;
}

//下降过程中减速
int Elevator::Down_SlowDown()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯运行中】" << "正在减速..." << endl;
    T.wait(23);//电梯下降减速需要23t
    return 0;
}

//电梯静止
int Elevator::Elv_Stop()
{
    cout << (clock() - delay) / TIME << "," << nexttime / TIME << "【电梯静止】" << "现在所处的楼层是：" << nowfloor << endl;
    if (moved)
    {
        now_stop = clock();//电梯静止开始的时刻
    }
    moved = 0;
    return 0;
}

//电梯工作状态的变化
int Elevator::Elv_Work()
{
    system("cls");//清屏
    E.Elv_Statues();//显示电梯状态

    int upflag = 0;//电梯上升的标志
    int downflag = 0;//电梯下降的标志
    int nowflag = nowfloor;//电梯所在楼层

    if (req_up[nowflag] == 1)//当前楼层存在向上请求
        upflag = 1;
    else//判断上面的楼层是否有请求
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
    if (req_down[nowflag] == 1)//当前楼层存在向下请求
        downflag = 1;
    else
    {
        //判断当前楼层的下层楼层是否存在请求
        for (nowflag = nowfloor - 1;nowflag >= 1;nowflag--)
        {
            if (req_floor[nowflag] == 1 || req_up[nowflag] == 1 || req_down[nowflag] == 1 || (elv_psg[nowflag - 1].StackIsEmpty() == 0) || wait_up_psg[nowflag - 1].QueueIsEmpty() == 0 || wait_down_psg[nowflag - 1].QueueIsEmpty() == 0)
            {
                downflag = 1;
                break;
            }
        }
    }

    //处于上升状态的电梯的工作状态的可能变化
    if (nowstate == up)//电梯正处于上升状态
    {
        
        if (nowfloor == MAXHEIGHT || (upflag == 0 && downflag == 1))//电梯转为向下状态的条件
        {
            if (nowfloor == MAXHEIGHT && downflag == 0)
                E.Elv_Stop();//到达最高层，且没有向下请求则静止
            else
            {
                nowstate = down;
                E.Elv_SpendUp();
                E.Elv_Down();//电梯开始下降
            }
        }
        else//电梯不需要改变方向
        {
            if (downflag == 0 && upflag == 0)//电梯静止条件
            {
                E.Elv_Stop();
                nowstate = idle;
            }
            else
                E.Elv_Up();//电梯继续上升
        }
    }
    else if (nowstate == down)//电梯处于下降状态
    {
        if (nowfloor == 1 || (downflag == 0 && upflag == 1))//改变状态
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
        else//不改变方向
        {
            if (downflag == 0 && upflag == 0)
            {
                Elv_Stop();
                nowstate = idle;//电梯空闲
            }
            else
                E.Elv_Down();
        }
    }
    else//电梯处于空闲状态
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
                E.Elv_SpendUp();//电梯加速
                E.Elv_Up();
            }
            else
            {
                nowstate = down;
                E.Elv_SpendUp();//电梯加速
                E.Elv_Down();
            }
        }
    }
    return 0;
}

//电梯控制函数
int Elevator::Elv_Control()
{

    P.PsgGaveUp();

    //电梯开门条件
    if ((req_floor[nowfloor] != 0) || req_up[nowfloor] != 0 || req_down[nowfloor] != 0 || (elv_psg[nowfloor - 1].StackIsEmpty() == 0) || wait_up_psg[nowfloor - 1].QueueIsEmpty() == 0 || wait_down_psg[nowfloor - 1].QueueIsEmpty() == 0)
    {
        if ((psg_num == MAXPSG) && (elv_psg[nowfloor - 1].StackIsEmpty() == 1))//电梯的人数已达最大，且该层没有人要出电梯，则不开门
        {
            //SlowDownFlag = 0;
            E.Elv_Work();
            //SlowDownFlag = 1;
        }
        else if ((nowstate == up && wait_up_psg[nowfloor - 1].QueueIsEmpty() == 1&&req_floor[nowfloor]==0) || (nowstate == down && wait_down_psg[nowfloor - 1].QueueIsEmpty() == 1&&req_floor[nowfloor]==0))//没有同方向请求，无需开门
        {
            E.Elv_Work();
        }
        else//开门
        {
            //SlowDownFlag = 1;
            system("cls");
            E.Elv_Statues();

            if (nowstate == up)
                E.Up_SlowDown();
            else if(nowstate==down)
                E.Down_SlowDown();

            E.Elv_OpenDoor();//电梯开门
            
            E.Elv_PsgOut();//乘客出电梯
            E.Elv_PsgIn();//乘客进入电梯

            E.Elv_Test();//电梯等待40t

            E.Elv_CloseDoor();//电梯关门
            //E.Elv_SpendUp();//电梯加速
            E.Elv_Work();//电梯开始工作
            //if (nowstate == up || nowstate == down)
                //E.Elv_SpendUp();
            //SlowDownFlag = 0;
            
        }
    }
    else//无需开门
    {
        //E.Elv_SpendUp();//电梯加速
        E.Elv_Work();
    }
        

    //电梯处于静止状态
    if (moved == 0)
    {
        req_floor[nowfloor] = 0;
        if ((clock() - now_stop) >= 300 * TIME)//电梯等待时间超过300t，返回第一层
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
