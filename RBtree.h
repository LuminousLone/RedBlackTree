#pragma once
#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
	int data;
	TreeNode* Parent;
	TreeNode* LeftChild;
	TreeNode* RightChild;
	int color;   // ��ɫΪ1����ɫΪ0
	TreeNode();
	TreeNode* InsertAsLC(int e);
	TreeNode* InsertAsRC(int e);
};

class RBtree {
public:
	RBtree();

	//��ת

	//1������ (������)
	void LeftRotate(TreeNode* root,TreeNode* x);   

	//2�������������ͣ�
	void RightRotate(TreeNode* root, TreeNode* x);

	//3���������������ͣ�
	void LeftRightRotate(TreeNode* root, TreeNode* x);

	//4���������������ͣ�
	void RightLeftRotate(TreeNode* root, TreeNode* x);

	//����
	TreeNode* find(TreeNode* p,int& e);

	TreeNode* FindPosi(TreeNode* p, int& e);

	//����
	TreeNode* insert(TreeNode* p,int e);

	//��ɫ
	void ChageColor(TreeNode* p);

	//�ҵ���ǰ�ڵ��ֱ�Ӻ�̣�����
	TreeNode* find_next(TreeNode* p);


	//���������ڵ�
	void swap(TreeNode* p, TreeNode* q);

	//ɾ��
	int remove(TreeNode* p);

	int remove_left(TreeNode* p);

	int remove_right(TreeNode* p);

	void Balance(TreeNode* p);

	//�������
	void In_Travle(TreeNode* p);


	//�õ����нڵ�λ��
	void GetPosi(vector<TreeNode*>& Posi);

	void Print(TreeNode* p);

	//ͳ��ÿ��ڵ���
	void Count_num(TreeNode* root, int* nums,int k);

	void ASL(TreeNode* root,int* nums);

	TreeNode* _root;    //��¼���ڵ��λ�ã����ڵ����Ϊ��ת���ı䣩

	int _size;
};
