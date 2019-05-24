#include"header.h"
#include"main.h"



/***************************************��������************************************************/
// ������ɷ�������
void createps(void)
{
	int pn;
	initialize();     //��ʼ��������ݽṹ
	cout<<"������Ҫ������ɷ������еĳ���";   //�Զ���������ɷ������еĳ���
	scanf("%d", &pn);
	int p=1, e,m;
	double t = 0.5;
	cout << "�����빤������ҳ����:";
	cin >> e;
	cout << "�����빤�����ƶ���:" ;
	cin >> m;
	srand((unsigned)time(NULL));   //��ʼ����������е�"����"
	pf_info.total_pn = pn;
	for (int j = 0; j < pn;){
		for (int i = 0; i<m; i++,j++)    //���������������
		{
			pf_info.serial[j] = rand() % (e+1) + p;   //������Ĵ�С��p-p+e֮��      
		}
		double r = rand() / double(RAND_MAX);
		if (r>t){
			p = rand() % ( 15- 1 + 1) + 1;//Ϊp����һ����1-15֮�����ֵ
		}
		else{
			p = p + 1;
		}
	}
}
// ����ҳ���Ƿ����ڴ棬1Ϊ���ڴ棬0Ϊ���ڼ�ȱҳ
int findpage(int page)
{
	int n;
	for (n = 0; n<pf_info.total_pf; n++)
	{
		pagehistory[n] ++;   // ������ʷ��1
	}
	for (n = 0; n<pf_info.total_pf; n++)
	{
		if (pageframe[n] == page)
		{
			inpflag = 0;    //inpflagȱҳ��־��0Ϊ��ȱҳ��1Ϊȱҳ	   
			pagehistory[n] = 0;   //�÷�����ʷΪ0
			return 1;
		}
	}
	inpflag = 1;  	//ҳ�治���ڣ�ȱҳ
	return 0;
}
//��ʼ��������ݽṹ
void initialize()
{
	int i, pf;
	inpflag = 0;
	pf_info.diseffect = 0;
	pf_info.flag = 0;
	printf("\n������Ҫ�����ҳ������");
	scanf("%d", &pf);
	pf_info.total_pf = pf;
	for (i = 0; i<100; i++)   // ���ҳ������
	{
		pf_info.serial[i] = -1;
	}
}
//  ��ʾ��ǰ״̬��ȱҳ���
void displayinfo(void)
{
	int i, n;
	//��ʾҳ������������
	if (vpoint == 0)
	{
		printf("\n=============ҳ���������=============\n");
		for (i = 0; i<pf_info.total_pn; i++)
		{
			printf("%4d", pf_info.serial[i]);
			if ((i + 1) % 10 == 0) printf("\n");   //ÿ����ʾ10��	  	 		   
		}
		printf("\n======================================\n");
	}

	//�Ժ�ÿ�η���ҳ�棬�����ǰ�ķ���ҳ�����Ӧҳ����Ϣ��ȱҳ��
	printf("����%3d : �ڴ�<", pf_info.serial[vpoint]);
	for (n = 0; n<pf_info.total_pf; n++)     // ҳ����Ϣ
	{
		if (pageframe[n] >= 0)			//���ҳ������ֵ��ֵ����-1�������ж�Ӧ���
			printf("%3d", pageframe[n]);
		else
			printf("   ");
	}
	printf(" >");
	if (inpflag == 1)
	{
		printf(" ==>ȱҳ ");
	}
	printf("\n");
}
//  ��ʾ��ǰ״̬��ȱҳ���
void displayinfoPBA(void)
{
	int i, n;
	//��ʾҳ������������
	if (vpoint == 0)
	{
		printf("\n=============ҳ���������=============\n");
		for (i = 0; i<pf_info.total_pn; i++)
		{
			printf("%4d", pf_info.serial[i]);
			if ((i + 1) % 10 == 0) printf("\n");   //ÿ����ʾ10��	  	 		   
		}
		printf("\n======================================\n");
	}

	//�Ժ�ÿ�η���ҳ�棬�����ǰ�ķ���ҳ�����Ӧҳ����Ϣ��ȱҳ��
	printf("����%3d : �ڴ�<", pf_info.serial[vpoint]);
	for (n = 0; n<pf_info.total_pf+2; n++)     // ҳ����Ϣ
	{
		if (pageframe[n] >= 0 && existence[n]==1)			//���ҳ������ֵ��ֵ����-1�������ж�Ӧ���
			printf("%3d", pageframe[n]);
		else
			printf("   ");
	}
	printf(" >");
	if (inpflag == 1)
	{
		printf(" ==>ȱҳ ");
	}
	printf("\n");
}


/***************************************��������************************************************/


/***************************************��Ҫ����************************************************/
// ����û��㷨
void OPT()
{
	createps();        // ������ɷ�������
	int n;
	int pstate;  //ҳ���Ƿ�����������У�0�����ڣ�1����
	int rpoint = 0;          // ҳ���滻ָ��
	int count = 0;           // �Ƿ�װ�����е�ҳ��

	for (n = 0; n<pf_info.total_pf; n++)
	{
		pageframe[n] = -1;    // ���ҳ����Ϣ
		pagehistory[n] = 0;   // ���ҳ����ʷ
	}
	inpflag = 0;    //ȱҳ��־��0Ϊ��ȱҳ��1Ϊȱҳ
	for (vpoint = 0; vpoint<pf_info.total_pn; vpoint++)  // ִ���㷨
	{
		pstate = findpage(pf_info.serial[vpoint]);  //����ҳ���Ƿ����ڴ�
		if (count<pf_info.total_pf)   // ��ʼʱ������ȱҳ
		{
			if (pstate == 0)   // ҳ��������װ��ҳ��
			{
				pageframe[rpoint] = pf_info.serial[vpoint]; //��Ҫ�����ҳ�����һ���յ�ҳ����
				rpoint = (rpoint + 1) % pf_info.total_pf;
				count++;
			}
			inpflag = 0;
		}
		else // ����ȱҳ�û�
		{
			if (pstate == 0)// ҳ���������û�ҳ��
			{
				int max = 0,p=0;
				for (int i = 0; i < pf_info.total_pf; i++){
					for (int n = vpoint; n<pf_info.total_pn; n++)
					{
						if (pageframe[i] == pf_info.serial[n] && n>max)
						{
							max = n;
							p = i;
							break;
						}
						else if (n == pf_info.total_pn - 1){
							p = i;
							i = pf_info.total_pf;
							break;
						}
					}
				}
				pageframe[p] = pf_info.serial[vpoint];
				pf_info.diseffect++;  // ȱҳ������1				
			}
		}
		displayinfo();    // ��ʾ��ǰ״̬
	} 
	printf("ȱҳ��%3.1f\n", (float)(pf_info.diseffect)*100.00 / vpoint);
	return;
}
//  FIFOҳ���û��㷨
void FIFO()
{
	createps();// ������ɷ�������
	int n;
	int pstate;    //ҳ���Ƿ�����������У�0�����ڣ�1����
	int rpoint = 0;          // ҳ���滻ָ���ʼ��Ϊ0 
	int count = 0;           // ҳ��ʹ���������
	for (n = 0; n<pf_info.total_pf; n++) // ���ҳ����Ϣ
	{
		pageframe[n] = -1;
	}
	inpflag = 0;   //ȱҳ��־��0Ϊ��ȱҳ��1Ϊȱҳ
	for (vpoint = 0; vpoint<pf_info.total_pn; vpoint++)  // ִ���㷨
	{
		pstate = findpage(pf_info.serial[vpoint]);  //����ҳ���Ƿ����ڴ�
		if (count<pf_info.total_pf)    // ��ҳ��δ��ʱ��������ȱҳ����ʱװ��ҳ��
		{
			if (pstate == 0)    // ҳ��������װ��ҳ��
			{
				pageframe[rpoint] = pf_info.serial[vpoint];
				rpoint = (rpoint + 1) % pf_info.total_pf;			//ʵ��ģҳ������ָ������
				count++;
			}
			inpflag = 0;
		}
		else      // ҳ����ʱ������ȱҳ�û�
		{
			if (pstate == 0)    //ҳ���������û�ҳ��
			{
				pageframe[rpoint] = pf_info.serial[vpoint];
				rpoint = (rpoint + 1) % pf_info.total_pf;
				pf_info.diseffect++;     // ȱҳ������1				  			
			}
		}
		displayinfo();       // ��ʾ��ǰ״̬
	}	 // �û��㷨ѭ������
	//��ʾȱҳ��
	printf("ȱҳ��%3.1f\n", (float)(pf_info.diseffect)*100.00 / vpoint);
	return;
}
//  LRUҳ���û��㷨
void LRU()
{
	createps();        // ������ɷ�������
	int n;
	int pstate;  //ҳ���Ƿ�����������У�0�����ڣ�1����
	int max;
	int rpoint = 0;          // ҳ���滻ָ��
	int count = 0;           // �Ƿ�װ�����е�ҳ��
	for (n = 0; n<pf_info.total_pf; n++)
	{
		pageframe[n] = -1;    // ���ҳ����Ϣ
		pagehistory[n] = 0;   // ���ҳ����ʷ
	}
	inpflag = 0;    //ȱҳ��־��0Ϊ��ȱҳ��1Ϊȱҳ
	for (vpoint = 0; vpoint<pf_info.total_pn; vpoint++)  // ִ���㷨
	{
		pstate = findpage(pf_info.serial[vpoint]);  //����ҳ���Ƿ����ڴ�
		if (count<pf_info.total_pf)   // ��ʼʱ������ȱҳ
		{
			if (pstate == 0)   // ҳ��������װ��ҳ��
			{
				pageframe[rpoint] = pf_info.serial[vpoint]; //��Ҫ�����ҳ�����һ���յ�ҳ����
				rpoint = (rpoint + 1) % pf_info.total_pf;
				count++;
			}
			inpflag = 0;
		}
		else // ����ȱҳ�û�
		{
			if (pstate == 0)// ҳ���������û�ҳ��
			{
				max = 0;
				for (n = 1; n<pf_info.total_pf; n++)
				{
					if (pagehistory[n]>pagehistory[max])
					{
						max = n;
					}
				}
				rpoint = max;
				pageframe[rpoint] = pf_info.serial[vpoint];
				pagehistory[rpoint] = 0;
				pf_info.diseffect++;  // ȱҳ������1				
			}
		}
		displayinfo();    // ��ʾ��ǰ״̬
	} 	// �û��㷨ѭ������
	printf("ȱҳ��%3.1f\n", (float)(pf_info.diseffect)*100.00 / vpoint);
	return;
}
//�Ľ�Clock()�㷨
void gClock()
{
	createps();        // ������ɷ�������
	int n;
	int pstate;  //ҳ���Ƿ�����������У�0�����ڣ�1����
	int max;
	int rpoint = 0;          // ҳ���滻ָ��
	int count = 0;           // �Ƿ�װ�����е�ҳ��
	int paccess[10];	//��¼�ڴ���з���λ
	int pmodify[10];    //��¼�ڴ�����޸�λ
	srand((unsigned)time(NULL));   //��ʼ����������е�"����"
	for (n = 0; n<pf_info.total_pf; n++)
	{
		pageframe[n] = -1;    // ���ҳ����Ϣ
		paccess[n] = 0;
		pmodify[n] = rand() % 2 ;   //�����0��1  
	}
	inpflag = 0;    //ȱҳ��־��0Ϊ��ȱҳ��1Ϊȱҳ
	for (vpoint = 0; vpoint<pf_info.total_pn; vpoint++)  // ִ���㷨
	{
		pstate = findpage(pf_info.serial[vpoint]);  //����ҳ���Ƿ����ڴ�
		for (n = 0; n<pf_info.total_pf; n++)
		{
			if (pageframe[n] == pf_info.serial[vpoint])
			{
				paccess[n] = 1;
			}
		}
		if (count<pf_info.total_pf)   // ��ʼʱ������ȱҳ
		{
			if (pstate == 0)   // ҳ��������װ��ҳ��
			{
				pageframe[rpoint] = pf_info.serial[vpoint]; //��Ҫ�����ҳ�����һ���յ�ҳ����
				rpoint = (rpoint + 1) % pf_info.total_pf;
				count++;
			}
			inpflag = 0;
		}
		else // ����ȱҳ�û�
		{
			if (pstate == 0)// ҳ���������û�ҳ��
			{
				rpoint = 0;
				int flag=0;
				for (n = 0; n<pf_info.total_pf; n++)
				{
					if (paccess[n] == 0 && pmodify[n]==0)
					{
						rpoint = n;
						break;
					}
					if (n == pf_info.total_pf - 1)flag = 1;
				}
				if (flag){
					for (n = 0; n<pf_info.total_pf; n++)
					{
						if (paccess[n] == 0 && pmodify[n] == 1)
						{
							rpoint = n;
							break;
						}
						paccess[n] = 0;
					}
				}
				pageframe[rpoint] = pf_info.serial[vpoint];
				pmodify[rpoint] = rand() % 2;		//���ֲ���޸�λֵ
				pf_info.diseffect++;  // ȱҳ������1				
			}
		}
		displayinfo();    // ��ʾ��ǰ״̬
	} 	// �û��㷨ѭ������
	printf("ȱҳ��%3.1f\n", (float)(pf_info.diseffect)*100.00 / vpoint);
	return;
}
//PBA()�㷨
void PBA(){
	struct Pb
	{
		int Memnum;			//�����ж�Ӧ�ڴ���
		int Pagenum;		//�����ж�Ӧ����ҳ��
	}pb[2];
	createps();        // ������ɷ�������
	int n;
	int pstate;  //ҳ���Ƿ�����������У�0�����ڣ�1����
	int rpoint = 0;          // ҳ���滻ָ��
	int count = 0;           // �Ƿ�װ�����е�ҳ��
	for (n = 0; n < pf_info.total_pf; n++)
	{
		pageframe[n] = -1;    // ���ҳ����Ϣ
		existence[n] = 1;//ҳ�����Ϊ��1
	}
	existence[pf_info.total_pf] = 0;
	existence[pf_info.total_pf+1] = 0;//������λ�Ĵ���λ
	pb[0].Memnum = pf_info.total_pf;
	pb[0].Pagenum = -1;
	pb[1].Memnum = pf_info.total_pf+1;
	pb[1].Pagenum = -1;				//��ʼ��������
	inpflag = 0;    //ȱҳ��־��0Ϊ��ȱҳ��1Ϊȱҳ
	for (vpoint = 0; vpoint<pf_info.total_pn; vpoint++)  // ִ���㷨
	{
		pstate = 0;//Ĭ��ȱҳ
		for (n = 0; n<pf_info.total_pf+2; n++)
		{
			if (pageframe[n] == pf_info.serial[vpoint] && existence[n]==1)
			{
				pstate = 1;//����ҳ��������ڴ���
				inpflag = 0;
				break;
			}
		}
		if (count<pf_info.total_pf)   // ��ʼʱ������ȱҳ
		{
			if (pstate == 0)   // ҳ��������װ��ҳ��
			{
				pageframe[rpoint] = pf_info.serial[vpoint]; //��Ҫ�����ҳ�����һ���յ�ҳ����
				rpoint = (rpoint + 1) % pf_info.total_pf;
				existence[rpoint] = 1;			
				count++;
			}
			inpflag = 0;
		}
		else // ����ȱҳ�û�
		{
			if (pstate == 0)// ҳ���������û�ҳ��
			{
				inpflag = 1;
				int flag = 0;//ҳ���Ƿ��ڿ�������,0���ڣ�1��
				for (int i = 0; i < 2; i++){
					if (pb[i].Pagenum == pf_info.serial[vpoint]){
						existence[pb[i].Memnum] = 1;
						pageframe[pb[i].Memnum] = pb[i].Pagenum;
						if (i == 0){//��������׵���
							pb[0].Memnum = pb[1].Memnum;
							pb[0].Pagenum = pb[1].Pagenum;	//���������ƶ�һλ
							existence[rpoint] = 0;		//�ӷ���ҳ������Ƚ��ȳ�����ҳ��,���������β
							pb[1].Memnum = rpoint;
							pb[1].Pagenum = pageframe[rpoint];
						}
						else{//�������β
							existence[rpoint] = 0;		//�ӷ���ҳ������Ƚ��ȳ�����ҳ��,�������
							pb[1].Memnum = rpoint;
							pb[1].Pagenum = pageframe[rpoint];
						}
						flag = 1;
					}
				}
				if (flag == 0){
					existence[pb[0].Memnum] = 1;
					pageframe[pb[0].Memnum] = pf_info.serial[vpoint];
					pb[0].Memnum = pb[1].Memnum;
					pb[0].Pagenum = pb[1].Pagenum;	//���������ƶ�һλ
					existence[rpoint] = 0;		//�ӷ���ҳ������Ƚ��ȳ�����ҳ��,���������β
					pb[1].Memnum = rpoint;
					pb[1].Pagenum = pageframe[rpoint];
				}
				rpoint = (rpoint + 1) % pf_info.total_pf;//ҳ��ָ������
				while (existence[rpoint] == 0)
					rpoint = (rpoint + 1) % pf_info.total_pf;//ҳ��ָ������
				pf_info.diseffect++;     // ȱҳ������1					
			}
		}
		displayinfoPBA();    // ��ʾ��ǰ״̬
	} 	// �û��㷨ѭ������
	printf("ȱҳ��%3.1f\n", (float)(pf_info.diseffect)*100.00 / vpoint);
	return;
}