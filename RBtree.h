#pragma once
#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
	int data;
	TreeNode* Parent;
	TreeNode* LeftChild;
	TreeNode* RightChild;
	int color;   // 红色为1，黑色为0
	TreeNode();
	TreeNode* InsertAsLC(int e);
	TreeNode* InsertAsRC(int e);
};

class RBtree {
public:
	RBtree();

	//旋转

	//1、左旋 (右右型)
	void LeftRotate(TreeNode* root,TreeNode* x);   

	//2、右旋（左左型）
	void RightRotate(TreeNode* root, TreeNode* x);

	//3、左右旋（左右型）
	void LeftRightRotate(TreeNode* root, TreeNode* x);

	//4、右左旋（右左型）
	void RightLeftRotate(TreeNode* root, TreeNode* x);

	//查找
	TreeNode* find(TreeNode* p,int& e);

	TreeNode* FindPosi(TreeNode* p, int& e);

	//插入
	TreeNode* insert(TreeNode* p,int e);

	//变色
	void ChageColor(TreeNode* p);

	//找到当前节点的直接后继（中序）
	TreeNode* find_next(TreeNode* p);


	//交换两个节点
	void swap(TreeNode* p, TreeNode* q);

	//删除
	int remove(TreeNode* p);

	int remove_left(TreeNode* p);

	int remove_right(TreeNode* p);

	void Balance(TreeNode* p);

	//中序遍历
	void In_Travle(TreeNode* p);


	//得到所有节点位置
	void GetPosi(vector<TreeNode*>& Posi);

	void Print(TreeNode* p);

	//统计每层节点数
	void Count_num(TreeNode* root, int* nums,int k);

	void ASL(TreeNode* root,int* nums);

	TreeNode* _root;    //记录根节点的位置（根节点会因为旋转而改变）

	int _size;
};
