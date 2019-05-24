#include "windows.h"
#include <conio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <stdio.h>
#include<iostream>
#include"time.h"
using namespace std;

/***************************************主要函数************************************************/
void FIFO();          //先进先出算法
void LRU();           //最近最久未使用算法
void OPT();// 最佳置换算法
void gClock(); //改进Clock算法
void PBA();   //PBA()算法
/***************************************主要函数************************************************/


/***************************************辅助函数************************************************/
void initialize();    //初始化相关数据结构
void createps();      //随机生成访问序列
void displayinfo();   //显示当前状态及缺页情况
void displayinfoPBA();
int  findpage();      //查找页面是否在内存
/***************************************辅助函数************************************************/