
#include<iostream>
#include<ctime>
#include<vector>
#include<algorithm>
#include"RBtree.h"
using namespace std;

int Show()
{   
	cout << "----------------------" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	cout << "3��ɾ��" << endl;
	cout << "4����ֵ�ݼ���ʾ" << endl;
	cout << "5����ʾƽ�����ҳ���" << endl;
	cout << "0���˳�" << endl;
	cout << "��ѡ��";
	int choice = -1;
	cin >> choice;
	cout << "------------------------" << endl;
	return choice;
}

int main()
{
	srand((unsigned int)time(NULL));   //�������������

	int nums[1000];      //����10����

	int k;
	cout << "�����������" << endl;
	cin >> k;

	RBtree MyRBtree;

	vector<TreeNode*> Posi;

	TreeNode* pos = NULL;

	for (int i = 0; i < k; i++)
	{
		nums[i] = rand() % 21 ;    //0��20�������
		cout << nums[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < k; i++) {
		cout << "--------------------" << endl;
		cout << "���뵽�ڣ�" << i << "����: "<<nums[i]<< endl;
		//cout << "���뵽�ڣ�" << i << "����: " << i+1 << endl;
	    pos =	MyRBtree.insert(MyRBtree._root,nums[i]);
		//pos = MyRBtree.insert(MyRBtree._root, i+1);
		MyRBtree.ChageColor(pos);
		MyRBtree.In_Travle(MyRBtree._root);
		cout << "�����ǣ�" << MyRBtree._root->data << endl;
		cout << "-------------------" << endl;
	}
	cout << "������ϣ�" << endl;
	MyRBtree.GetPosi(Posi);

	int numb[10];  //�洢ÿ��Ľڵ������ڼ���ƽ�����ҳ���

	while (1) {

		int choice = Show();

		switch (choice)
		{
		case 1:
			int number;
			cout << "������������ݣ�";
			cin >> number;
			MyRBtree.find(MyRBtree._root, number);
			break;
		case 2: //����
			int nums;
			cout << "������������ݣ�";
			cin >> nums;
		    pos=MyRBtree.insert(MyRBtree._root, nums);
			MyRBtree.ChageColor(pos);
			cout << nums << "�Ѳ���ɹ���" << endl;
			Posi.clear();
			MyRBtree.GetPosi(Posi);
		
			for (int i = 0; i < 10; i++) numb[i] = 0;
			MyRBtree.Count_num(MyRBtree._root, numb, 0);
			MyRBtree.ASL(MyRBtree._root, numb);
			break;
		case 3: //ɾ��
		{	int e;
		cout << "������ɾ�����ݣ�";
		cin >> e;
		int k = Posi.size();
		for (vector<TreeNode*>::iterator it = Posi.begin(); it != Posi.end(); it++) {
			if ((*it)->data == e) {
				cout << "���ҵ�ɾ�����ݣ�" << endl;
				 MyRBtree.remove(*it);
				 cout << e << "��ɾ���ɹ���";
				Posi.clear();
				MyRBtree.GetPosi(Posi);
				cout << endl;
				break;
			}

		}
		if (k == Posi.size()) {
			cout << "δ�ҵ���Ҫɾ�����ݣ�" << endl;
		}

		for (int i = 0; i < 10; i++) numb[i] = 0;
		MyRBtree.Count_num(MyRBtree._root, numb, 0);
		MyRBtree.ASL(MyRBtree._root, numb);

		break;
		}
		case 4://��ʾ
			if (MyRBtree._size == 0) {
				cout << "��Ϊ�գ�" << endl;
				break;
			}
			else {
				
				for (int i = Posi.size() - 1; i >= 0; i--) {
					MyRBtree.Print(Posi[i]);
					
				}
				cout << endl;
				cout << "�����ǣ�" << MyRBtree._root->data << endl;
				break;
			}
		case 5:
			for (int i = 0; i < 10; i++) numb[i] = 0;
			MyRBtree.Count_num(MyRBtree._root, numb, 0);
			for (int i = 0; i < 10; i++) {
				cout<<"��"<<i+1<<"����"<<numb[i]<<"���ڵ�"<<endl;
			}
			MyRBtree.ASL(MyRBtree._root, numb);
			break;
		case 0:
			system("cls");
			exit(0);
		default:
			system("cls");
		}

	}
	
	return 0;
}