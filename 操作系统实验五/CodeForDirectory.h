
#ifndef _CODEFORDIRECTORY_H
#define _CODEFORDIRECTORY_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#include "CodeForDisk.h"
#include "CodeForFiles.h"

#define K 10 //��������������¼Ŀ¼��Ϣ

//��ַ��
typedef struct indirect
{
    int diskNum; //�����߼�������
    int count; //ʹ�ù��ĳ���

}INDIRECT;

//�ļ���ʶ��
typedef struct index
{
    int number; //�ļ���ʶ����
    int size; //��С
    INDIRECT *addr[3]; //3��ֱ�ӵ�ַ

}INDEX;

typedef struct directory
{
    char *filename; //�ļ���
    INDEX *index1;//�ļ�����
    struct directory *next; //ʹ��ѭ��������Ŀ¼��Ϣ
}DIC;

//Ŀ¼�Ĵ洢�ṹ
typedef struct directory1
{
    int number; //�ļ���ʶ����
    int size; //��С
    INDIRECT **addr; //Ŀ¼��ռ��ֱ�ӵ�ַ

}DIC1;

/******************************************************/

extern DIC1 *dic1; //Ŀ¼

extern DIC *dicHead; //Ŀ¼����ͷָ��

extern DIC *dicTail; //Ŀ¼����βָ��

extern int countOfFiles; //�ļ�����

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

    //Ŀ¼Խ��
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
    
	//��������
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

    //�ҵ�filename��Ӧ��Ŀ¼
    for(int i = 0; i < countOfFiles; i ++)
    {
        if(strcmp(dic->filename, filename) == 0)
            break;
        dic2 = dic;
        dic = dic->next;
    }

    //������ļ�ռ���˶�������
    int x = dic->index1->size;

    int y = x / SIZE;

    if(x % SIZE > 0)
        y ++;
    //�ͷ�����������Ϣ
    for(int j = 0; j < y; j ++)
        //�޸�λͼ
        map[dic->index1->addr[j]->diskNum / a][dic->index1->addr[j]->diskNum % a] = 0;
    for(i = 0; i < 3; i ++)
        free(dic->index1->addr[i]);
    //free(dic->index1);
    //�ͷ��ļ���
    //free(dic->filename);
    //�ͷ�Ŀ¼
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

		printf("��ǰϵͳ���ļ�!\n");
	}
    for(int i = 0; i < countOfFiles; i ++)
    {
        printf("�ļ���:%s\t", dic->filename);

        printf("�ļ���:%d\t", dic->index1->number);

        printf("�ļ���С:%d\t", dic->index1->size);

        int block = dic->index1->size / SIZE;

        if(block == 0 || dic->index1->size % SIZE)
            block ++;
        
		for(int j = 0; j < block; j ++)
        {
            printf("��ռ���̿��:");
            printf("%d\t", dic->index1->addr[j]->diskNum);
            printf("ռ�ÿռ��С:%d\t", dic->index1->addr[j]->count);
        }
        
		printf("\n");
        
		dic = dic->next;
    }
    return 0;
}
/******************************************************/

#endif
