
#include<iostream>
#include<ctime>
#include<vector>
#include<algorithm>
#include"RBtree.h"
using namespace std;

int Show()
{   
	cout << "----------------------" << endl;
	cout << "1、检索" << endl;
	cout << "2、插入" << endl;
	cout << "3、删除" << endl;
	cout << "4、按值递减显示" << endl;
	cout << "5、显示平均查找长度" << endl;
	cout << "0、退出" << endl;
	cout << "请选择：";
	int choice = -1;
	cin >> choice;
	cout << "------------------------" << endl;
	return choice;
}

int main()
{
	srand((unsigned int)time(NULL));   //设置随机数种子

	int nums[1000];      //插入10个数

	int k;
	cout << "请输入个数：" << endl;
	cin >> k;

	RBtree MyRBtree;

	vector<TreeNode*> Posi;

	TreeNode* pos = NULL;

	for (int i = 0; i < k; i++)
	{
		nums[i] = rand() % 21 ;    //0到20的随机数
		cout << nums[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < k; i++) {
		cout << "--------------------" << endl;
		cout << "插入到第：" << i << "个数: "<<nums[i]<< endl;
		//cout << "插入到第：" << i << "个数: " << i+1 << endl;
	    pos =	MyRBtree.insert(MyRBtree._root,nums[i]);
		//pos = MyRBtree.insert(MyRBtree._root, i+1);
		MyRBtree.ChageColor(pos);
		MyRBtree.In_Travle(MyRBtree._root);
		cout << "树根是：" << MyRBtree._root->data << endl;
		cout << "-------------------" << endl;
	}
	cout << "插入完毕！" << endl;
	MyRBtree.GetPosi(Posi);

	int numb[10];  //存储每层的节点数用于计算平均查找长度

	while (1) {

		int choice = Show();

		switch (choice)
		{
		case 1:
			int number;
			cout << "请输入检索数据：";
			cin >> number;
			MyRBtree.find(MyRBtree._root, number);
			break;
		case 2: //插入
			int nums;
			cout << "请输入插入数据：";
			cin >> nums;
		    pos=MyRBtree.insert(MyRBtree._root, nums);
			MyRBtree.ChageColor(pos);
			cout << nums << "已插入成功！" << endl;
			Posi.clear();
			MyRBtree.GetPosi(Posi);
		
			for (int i = 0; i < 10; i++) numb[i] = 0;
			MyRBtree.Count_num(MyRBtree._root, numb, 0);
			MyRBtree.ASL(MyRBtree._root, numb);
			break;
		case 3: //删除
		{	int e;
		cout << "请输入删除数据：";
		cin >> e;
		int k = Posi.size();
		for (vector<TreeNode*>::iterator it = Posi.begin(); it != Posi.end(); it++) {
			if ((*it)->data == e) {
				cout << "已找到删除数据！" << endl;
				 MyRBtree.remove(*it);
				 cout << e << "已删除成功！";
				Posi.clear();
				MyRBtree.GetPosi(Posi);
				cout << endl;
				break;
			}

		}
		if (k == Posi.size()) {
			cout << "未找到需要删除数据！" << endl;
		}

		for (int i = 0; i < 10; i++) numb[i] = 0;
		MyRBtree.Count_num(MyRBtree._root, numb, 0);
		MyRBtree.ASL(MyRBtree._root, numb);

		break;
		}
		case 4://显示
			if (MyRBtree._size == 0) {
				cout << "树为空！" << endl;
				break;
			}
			else {
				
				for (int i = Posi.size() - 1; i >= 0; i--) {
					MyRBtree.Print(Posi[i]);
					
				}
				cout << endl;
				cout << "树根是：" << MyRBtree._root->data << endl;
				break;
			}
		case 5:
			for (int i = 0; i < 10; i++) numb[i] = 0;
			MyRBtree.Count_num(MyRBtree._root, numb, 0);
			for (int i = 0; i < 10; i++) {
				cout<<"第"<<i+1<<"层有"<<numb[i]<<"个节点"<<endl;
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