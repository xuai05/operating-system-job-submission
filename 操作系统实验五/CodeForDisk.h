#ifndef _CODEFORDISK_H
#define _CODEFORDISK_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#define L 100 //�ܵ��߼�������
#define SIZE 511 //����10���ֽ�
#define sectorsPerTrack 30 //ÿ���ŵ���������
#define M 10//λͼ������
#define N 10//λͼ������

/******************************************************/
typedef struct ldisk
{	
	//����
    int C; 
    //��ͷ
	int H; 
    //����
	int B; 
	//�����е�����
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

int blockOfMap; //λͼ��ռ�Ŀ���

int **map = NULL; //λͼ

/******************************************************/
//��ʼ����������
int initDisk()
{
    int m = M;
    int n = N;
    //��ʼ������
    disk = (LDISK *)malloc(L * sizeof(LDISK));
    //����λͼ�ռ�
    map = (int **)malloc(m * sizeof(int *));
    for(int i = 0; i < m; i ++)
        map[i] = (int *)malloc(n * sizeof(int));
    //��ʼ��λͼ
    for(i = 0; i < m; i ++)
    {
        for(int j = 0; j < n; j ++)
        {
            map[i][j] = 0;
        }
    }
    //��λͼд�����
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
//��������ɺ���
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
    //������
    disk[i].B = i % sectorsPerTrack + 1;
    //�����
    disk[i].C = y >> 1;
    //��ͷ��
    disk[i].H = y & 1;
    strcpy(disk[i].content, p);
    return 0;
}
/******************************************************/
int read_block(int i, char *p)
{
    int y = i / sectorsPerTrack;
    //������
    disk[i].B = i % sectorsPerTrack + 1;
    //�����
    disk[i].C = y >> 1;
    //��ͷ��
    disk[i].H = y & 1;
    strcpy(p, disk[i].content);
    return 0;
}


#endif
