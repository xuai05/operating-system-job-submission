
#include"header.h"

///////////////////////////////////////////////////////////////////
//  ������
int main()
{
	int flag = 1;
	int chioce;
	while (flag)
	{
		cout<<"*******************************************"<<endl;
		cout << "     ��Ҫִ��������㷨			�밴1"<< endl;
		cout << "     ��Ҫִ��FIFO ҳ�����㷨		�밴2" << endl;
		cout << "     ��Ҫִ��LRUҳ�����㷨		�밴3" << endl;
		cout << "     ��Ҫִ�иĽ���Clock�㷨		�밴4" << endl;
		cout << "     ��Ҫִ��ҳ�滺���㷨PBA		�밴5" << endl;
		cout << "     ��Ҫ�˳�				�밴0" << endl;
		cout << "*******************************************\n" << endl;
		cout << "�������ѡ�� " ;
		cin >> chioce;
		while (chioce != 1 && chioce != 2 && chioce != 3 && chioce != 4 && chioce != 5 && chioce != 0){
			cout << "������󣡣�������������" << endl;
			cin >> chioce;
		}
		switch (chioce)
		{
		case 1:
			cout << "*****************************ҳ������û��㷨****************************"<< endl;
			OPT();
			break;
		case 2:
			cout << "*****************************FIFOҳ���û��㷨****************************" << endl;
			FIFO();
			break;
		case 3:
			cout << "*****************************LRUҳ���û��㷨****************************" << endl;
			LRU();
			break;
		case 4:
			cout << "*****************************�Ľ���Clock�㷨****************************" << endl;
			gClock();
			break;
		case 5:
			cout << "*****************************ҳ�滺���㷨PBA****************************" << endl;
			PBA();
			break;
		case 0:
			cout << "�ټ�������" << endl;
			flag = 0;
			break;
		}
		system("pause");
	}
	return 0;
}