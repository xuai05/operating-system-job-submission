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
	printf("��ӭ�����ļ�ϵͳ��������ʾ���£�\n");

	printf("\t 0. �˳�ϵͳ\n");
	printf("\t 1. �ļ��б�\n");
    printf("\t 2. �����ļ�\n");
    printf("\t 3. ɾ���ļ�\n");
    printf("\t 4. ���ļ�\n");
    printf("\t 5. �ر��ļ�\n");
    printf("\t 6. ��ȡ�ļ�\n");
    printf("\t 7. д���ļ�\n");
    printf("\t 8. �ƶ�ָ��\n");
      
    printf("********************************\n");
    //printf("\n");

    while(1) {

		//��Ӧ���벻�Ϸ������
		n = 9;
      
        printf("\n��ѡ���ܣ�");		
       
		scanf("%d", &n);
        
		switch (n) 
		{
            case 0:
                printf("�˳��ɹ���\n");
                return 0;
			case 1:     
				//��ʾ�����ļ�
                showDictionary();
                break;          
			case 2:     
				//�����ļ�
                printf("�������ļ���:");
                scanf("%s", name);
                create(name);
                break;
            case 3:     
				//ɾ���ļ�
                printf("�������ļ���:");
                scanf("%s", name);
                res = destroy(name);
                break;
            case 4:     
				//���ļ�
                printf("�������ļ���:");
                scanf("%s", name);
                f = open(name);
                if(f != NULL)
                {
                    printf("%s�򿪳ɹ���\n",name);
                }
                break;
            case 5:     
				//�ر��ļ�
                printf("�������ļ���:");
                scanf("%s", name);
                f = open(name);
                if(f == NULL)
                {
                    break;
                }
                close(f);
                break;
            case 6:     
				//���ļ�
                printf("�������ļ���:");
                scanf("%s", name);
                f = open(name);

                if(f == NULL)
                {
                    break;
                }
                printf("�������ȡ����:");
                scanf("%d", &len);
                str[0] = '\0';
                f = read(f, str, len);
                if(f == NULL)
                {
                    printf("����Խ��\n");
                }
                printf("%s\n", str);

                break;
            case 7:     
				//д�ļ�
                printf("�������ļ���:");
                scanf("%s", name);
                f = open(name);

                if(f == NULL)
                {
                    break;
                }
                printf("������д������:");
                scanf("%s", str);
                printf("������д�볤��:");
                scanf("%d", &len);
                f = write(f, str, len);

                break;
            case 8:     
				//�ƶ��ļ�ָ��
                printf("�������ļ���:");
                scanf("%s", name);
                
				f = open(name);

                if(f == NULL)
                {
                    break;
                }

                printf("�������ƶ�λ��:");
                
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

