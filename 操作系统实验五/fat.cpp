// fat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

#include "CodeForDisk.h"
#include "CodeForFiles.h"
#include "CodeForDirectory.h"

int main(int argc, char* argv[])
{
    initDisk();
    
	initDic();

	int n;
	int res;
    int len;

    char name[28];

    char str[512];
    
	FILES* f;

	printf("\n");
    printf("********************************\n");
	printf("欢迎来到文件系统，功能显示如下：\n");

	printf("\t 0. 退出系统\n");
	printf("\t 1. 文件列表\n");
    printf("\t 2. 创建文件\n");
    printf("\t 3. 删除文件\n");
    printf("\t 4. 打开文件\n");
    printf("\t 5. 关闭文件\n");
    printf("\t 6. 读取文件\n");
    printf("\t 7. 写入文件\n");
    printf("\t 8. 移动指针\n");
      
    printf("********************************\n");
    //printf("\n");

    while(1) {

		//对应输入不合法的情况
		n = 9;
      
        printf("\n请选择功能：");		
       
		scanf("%d", &n);
        
		switch (n) 
		{
            case 0:
                printf("退出成功！\n");
                return 0;
			case 1:     
				//显示所有文件
                showDictionary();
                break;          
			case 2:     
				//创建文件
                printf("请输入文件名:");
                scanf("%s", name);
                create(name);
                break;
            case 3:     
				//删除文件
                printf("请输入文件名:");
                scanf("%s", name);
                res = destroy(name);
                break;
            case 4:     
				//打开文件
                printf("请输入文件名:");
                scanf("%s", name);
                f = open(name);
                if(f != NULL)
                {
                    printf("%s打开成功！\n",name);
                }
                break;
            case 5:     
				//关闭文件
                printf("请输入文件名:");
                scanf("%s", name);
                f = open(name);
                if(f == NULL)
                {
                    break;
                }
                close(f);
                break;
            case 6:     
				//读文件
                printf("请输入文件名:");
                scanf("%s", name);
                f = open(name);

                if(f == NULL)
                {
                    break;
                }
                printf("请输入读取长度:");
                scanf("%d", &len);
                str[0] = '\0';
                f = read(f, str, len);
                if(f == NULL)
                {
                    printf("长度越界\n");
                }
                printf("%s\n", str);

                break;
            case 7:     
				//写文件
                printf("请输入文件名:");
                scanf("%s", name);
                f = open(name);

                if(f == NULL)
                {
                    break;
                }
                printf("请输入写入内容:");
                scanf("%s", str);
                printf("请输入写入长度:");
                scanf("%d", &len);
                f = write(f, str, len);

                break;
            case 8:     
				//移动文件指针
                printf("请输入文件名:");
                scanf("%s", name);
                
				f = open(name);

                if(f == NULL)
                {
                    break;
                }

                printf("请输入移动位置:");
                
				scanf("%d", &len);
                
				f = lseek(f, len);

                if(f == NULL)
                {
                    break;
                }
                break;            

            default:
				break;
        }

		fflush(stdin);
    }
}

