
#ifndef _CODEFORDIRECTORY_H
#define _CODEFORDIRECTORY_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#include "CodeForDisk.h"
#include "CodeForFiles.h"

#define K 10 //保留区，用来记录目录信息

//地址项
typedef struct indirect
{
    int diskNum; //磁盘逻辑扇区号
    int count; //使用过的长度

}INDIRECT;

//文件标识符
typedef struct index
{
    int number; //文件标识符号
    int size; //大小
    INDIRECT *addr[3]; //3个直接地址

}INDEX;

typedef struct directory
{
    char *filename; //文件名
    INDEX *index1;//文件索引
    struct directory *next; //使用循环链表储存目录信息
}DIC;

//目录的存储结构
typedef struct directory1
{
    int number; //文件标识符号
    int size; //大小
    INDIRECT **addr; //目录所占的直接地址

}DIC1;

/******************************************************/

extern DIC1 *dic1; //目录

extern DIC *dicHead; //目录链表头指针

extern DIC *dicTail; //目录链表尾指针

extern int countOfFiles; //文件总数

int initDic();

int createDirectory(char *filename, int blockNumber);

int destoryDirectory(char *filename);

int showDictionary();

DIC1 *dic1 = NULL;

DIC *dicHead = NULL;

DIC *dicTail = NULL;

/******************************************************/
int initDic()
{
    dic1 = (DIC1 *)malloc(sizeof(DIC1));
    
	dic1->number = 0;
    
	dic1->size = 0;
    
	dicHead = (DIC *) malloc(sizeof(DIC));
    
	dicTail = (DIC *) malloc(sizeof(DIC));

    return 0;
}
/******************************************************/
int createDirectory(char *filename, int blockNumber)
{
    int k = K;

    //目录越界
	if(countOfFiles * sizeof(DIC) + sizeof(dic1) > (k - blockOfMap) * SIZE)
        return -1; 
    
	DIC *dic = NULL;
    
	dic = (DIC *) malloc(countOfFiles * sizeof(DIC));
    
	dic->filename = (char *) malloc(strlen(filename) * sizeof(char));
    
	strcpy(dic->filename, filename);
    
	dic->index1 = (INDEX *)malloc(sizeof(INDEX));
    
	dic->index1->number = countOfFiles;
    
	dic->index1->size = 0;
    
	for(int i = 0; i < 3; i ++)
        dic->index1->addr[i] = (INDIRECT *)malloc(sizeof(INDIRECT));
    
	dic->index1->addr[0]->diskNum = blockNumber;
    
	dic->index1->addr[0]->count = 0;
   
	dic->next = (DIC *)malloc(sizeof(DIC));
    
	//生成链表
    if(countOfFiles == 1)
    {
        memcpy(dicHead, dic, sizeof(DIC));
        dicTail = dicHead;
        dicHead->next = dicTail;
        dicTail->next = dicHead;
        free(dic);
    } 
	else
    {
        dicTail->next = dic;
        dic->next = dicHead;
        dicTail = dic;
    }
    return 0;
}
/******************************************************/
int destoryDirectory(char *filename)
{
    DIC *dic = dicHead;
    DIC *dic2 = dicHead;
    int a = M;

    //找到filename对应的目录
    for(int i = 0; i < countOfFiles; i ++)
    {
        if(strcmp(dic->filename, filename) == 0)
            break;
        dic2 = dic;
        dic = dic->next;
    }

    //计算出文件占用了多少扇区
    int x = dic->index1->size;

    int y = x / SIZE;

    if(x % SIZE > 0)
        y ++;
    //释放所有扇区信息
    for(int j = 0; j < y; j ++)
        //修改位图
        map[dic->index1->addr[j]->diskNum / a][dic->index1->addr[j]->diskNum % a] = 0;
    for(i = 0; i < 3; i ++)
        free(dic->index1->addr[i]);
    //free(dic->index1);
    //释放文件名
    //free(dic->filename);
    //释放目录
    dic2->next = dic->next;

    dicHead = dic2->next;

    free(dic);

    return 0;
}
/******************************************************/
int showDictionary()
{
    DIC *dic = dicHead;

	if (countOfFiles == 0){

		printf("当前系统无文件!\n");
	}
    for(int i = 0; i < countOfFiles; i ++)
    {
        printf("文件名:%s\t", dic->filename);

        printf("文件号:%d\t", dic->index1->number);

        printf("文件大小:%d\t", dic->index1->size);

        int block = dic->index1->size / SIZE;

        if(block == 0 || dic->index1->size % SIZE)
            block ++;
        
		for(int j = 0; j < block; j ++)
        {
            printf("所占磁盘块号:");
            printf("%d\t", dic->index1->addr[j]->diskNum);
            printf("占用空间大小:%d\t", dic->index1->addr[j]->count);
        }
        
		printf("\n");
        
		dic = dic->next;
    }
    return 0;
}
/******************************************************/

#endif
