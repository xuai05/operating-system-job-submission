#ifndef _CODEFORFILES_H
#define _CODEFORFILES_H

#include "disk.h"
#include "directory.h"

typedef struct files
{
	//�ļ����
    int number; 
	//�ļ���
    char *filename; 
	//�ļ���С
    int size; 
	//�ļ�ƫ��ָ��
    int pos; 
	//3��ֱ�ӵ�ַ
    INDIRECT *addr[3]; 
	//����ļ��е���������
    char *content; 

}FILES;

/******************************************************/

int create(char *filename);

int destroy(char *filename);

FILES *open(char *filename);

int close(FILES *file);

FILES *read(FILES *file, char *mem_area, int count);

FILES *write(FILES *file, char *mem_area, int count);

FILES *lseek(FILES* file, int pos);

int countOfFiles = 0;

/******************************************************/
int create(char *filename)
{
    DIC *dic = dicHead;

    int flag = 0;

    for(int i = 0; i < countOfFiles; i ++)
    {
        if(strcmp(dic->filename, filename) == 0)
        {
            flag = 1;
            break;
        }

        dic = dic->next;
    }

    if(flag == 1)
    {
        printf("�ļ����Ѵ���!\n");
        return NULL;
    }

    int a = M;

    int start = K;

    int size = L - K;

    countOfFiles ++;
    // ���������
    int blockNumber = createRandomNUmber(start, size);
    // ��ѯλͼ
    while(map[blockNumber / a][blockNumber % a] == 1)
	{
        blockNumber = createRandomNUmber(start, size);
	}
    // ��λͼΪ1
    map[blockNumber / a][blockNumber % a] = 1;
    // ����Ŀ¼
    createDirectory(filename, blockNumber);
    
	printf("�ɹ�����!\n");
    
	return 0;
}
/******************************************************/
FILES *open(char *filename)
{
    DIC *dic = dicHead;
	// ������
    char buffer[512] = ""; 
    
	int flag = 0;
    
	for(int i = 0; i < countOfFiles; i ++)
    {
        if(strcmp(dic->filename, filename) == 0)
        {
            flag = 1;
            break;
        }

        dic = dic->next;
    }

    if(flag == 0)
    {
        printf("�ļ�������!\n");
        return NULL;
    }

	// ���ļ�
    FILES *file = NULL;
    
	file = (FILES *)malloc(sizeof(FILES));
    
	file->number = dic->index1->number;
    
	for(i = 0; i < 3; i ++)
	{
        file->addr[i] = (INDIRECT *)malloc(sizeof(INDIRECT));
	}
    for(i = 0; i < 3; i ++)
	{
        memcpy(file->addr[i], dic->index1->addr[i], sizeof(INDIRECT));
	}
    file->size = dic->index1->size;
    
	file->filename = (char *)malloc(strlen(filename) * sizeof(char));
    
	memcpy(file->filename, filename, strlen(filename));
    
	file->pos = 0;
    
	//�������е����ݶ���file��   
	int block = file->size / SIZE;
    
	int offset = file->size % SIZE;
    
	file->content = (char *)malloc(file->size * sizeof(char));
    
	if(offset > 0)
	{
        block ++;
    }
	for(i = 0; i < block; i ++)
    {
        read_block(dic->index1->addr[i]->diskNum, buffer);
        
		strcpy(&file->content[i * SIZE], buffer);
    }

    return file;
}
/******************************************************/
int close(FILES *file)
{
    for(int i = 0; i < 3; i ++)
        free(file->addr[i]);
    for(i = 0; i < 3; i ++)
        file->addr[i] = NULL;
    //�ͷ��ļ���
    if(file->filename != NULL)
    {
        free(file->filename);
        
		file->filename = NULL;
    }
    //�ͷ��ļ�����
    if(file->content != NULL)
    {
        free(file->content);
        
		file->content = NULL;
    }
    //�ͷ�fileָ��
    free(file);
    
	printf("�ɹ��ر�!\n");
    
	return 0;
}
/******************************************************/
int destroy(char *filename)
{
    DIC *dic = dicHead;

    int flag = 0;
    for(int i = 0; i < countOfFiles; i ++)
    {
        if(strcmp(dic->filename, filename) == 0)
        {
            flag = 1;
            break;
        }

        dic = dic->next;
    }

    if(flag == 0)
    {
        printf("�ļ�������!\n");
        return -1;
    }

    //ɾ���ļ�
    int blockNumber = dic->index1->size / SIZE;
    
	if(dic->index1->size % SIZE > 0)
	{
        blockNumber ++;
	}
    //ɾ�����п����Ԫ��
    for(i = 0; i < blockNumber; i ++)
    {
        write_block(dic->index1->addr[i]->diskNum, "\0");
    }
    //ɾ��Ŀ¼
    destoryDirectory(filename);
    
	countOfFiles --;

	printf("�ɹ�ɾ��!\n");

    return 0;
}
/******************************************************/
FILES *read(FILES *file, char *mem_area, int count)
{
    char buffer[512] = ""; //������
    
	if((count + file->pos) > file->size)
        return NULL; //Խ�����
    
	int a = count / SIZE;
    
	for(int i = 0; i < a; i ++)
    {
        memcpy(buffer, &file->content[file->pos + i * SIZE], SIZE * sizeof(char));
        strcpy(&mem_area[i * SIZE], buffer);
    }
    
	memcpy(buffer, &file->content[file->pos + a * SIZE], (count % SIZE) * sizeof(char));
    
	strcpy(&mem_area[a * SIZE], buffer);
    
	file->pos = file->pos + count;
    
	printf("�ɹ�����!\n");
    return file;
}
/******************************************************/
FILES *write (FILES *file, char *mem_area, int count)
{
    DIC *dic = dicHead;
    
	char *buffer = NULL; //������
    
	buffer = (char *)malloc(SIZE * sizeof(char));
    
	if(file->pos + count > 3 * SIZE)
        return NULL; //Խ��

    //���ԭ�ȴ��������е�����
    int m = M;
    
	int blocknumber = file->size / SIZE;
   
	if((file->size % SIZE) > 0)
	{
        blocknumber ++;
    }
	for(int i = 0; i < blocknumber; i ++)
	{
        strcpy(disk[file->addr[i]->diskNum].content, "\0");
    }
	for(i = 1; i < blocknumber; i ++)
	{
        //��λͼ
        map[file->addr[i]->diskNum / m][file->addr[i]->diskNum % m] = 0;
    }
	//�ҵ�Ŀ¼
    for(i = 0; i < countOfFiles; i ++)
    {
        if(dic->index1->number == file->number)
            break;
        dic = dic->next;
    }
    //����Ŀ¼�е�����
    for(i = 1; i < blocknumber; i ++)
        dic->index1->addr[i]->diskNum= 0;
    for(i = 0; i < 3; i ++)
        dic->index1->addr[i]->count = 0;
    for(i = 1; i < 3; i ++)
        dic->index1->addr[i]->diskNum = -1;
    //����fileָ�����ļ�������
    file->size = file->pos + count;
    //���·���ռ�
    char *s;
    
	s = (char *)malloc(strlen(file->content) *sizeof(char));
    
	memcpy(s, file->content, strlen(file->content) *sizeof(char));
    
	file->content = (char *)realloc(file->content, file->size * sizeof(char));
    
	memcpy(file->content, s, sizeof(file->pos) *sizeof(char));
    	
	memcpy(&file->content[file->pos], mem_area, count * sizeof(char));
    
	//��file�е�����ͨ��bufferд�����
    blocknumber = file->size / SIZE;
    
	if(file->size % SIZE > 0)
        blocknumber ++;
    //��������Ĵ���������
    int start = K;
    
	int size = L - K;
    
	for(i = 1; i < blocknumber; i ++)
    {
        file->addr[i]->diskNum = createRandomNUmber(start, size);
        
		while(map[file->addr[i]->diskNum / m][file->addr[i]->diskNum % m] != 0)
            file->addr[i]->diskNum = createRandomNUmber(start, size);
    }
    //��buffer��д������
    for(i = 0; i < blocknumber - 1; i ++)
    {
        //���뻺����
        memcpy(buffer, &file->content[i * SIZE], (SIZE) * sizeof(char));
        //�������������
        write_block(file->addr[i]->diskNum, buffer);
    }
    if(count % SIZE > 0)
    {
        strcpy(buffer, &file->content[(blocknumber - 1) * SIZE]);
        write_block(file->addr[blocknumber - 1]->diskNum, buffer);
    }
    else if(count % SIZE == 0)
    {
        memcpy(buffer, &file->content[(blocknumber - 1) * SIZE], SIZE * sizeof(char));
        write_block(file->addr[blocknumber - 1]->diskNum, buffer);
    }
    for(i = 0; i < blocknumber - 1; i ++)
	{
        file->addr[i]->count = SIZE;
    }
	if(file->size == SIZE)
	{
        file->addr[blocknumber - 1]->count = file->size;
    }
	else
	{
        file->addr[blocknumber - 1]->count = file->size % SIZE;
    }
	//д��Ŀ¼
    for(i = 0; i < 3; i ++)
	{
        memcpy(dic->index1->addr[i], file->addr[i], sizeof(INDIRECT));
    }
	dic->index1->size = file->size;
    
	file->pos = file->size;
    
	printf("�ɹ�д��!\n");
    
	free(buffer);
    
	return file;
}
/******************************************************/
//����ƶ�pos����λ
FILES *lseek(FILES* file, int pos)
{
    file->pos += pos;
    
	return file;
}

#endif