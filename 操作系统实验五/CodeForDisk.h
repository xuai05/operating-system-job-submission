#ifndef _CODEFORDISK_H
#define _CODEFORDISK_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#define L 100 //总的逻辑扇区数
#define SIZE 511 //扇区10个字节
#define sectorsPerTrack 30 //每个磁道的扇区数
#define M 10//位图的行数
#define N 10//位图的列数

/******************************************************/
typedef struct ldisk
{	
	//柱面
    int C; 
    //磁头
	int H; 
    //扇区
	int B; 
	//扇区中的内容
    char content[SIZE + 1]; 

}LDISK;

/******************************************************/

extern int **map;

extern LDISK *disk;

extern int blockOfMap;

int initDisk();

int read_block(int i, char *p);

int write_block(int i, char *p);

int createRandomNUmber(int start, int size);

LDISK *disk;

int blockOfMap; //位图所占的块数

int **map = NULL; //位图

/******************************************************/
//初始化磁盘序列
int initDisk()
{
    int m = M;
    int n = N;
    //初始化磁盘
    disk = (LDISK *)malloc(L * sizeof(LDISK));
    //申请位图空间
    map = (int **)malloc(m * sizeof(int *));
    for(int i = 0; i < m; i ++)
        map[i] = (int *)malloc(n * sizeof(int));
    //初始化位图
    for(i = 0; i < m; i ++)
    {
        for(int j = 0; j < n; j ++)
        {
            map[i][j] = 0;
        }
    }
    //将位图写入磁盘
    char map_char[M][N];

    for(i = 0; i < m; i ++)
    {
        for(int j = 0; j < n; j ++)
        {
            map_char[i][j] = (char) (map[i][j] + '0');
        }
    }

    int sizeOfMap = m * n * sizeof(char);

    if(sizeOfMap % SIZE > 0)
        blockOfMap = sizeOfMap / SIZE + 1;
    else
        blockOfMap = sizeOfMap / SIZE;

    int d = 0;
    int c = 0;
    for(int a = 0; a < m; a ++)
    {
        for(int b = 0; b < m; b ++)
        {
            strcpy(&disk[d].content[c], &map_char[a][b]);
            c ++;
            if(c == SIZE - 1)
            {
                d ++;
                c = 0;
            }
        }
    }
    return 0;
}
/******************************************************/
//随机数生成函数
int createRandomNUmber(int start, int size)
{
    srand((unsigned int )clock());
    
	int num = (int)(start + (size * (rand() / (RAND_MAX + 1.0))));
    
	return num;
}
/******************************************************/
int write_block(int i, char *p)
{
    int y = i / sectorsPerTrack;
    //扇区号
    disk[i].B = i % sectorsPerTrack + 1;
    //柱面号
    disk[i].C = y >> 1;
    //磁头号
    disk[i].H = y & 1;
    strcpy(disk[i].content, p);
    return 0;
}
/******************************************************/
int read_block(int i, char *p)
{
    int y = i / sectorsPerTrack;
    //扇区号
    disk[i].B = i % sectorsPerTrack + 1;
    //柱面号
    disk[i].C = y >> 1;
    //磁头号
    disk[i].H = y & 1;
    strcpy(p, disk[i].content);
    return 0;
}


#endif
