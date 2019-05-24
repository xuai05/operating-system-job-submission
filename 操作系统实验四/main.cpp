
#include"header.h"

///////////////////////////////////////////////////////////////////
//  主函数
int main()
{
	int flag = 1;
	int chioce;
	while (flag)
	{
		cout<<"*******************************************"<<endl;
		cout << "     若要执行最佳置算法			请按1"<< endl;
		cout << "     若要执行FIFO 页面置算法		请按2" << endl;
		cout << "     若要执行LRU页面置算法		请按3" << endl;
		cout << "     若要执行改进型Clock算法		请按4" << endl;
		cout << "     若要执行页面缓冲算法PBA		请按5" << endl;
		cout << "     若要退出				请按0" << endl;
		cout << "*******************************************\n" << endl;
		cout << "输入你的选项 " ;
		cin >> chioce;
		while (chioce != 1 && chioce != 2 && chioce != 3 && chioce != 4 && chioce != 5 && chioce != 0){
			cout << "输入错误！！！请重新输入" << endl;
			cin >> chioce;
		}
		switch (chioce)
		{
		case 1:
			cout << "*****************************页面最佳置换算法****************************"<< endl;
			OPT();
			break;
		case 2:
			cout << "*****************************FIFO页面置换算法****************************" << endl;
			FIFO();
			break;
		case 3:
			cout << "*****************************LRU页面置换算法****************************" << endl;
			LRU();
			break;
		case 4:
			cout << "*****************************改进型Clock算法****************************" << endl;
			gClock();
			break;
		case 5:
			cout << "*****************************页面缓冲算法PBA****************************" << endl;
			PBA();
			break;
		case 0:
			cout << "再见！！！" << endl;
			flag = 0;
			break;
		}
		system("pause");
	}
	return 0;
}