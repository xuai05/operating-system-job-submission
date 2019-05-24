#include"header.h"
#include"main.h"



/***************************************辅助函数************************************************/
// 随机生成访问序列
void createps(void)
{
	int pn;
	initialize();     //初始化相关数据结构
	cout<<"请输入要随机生成访问序列的长度";   //自定义随机生成访问序列的长度
	scanf("%d", &pn);
	int p=1, e,m;
	double t = 0.5;
	cout << "请输入工作集中页面数:";
	cin >> e;
	cout << "请输入工作集移动率:" ;
	cin >> m;
	srand((unsigned)time(NULL));   //初始化随机数队列的"种子"
	pf_info.total_pn = pn;
	for (int j = 0; j < pn;){
		for (int i = 0; i<m; i++,j++)    //产生随机访问序列
		{
			pf_info.serial[j] = rand() % (e+1) + p;   //随机数的大小在p-p+e之间      
		}
		double r = rand() / double(RAND_MAX);
		if (r>t){
			p = rand() % ( 15- 1 + 1) + 1;//为p生成一个在1-15之间的新值
		}
		else{
			p = p + 1;
		}
	}
}
// 查找页面是否在内存，1为在内存，0为不在即缺页
int findpage(int page)
{
	int n;
	for (n = 0; n<pf_info.total_pf; n++)
	{
		pagehistory[n] ++;   // 访问历史加1
	}
	for (n = 0; n<pf_info.total_pf; n++)
	{
		if (pageframe[n] == page)
		{
			inpflag = 0;    //inpflag缺页标志，0为不缺页，1为缺页	   
			pagehistory[n] = 0;   //置访问历史为0
			return 1;
		}
	}
	inpflag = 1;  	//页面不存在，缺页
	return 0;
}
//初始化相关数据结构
void initialize()
{
	int i, pf;
	inpflag = 0;
	pf_info.diseffect = 0;
	pf_info.flag = 0;
	printf("\n请输入要分配的页框数：");
	scanf("%d", &pf);
	pf_info.total_pf = pf;
	for (i = 0; i<100; i++)   // 清空页面序列
	{
		pf_info.serial[i] = -1;
	}
}
//  显示当前状态及缺页情况
void displayinfo(void)
{
	int i, n;
	//显示页面访问序列情况
	if (vpoint == 0)
	{
		printf("\n=============页面访问序列=============\n");
		for (i = 0; i<pf_info.total_pn; i++)
		{
			printf("%4d", pf_info.serial[i]);
			if ((i + 1) % 10 == 0) printf("\n");   //每行显示10个	  	 		   
		}
		printf("\n======================================\n");
	}

	//以后每次访问页面，输出当前的访问页面与对应页框信息及缺页率
	printf("访问%3d : 内存<", pf_info.serial[vpoint]);
	for (n = 0; n<pf_info.total_pf; n++)     // 页框信息
	{
		if (pageframe[n] >= 0)			//如果页框内有值（值大于-1），进行对应输出
			printf("%3d", pageframe[n]);
		else
			printf("   ");
	}
	printf(" >");
	if (inpflag == 1)
	{
		printf(" ==>缺页 ");
	}
	printf("\n");
}
//  显示当前状态及缺页情况
void displayinfoPBA(void)
{
	int i, n;
	//显示页面访问序列情况
	if (vpoint == 0)
	{
		printf("\n=============页面访问序列=============\n");
		for (i = 0; i<pf_info.total_pn; i++)
		{
			printf("%4d", pf_info.serial[i]);
			if ((i + 1) % 10 == 0) printf("\n");   //每行显示10个	  	 		   
		}
		printf("\n======================================\n");
	}

	//以后每次访问页面，输出当前的访问页面与对应页框信息及缺页率
	printf("访问%3d : 内存<", pf_info.serial[vpoint]);
	for (n = 0; n<pf_info.total_pf+2; n++)     // 页框信息
	{
		if (pageframe[n] >= 0 && existence[n]==1)			//如果页框内有值（值大于-1），进行对应输出
			printf("%3d", pageframe[n]);
		else
			printf("   ");
	}
	printf(" >");
	if (inpflag == 1)
	{
		printf(" ==>缺页 ");
	}
	printf("\n");
}


/***************************************辅助函数************************************************/


/***************************************主要函数************************************************/
// 最佳置换算法
void OPT()
{
	createps();        // 随机生成访问序列
	int n;
	int pstate;  //页面是否存在于内容中，0不存在，1存在
	int rpoint = 0;          // 页面替换指针
	int count = 0;           // 是否装满所有的页框

	for (n = 0; n<pf_info.total_pf; n++)
	{
		pageframe[n] = -1;    // 清除页框信息
		pagehistory[n] = 0;   // 清除页框历史
	}
	inpflag = 0;    //缺页标志，0为不缺页，1为缺页
	for (vpoint = 0; vpoint<pf_info.total_pn; vpoint++)  // 执行算法
	{
		pstate = findpage(pf_info.serial[vpoint]);  //查找页面是否在内存
		if (count<pf_info.total_pf)   // 开始时不计算缺页
		{
			if (pstate == 0)   // 页不存在则装入页面
			{
				pageframe[rpoint] = pf_info.serial[vpoint]; //把要调入的页面放入一个空的页框里
				rpoint = (rpoint + 1) % pf_info.total_pf;
				count++;
			}
			inpflag = 0;
		}
		else // 正常缺页置换
		{
			if (pstate == 0)// 页不存在则置换页面
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
				pf_info.diseffect++;  // 缺页次数加1				
			}
		}
		displayinfo();    // 显示当前状态
	} 
	printf("缺页率%3.1f\n", (float)(pf_info.diseffect)*100.00 / vpoint);
	return;
}
//  FIFO页面置换算法
void FIFO()
{
	createps();// 随机生成访问序列
	int n;
	int pstate;    //页面是否存在于内容中，0不存在，1存在
	int rpoint = 0;          // 页面替换指针初始化为0 
	int count = 0;           // 页框使用情况计数
	for (n = 0; n<pf_info.total_pf; n++) // 清除页框信息
	{
		pageframe[n] = -1;
	}
	inpflag = 0;   //缺页标志，0为不缺页，1为缺页
	for (vpoint = 0; vpoint<pf_info.total_pn; vpoint++)  // 执行算法
	{
		pstate = findpage(pf_info.serial[vpoint]);  //查找页面是否在内存
		if (count<pf_info.total_pf)    // 当页框未满时，不计算缺页，此时装入页面
		{
			if (pstate == 0)    // 页不存在则装入页面
			{
				pageframe[rpoint] = pf_info.serial[vpoint];
				rpoint = (rpoint + 1) % pf_info.total_pf;			//实现模页面数，指针下移
				count++;
			}
			inpflag = 0;
		}
		else      // 页面满时，正常缺页置换
		{
			if (pstate == 0)    //页不存在则置换页面
			{
				pageframe[rpoint] = pf_info.serial[vpoint];
				rpoint = (rpoint + 1) % pf_info.total_pf;
				pf_info.diseffect++;     // 缺页次数加1				  			
			}
		}
		displayinfo();       // 显示当前状态
	}	 // 置换算法循环结束
	//显示缺页率
	printf("缺页率%3.1f\n", (float)(pf_info.diseffect)*100.00 / vpoint);
	return;
}
//  LRU页面置换算法
void LRU()
{
	createps();        // 随机生成访问序列
	int n;
	int pstate;  //页面是否存在于内容中，0不存在，1存在
	int max;
	int rpoint = 0;          // 页面替换指针
	int count = 0;           // 是否装满所有的页框
	for (n = 0; n<pf_info.total_pf; n++)
	{
		pageframe[n] = -1;    // 清除页框信息
		pagehistory[n] = 0;   // 清除页框历史
	}
	inpflag = 0;    //缺页标志，0为不缺页，1为缺页
	for (vpoint = 0; vpoint<pf_info.total_pn; vpoint++)  // 执行算法
	{
		pstate = findpage(pf_info.serial[vpoint]);  //查找页面是否在内存
		if (count<pf_info.total_pf)   // 开始时不计算缺页
		{
			if (pstate == 0)   // 页不存在则装入页面
			{
				pageframe[rpoint] = pf_info.serial[vpoint]; //把要调入的页面放入一个空的页框里
				rpoint = (rpoint + 1) % pf_info.total_pf;
				count++;
			}
			inpflag = 0;
		}
		else // 正常缺页置换
		{
			if (pstate == 0)// 页不存在则置换页面
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
				pf_info.diseffect++;  // 缺页次数加1				
			}
		}
		displayinfo();    // 显示当前状态
	} 	// 置换算法循环结束
	printf("缺页率%3.1f\n", (float)(pf_info.diseffect)*100.00 / vpoint);
	return;
}
//改进Clock()算法
void gClock()
{
	createps();        // 随机生成访问序列
	int n;
	int pstate;  //页面是否存在于内容中，0不存在，1存在
	int max;
	int rpoint = 0;          // 页面替换指针
	int count = 0;           // 是否装满所有的页框
	int paccess[10];	//记录内存框中访问位
	int pmodify[10];    //记录内存框中修改位
	srand((unsigned)time(NULL));   //初始化随机数队列的"种子"
	for (n = 0; n<pf_info.total_pf; n++)
	{
		pageframe[n] = -1;    // 清除页框信息
		paccess[n] = 0;
		pmodify[n] = rand() % 2 ;   //随机数0或1  
	}
	inpflag = 0;    //缺页标志，0为不缺页，1为缺页
	for (vpoint = 0; vpoint<pf_info.total_pn; vpoint++)  // 执行算法
	{
		pstate = findpage(pf_info.serial[vpoint]);  //查找页面是否在内存
		for (n = 0; n<pf_info.total_pf; n++)
		{
			if (pageframe[n] == pf_info.serial[vpoint])
			{
				paccess[n] = 1;
			}
		}
		if (count<pf_info.total_pf)   // 开始时不计算缺页
		{
			if (pstate == 0)   // 页不存在则装入页面
			{
				pageframe[rpoint] = pf_info.serial[vpoint]; //把要调入的页面放入一个空的页框里
				rpoint = (rpoint + 1) % pf_info.total_pf;
				count++;
			}
			inpflag = 0;
		}
		else // 正常缺页置换
		{
			if (pstate == 0)// 页不存在则置换页面
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
				pmodify[rpoint] = rand() % 2;		//随机植入修改位值
				pf_info.diseffect++;  // 缺页次数加1				
			}
		}
		displayinfo();    // 显示当前状态
	} 	// 置换算法循环结束
	printf("缺页率%3.1f\n", (float)(pf_info.diseffect)*100.00 / vpoint);
	return;
}
//PBA()算法
void PBA(){
	struct Pb
	{
		int Memnum;			//空闲列对应内存块号
		int Pagenum;		//空闲列对应访问页号
	}pb[2];
	createps();        // 随机生成访问序列
	int n;
	int pstate;  //页面是否存在于内容中，0不存在，1存在
	int rpoint = 0;          // 页面替换指针
	int count = 0;           // 是否装满所有的页框
	for (n = 0; n < pf_info.total_pf; n++)
	{
		pageframe[n] = -1;    // 清除页框信息
		existence[n] = 1;//页框存在为置1
	}
	existence[pf_info.total_pf] = 0;
	existence[pf_info.total_pf+1] = 0;//设置两位的存在位
	pb[0].Memnum = pf_info.total_pf;
	pb[0].Pagenum = -1;
	pb[1].Memnum = pf_info.total_pf+1;
	pb[1].Pagenum = -1;				//初始化空闲链
	inpflag = 0;    //缺页标志，0为不缺页，1为缺页
	for (vpoint = 0; vpoint<pf_info.total_pn; vpoint++)  // 执行算法
	{
		pstate = 0;//默认缺页
		for (n = 0; n<pf_info.total_pf+2; n++)
		{
			if (pageframe[n] == pf_info.serial[vpoint] && existence[n]==1)
			{
				pstate = 1;//访问页面存在于内存中
				inpflag = 0;
				break;
			}
		}
		if (count<pf_info.total_pf)   // 开始时不计算缺页
		{
			if (pstate == 0)   // 页不存在则装入页面
			{
				pageframe[rpoint] = pf_info.serial[vpoint]; //把要调入的页面放入一个空的页框里
				rpoint = (rpoint + 1) % pf_info.total_pf;
				existence[rpoint] = 1;			
				count++;
			}
			inpflag = 0;
		}
		else // 正常缺页置换
		{
			if (pstate == 0)// 页不存在则置换页面
			{
				inpflag = 1;
				int flag = 0;//页面是否在空闲链内,0不在，1在
				for (int i = 0; i < 2; i++){
					if (pb[i].Pagenum == pf_info.serial[vpoint]){
						existence[pb[i].Memnum] = 1;
						pageframe[pb[i].Memnum] = pb[i].Pagenum;
						if (i == 0){//如果是链首弹出
							pb[0].Memnum = pb[1].Memnum;
							pb[0].Pagenum = pb[1].Pagenum;	//空闲链首移动一位
							existence[rpoint] = 0;		//从访问页框根据先进先出弹出页框,放入空闲链尾
							pb[1].Memnum = rpoint;
							pb[1].Pagenum = pageframe[rpoint];
						}
						else{//如果是链尾
							existence[rpoint] = 0;		//从访问页框根据先进先出弹出页框,放入空闲
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
					pb[0].Pagenum = pb[1].Pagenum;	//空闲链首移动一位
					existence[rpoint] = 0;		//从访问页框根据先进先出弹出页框,放入空闲链尾
					pb[1].Memnum = rpoint;
					pb[1].Pagenum = pageframe[rpoint];
				}
				rpoint = (rpoint + 1) % pf_info.total_pf;//页面指针下移
				while (existence[rpoint] == 0)
					rpoint = (rpoint + 1) % pf_info.total_pf;//页面指针下移
				pf_info.diseffect++;     // 缺页次数加1					
			}
		}
		displayinfoPBA();    // 显示当前状态
	} 	// 置换算法循环结束
	printf("缺页率%3.1f\n", (float)(pf_info.diseffect)*100.00 / vpoint);
	return;
}