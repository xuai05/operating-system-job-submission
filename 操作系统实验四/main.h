#include"header.h"

int   invalidcount = 0;   // 缺页次数
int   vpoint;             //页面访问指针
int   pageframe[10];      // 内存中页框数组
int   pagehistory[10];    //记录内存中页框中数据的访问历史
int   inpflag;            //缺页标志，0为不缺页，1为缺页
int   faflag;			  //内存中页框是否满
int existence[10];		//设置页框的存在位
struct PageInfo       //页面信息结构
{
	int  serial[100];  // 模拟的最大访问页面数，实际控制在20以上
	int  flag;         // 标志位，0表示无页面访问数据
	int  diseffect;    // 缺页次数
	int  total_pf;     // 分配的页框数
	int  total_pn;     // 访问页面序列长度
} pf_info;