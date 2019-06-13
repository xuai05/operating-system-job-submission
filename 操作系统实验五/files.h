#ifndef _CODEFORFILES_H
#define _CODEFORFILES_H

#include "disk.h"
#include "directory.h"

typedef struct files
{
	//文件编号
    int number; 
	//文件名
    char *filename; 
	//文件大小
    int size; 
	//文件偏移指针
    int pos; 
	//3个直接地址
    INDIRECT *addr[3]; 
	//存放文件中的所有内容
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
        printf("文件名已存在!\n");
        return NULL;
    }

    int a = M;

    int start = K;

    int size = L - K;

    countOfFiles ++;
    // 生成随机数
    int blockNumber = createRandomNUmber(start, size);
    // 查询位图
    while(map[blockNumber / a][blockNumber % a] == 1)
	{
        blockNumber = createRandomNUmber(start, size);
	}
    // 置位图为1
    map[blockNumber / a][blockNumber % a] = 1;
    // 建立目录
    createDirectory(filename, blockNumber);
    
	printf("成功创建!\n");
    
	return 0;
}
/******************************************************/
FILES *open(char *filename)
{
    DIC *dic = dicHead;
	// 缓冲区
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
        printf("文件不存在!\n");
        return NULL;
    }

	// 打开文件
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
    
	//将磁盘中的内容读到file中   
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
    //释放文件名
    if(file->filename != NULL)
    {
        free(file->filename);
        
		file->filename = NULL;
    }
    //释放文件内容
    if(file->content != NULL)
    {
        free(file->content);
        
		file->content = NULL;
    }
    //释放file指针
    free(file);
    
	printf("成功关闭!\n");
    
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
        printf("文件不存在!\n");
        return -1;
    }

    //删除文件
    int blockNumber = dic->index1->size / SIZE;
    
	if(dic->index1->size % SIZE > 0)
	{
        blockNumber ++;
	}
    //删除所有块里的元素
    for(i = 0; i < blockNumber; i ++)
    {
        write_block(dic->index1->addr[i]->diskNum, "\0");
    }
    //删除目录
    destoryDirectory(filename);
    
	countOfFiles --;

	printf("成功删除!\n");

    return 0;
}
/******************************************************/
FILES *read(FILES *file, char *mem_area, int count)
{
    char buffer[512] = ""; //缓冲区
    
	if((count + file->pos) > file->size)
        return NULL; //越界错误
    
	int a = count / SIZE;
    
	for(int i = 0; i < a; i ++)
    {
        memcpy(buffer, &file->content[file->pos + i * SIZE], SIZE * sizeof(char));
        strcpy(&mem_area[i * SIZE], buffer);
    }
    
	memcpy(buffer, &file->content[file->pos + a * SIZE], (count % SIZE) * sizeof(char));
    
	strcpy(&mem_area[a * SIZE], buffer);
    
	file->pos = file->pos + count;
    
	printf("成功读入!\n");
    return file;
}
/******************************************************/
FILES *write (FILES *file, char *mem_area, int count)
{
    DIC *dic = dicHead;
    
	char *buffer = NULL; //缓冲区
    
	buffer = (char *)malloc(SIZE * sizeof(char));
    
	if(file->pos + count > 3 * SIZE)
        return NULL; //越界

    //清除原先磁盘扇区中的数据
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
        //改位图
        map[file->addr[i]->diskNum / m][file->addr[i]->diskNum % m] = 0;
    }
	//找到目录
    for(i = 0; i < countOfFiles; i ++)
    {
        if(dic->index1->number == file->number)
            break;
        dic = dic->next;
    }
    //更改目录中的内容
    for(i = 1; i < blocknumber; i ++)
        dic->index1->addr[i]->diskNum= 0;
    for(i = 0; i < 3; i ++)
        dic->index1->addr[i]->count = 0;
    for(i = 1; i < 3; i ++)
        dic->index1->addr[i]->diskNum = -1;
    //更改file指针中文件的内容
    file->size = file->pos + count;
    //重新分配空间
    char *s;
    
	s = (char *)malloc(strlen(file->content) *sizeof(char));
    
	memcpy(s, file->content, strlen(file->content) *sizeof(char));
    
	file->content = (char *)realloc(file->content, file->size * sizeof(char));
    
	memcpy(file->content, s, sizeof(file->pos) *sizeof(char));
    	
	memcpy(&file->content[file->pos], mem_area, count * sizeof(char));
    
	//将file中的内容通过buffer写入磁盘
    blocknumber = file->size / SIZE;
    
	if(file->size % SIZE > 0)
        blocknumber ++;
    //生成随机的磁盘扇区块
    int start = K;
    
	int size = L - K;
    
	for(i = 1; i < blocknumber; i ++)
    {
        file->addr[i]->diskNum = createRandomNUmber(start, size);
        
		while(map[file->addr[i]->diskNum / m][file->addr[i]->diskNum % m] != 0)
            file->addr[i]->diskNum = createRandomNUmber(start, size);
    }
    //从buffer中写入扇区
    for(i = 0; i < blocknumber - 1; i ++)
    {
        //存入缓冲区
        memcpy(buffer, &file->content[i * SIZE], (SIZE) * sizeof(char));
        //缓冲区存入磁盘
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
	//写回目录
    for(i = 0; i < 3; i ++)
	{
        memcpy(dic->index1->addr[i], file->addr[i], sizeof(INDIRECT));
    }
	dic->index1->size = file->size;
    
	file->pos = file->size;
    
	printf("成功写入!\n");
    
	free(buffer);
    
	return file;
}
/******************************************************/
//向后移动pos个单位
FILES *lseek(FILES* file, int pos)
{
    file->pos += pos;
    
	return file;
}

#endif