#include"header.h"

int   invalidcount = 0;   // ȱҳ����
int   vpoint;             //ҳ�����ָ��
int   pageframe[10];      // �ڴ���ҳ������
int   pagehistory[10];    //��¼�ڴ���ҳ�������ݵķ�����ʷ
int   inpflag;            //ȱҳ��־��0Ϊ��ȱҳ��1Ϊȱҳ
int   faflag;			  //�ڴ���ҳ���Ƿ���
int existence[10];		//����ҳ��Ĵ���λ
struct PageInfo       //ҳ����Ϣ�ṹ
{
	int  serial[100];  // ģ���������ҳ������ʵ�ʿ�����20����
	int  flag;         // ��־λ��0��ʾ��ҳ���������
	int  diseffect;    // ȱҳ����
	int  total_pf;     // �����ҳ����
	int  total_pn;     // ����ҳ�����г���
} pf_info;