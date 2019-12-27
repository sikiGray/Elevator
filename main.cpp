/*
//#include<iostream>
//#include"Elevator.h"
//#include"LinkedQueue.h"
//#include"LinkedStack.h"
//#include "stdafx.h"
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <iomanip>
#include<stdlib.h>
#include "Elevator.h"
#include <process.h>
using namespace std;


void Init()
{
    for (int i = 1;i <= 5;++i)
    {
        req_up[i] = 0;
        req_down[i] = 0;
        req_floor[i] = 0;
    }
}

int main(void)
{
    timesum=clock();
    T.Init();
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
        P.New_Psg();
    }
    return 0;
}*/
