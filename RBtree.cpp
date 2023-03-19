
#include"RBtree.h"
#include<iostream>
#include<cmath>

using namespace std;

TreeNode::TreeNode()
{
	 Parent = NULL; 
	 LeftChild = NULL;
	 RightChild = NULL; 
	 data = -1;
	 color = 1;  //默认节点为红色
}

TreeNode* TreeNode::InsertAsLC(int e)
{
	TreeNode* temp;
	temp = new TreeNode;
	temp->data = e;

	temp->Parent = this;
	this->LeftChild = temp;
	return temp;
}

TreeNode* TreeNode::InsertAsRC(int e)
{
	TreeNode* temp;
	temp = new TreeNode;
	temp->data = e;

	temp->Parent = this;
	this->RightChild = temp;
	return temp;
}


RBtree::RBtree()
{
	this->_size = 0;
	this->_root = NULL;
}

void RBtree::LeftRotate(TreeNode* root,TreeNode* x)
{
	//1、将x的右孩子y作为x的parent节点,x成为y的左孩子；
	//2、将y的左子树接为x的右子树

	TreeNode* y = x->RightChild;

	x->RightChild = y->LeftChild;

	if(y->LeftChild !=NULL)  y->LeftChild->Parent = x;

	y->Parent = x->Parent;

	if (x == _root)    _root= y; //如果x是根
	else if (x == x->Parent->LeftChild)   x->Parent->LeftChild = y;  //x是左孩子
	else x->Parent->RightChild = y;          //x是右孩子

	y->LeftChild = x;
	x->Parent = y;
}

void RBtree::RightRotate(TreeNode* root, TreeNode* x)
{
	//1、将x的左孩子y作为x的parent节点,x成为y的右孩子；
	//2、将y的右子树接为x的左子树

	TreeNode* y = x->LeftChild;

	x->LeftChild = y->RightChild;

	if( y->RightChild !=NULL) y->RightChild->Parent = x;

	y->Parent = x->Parent;

	if (x == _root)   _root = y; //如果x是根
	else if (x == x->Parent->LeftChild)   x->Parent->LeftChild = y;  //x是左孩子
	else x->Parent->RightChild = y;          //x是右孩子

	y->RightChild = x;
	x->Parent = y;

}

void RBtree::LeftRightRotate(TreeNode* root, TreeNode* x)  //传入节点A
{
	this->LeftRotate(root, x->LeftChild);  //B左旋
	this->RightRotate(root, x);           //A右旋
}  

void RBtree::RightLeftRotate(TreeNode* root, TreeNode* x)   //传入A
{
	this->RightRotate(root, x->RightChild); //B右旋
	this->LeftRotate(root, x);              //A左旋
}

TreeNode* RBtree::find(TreeNode* p,int& e)
{   
	if (p == NULL) {

		cout << "未找到！" << endl;
		return p;
	}

	if (p->data == e)   //找到
	{
		cout << p->data << "==" << e << endl;
		cout << "已找到！" << endl;
		return p;
	}
	else {

		if (p->data > e) { //在当前根的左边
	           
			 cout << e << "<" << p->data << " " << endl;
			  return find(p->LeftChild, e);     //去左边寻找
		}

		else {       //在当前根的右边
		cout << e << ">" << p->data << " " << endl;
		  return find(p->RightChild, e);
		}

	}
}

TreeNode* RBtree::FindPosi(TreeNode* p, int& e)
{
	if (p == NULL) {

		return p;
	}

	if (p->data == e)   //找到
	{
		return p;
	}
	else {

		if (p->data > e) { //在当前根的左边

			if (p->LeftChild == NULL)  return p;     //没有左子树
			else   return FindPosi(p->LeftChild, e);     //去左边寻找
		}

		else {       //在当前根的右边

			if (p->RightChild == NULL)  return p;    //没有右子树
			else  return FindPosi(p->RightChild, e);
		}

	}
}

TreeNode* RBtree::insert(TreeNode* p,int e)
{
	
	if (this->_size == 0) {  //插入根节点

		TreeNode* RBtree_root = new TreeNode;
		RBtree_root->data = e;
		RBtree_root->color = 0;
		_root = RBtree_root;
		_size++;
		return  _root;
	}

	TreeNode* posi = FindPosi(p, e);   

	//1、插入到左子树
	 if ( e<=posi->data ) {    
		if (posi->LeftChild == NULL) {    //左子树为空
                                       // 直接插入
			_size++; 
			return posi->InsertAsLC(e);
		}
		else {                             //否则去左子树
			return insert(posi->LeftChild,e);
		}
	
	}
	 //2、插入到右子树同理
	 else {
		 if (posi->RightChild == NULL) {
			 _size++;
			 return posi->InsertAsRC(e);
		 }
		 else {
			 return insert(posi->RightChild, e);
		 }
	 }
	
}

void RBtree::ChageColor(TreeNode* p)
{
	if (p == NULL) {
		//cout << "参数错误！" << endl;
		return;
	}

	if (p == _root) { //1、如果插入的是根节点，染黑即可
		p->color = 0;  
		return ; 
	}
	 
	if (p->Parent->color == 0) {    //2、如果插入节点的父亲是黑色， 不进行处理
		return ;
	}

	//  插入节点的父亲是红色
	if (p->Parent->color == 1  && p->Parent->Parent !=NULL) {
		 //3、并且当前节点的叔叔节点是红色： 
	    //把父节点和叔叔节点改为黑色，把祖父节点改为红色，把祖父节点作为当前节点，向上判断

		 //1、父亲为右孩子，左叔叔存在且为红
		if ( p->Parent == p->Parent->Parent->RightChild && p->Parent->Parent->LeftChild != NULL && p->Parent->Parent->LeftChild->color == 1) {

			p->Parent->color = 0;
			p->Parent->Parent->LeftChild->color = 0;
			p->Parent->Parent->color = 1;

		return  ChageColor(p->Parent->Parent);
		}
		//2、父亲为左孩子，右叔叔存在且为红
		if (p->Parent == p->Parent->Parent->LeftChild && p->Parent->Parent->RightChild != NULL && p->Parent->Parent->RightChild->color == 1) {
			p->Parent->color = 0;
			p->Parent->Parent->RightChild->color = 0;
			p->Parent->Parent->color = 1;

		 return  ChageColor(p->Parent->Parent);
		}

		//当前节点的叔叔节点不是红色，则分为以下四种情况：

		//父亲是祖父的右孩子，当前节点是父亲的右孩子
		if ((p->Parent->Parent->LeftChild == NULL || p->Parent->Parent->LeftChild->color == 0) && p->Parent->Parent->RightChild == p->Parent && p == p->Parent->RightChild) {

			//做左旋处理，再把父节点改为黑色，之前的祖父节点改为红色
			p->Parent->Parent->color = 1;
			p->Parent->color = 0;

			this->LeftRotate(_root, p->Parent->Parent);
			return;
		 }
		//父亲是祖父的左孩子，当前节点是父亲的左孩子
		if ((p->Parent->Parent->RightChild == NULL || p->Parent->Parent->RightChild->color == 0) && p->Parent->Parent->LeftChild == p->Parent && p == p->Parent->LeftChild) {

			//做右旋处理，再把父节点改为黑色，之前的祖父节点改为红色
			p->Parent->Parent->color = 1;
			p->Parent->color = 0;

			this->RightRotate(_root, p->Parent->Parent);
			return ;
		}

		//父亲是祖父的左孩子，当前节点是父亲的右孩子
		if ((p->Parent->Parent->RightChild == NULL || p->Parent->Parent->RightChild->color == 0) && p->Parent->Parent->LeftChild == p->Parent && p == p->Parent->RightChild) {

			//先左旋，再右旋，然后将当前节点改为黑色，之前的祖父节点改为红色
			p->color = 0;
			p->Parent->Parent->color = 1;

			this->LeftRightRotate(_root, p->Parent->Parent);
			return ;
		}

		//父亲是祖父的右孩子，当前节点是父亲的左孩子
		if ((p->Parent->Parent->LeftChild == NULL || p->Parent->Parent->LeftChild->color == 0) && p->Parent->Parent->RightChild == p->Parent && p == p->Parent->LeftChild) {

			//先右旋，再左旋，然后将当前节点改为黑色，之前的祖父节点改为红色
			p->color = 0;
			p->Parent->Parent->color = 1;

			this->RightLeftRotate(_root, p->Parent->Parent);
			return ;
		}

	}
}

TreeNode* RBtree::find_next(TreeNode* p)
{
	TreeNode* Posi[100];
	int k = 0;
	TreeNode* Stack[100];   //辅助栈
	int top = -1;   //栈顶指针
	TreeNode* temp = _root;
	top++;
	Stack[top] = temp;
	temp = temp->LeftChild;

	while ( 1 ) {
		while ( temp != NULL) {
			top++;
			Stack[top] = temp;
			temp = temp->LeftChild;
		}
		if (top == -1)  break;

		temp = Stack[top];
		top--;

		Posi[k] = temp;
		k++;

		temp = temp->RightChild;
	}

	for (int i = 0; i < k; i++)
	{
		if (Posi[i] == p  && i<k-1) {

			cout << "后继为：" << Posi[i+1]->data;
			return Posi[i + 1];
		 }
	}

	cout << "未找到后继！" << endl;
	return NULL;
}

void RBtree::In_Travle(TreeNode* p)
{
	if (p == NULL)  return;

	In_Travle(p->LeftChild);

	//cout << "数据是：" << p->data << "颜色是：" << p->color << endl;
	this->Print(p);

	In_Travle(p->RightChild);

}

void RBtree::swap(TreeNode* p, TreeNode* q)
{
	TreeNode* temp = p;
	p->data = q->data;
	q->data = temp->data;
}

void RBtree::Balance(TreeNode* p)
{
	if (p==NULL ||p == _root || p->color == 1 ) return;

	
	//父亲是红色，兄弟和兄弟的孩子（只能是叶子）是黑色
	if (p->Parent->color == 1) {
		//将父亲改为黑色，将兄弟改为红色
		if (p == p->Parent->LeftChild && (p->Parent->RightChild == NULL || p->Parent->RightChild->color == 0)) {	
			p->Parent->color = 0;
			if (p->Parent->RightChild != NULL)
				p->Parent->RightChild->color = 1;
			return;
		}
		if (p == p->Parent->RightChild && (p->Parent->LeftChild == NULL || p->Parent->LeftChild->color == 0)) {
			p->Parent->color = 0;
			if (p->Parent->LeftChild != NULL)
				p->Parent->LeftChild->color = 1;
			return;
		}

	}
	
	if (p->Parent->color == 0) {
		//将兄弟改为红色，并将父亲作为待平衡的节点往上回溯；
		if (p == p->Parent->LeftChild && p->Parent->RightChild->color == 0 && (p->Parent->RightChild->LeftChild == NULL || p->Parent->RightChild->LeftChild->color == 0) && (p->Parent->RightChild->RightChild == NULL || p->Parent->RightChild->RightChild->color == 0)) {

			p->Parent->RightChild->color = 1;
		
			return this->Balance(p->Parent);
		}

		else if (p == p->Parent->RightChild && p->Parent->LeftChild->color == 0 && (p->Parent->LeftChild->LeftChild == NULL || p->Parent->LeftChild->LeftChild->color == 0) && (p->Parent->LeftChild->RightChild == NULL || p->Parent->LeftChild->RightChild->color == 0)) {

			p->Parent->LeftChild->color = 1;
		
			return this->Balance(p->Parent);

		}
	}

	//待删除节点的兄弟节点是红色
	// 将父亲节点与兄弟节点的颜色互换，然后对父亲节点进行左旋操作，则p节点兄弟变为黑色
	if (p == p->Parent->LeftChild && (p->Parent->RightChild != NULL && p->Parent->RightChild->color == 1)) { //p是左孩子
	
		int color = p->Parent->color;
		p->Parent->color = p->Parent->RightChild->color;
		p->Parent->RightChild->color = color;
		this->LeftRotate(_root, p->Parent);
		return  ;
	}
	if (p == p->Parent->RightChild && (p->Parent->LeftChild != NULL && p->Parent->LeftChild->color == 1)) { //p是右孩子
		int color = p->Parent->color;
		p->Parent->color = p->Parent->LeftChild->color;
		p->Parent->LeftChild->color = color;
		this->RightRotate(_root, p->Parent);
		return ;
	}
	
	//兄弟节点是黑色，远侄子节点是黑色，且近侄子节点是红色
	// 对兄弟右旋，并将兄弟与它的左孩子颜色互换，则变为情况2
	if (p == p->Parent->LeftChild && p->Parent->RightChild->color == 0 && (p->Parent->RightChild->RightChild == NULL || p->Parent->RightChild->RightChild->color == 0) && (p->Parent->RightChild->LeftChild != NULL && p->Parent->RightChild->LeftChild->color == 1)) {
		
		
		int color = p->Parent->RightChild->color;
		p->Parent->RightChild->color = p->Parent->RightChild->LeftChild->color;
		p->Parent->RightChild->LeftChild->color = color;
		this->RightRotate(_root, p->Parent->RightChild);
		return   ;
	}
	if (p == p->Parent->RightChild && p->Parent->LeftChild->color == 0 && (p->Parent->LeftChild->LeftChild == NULL || p->Parent->LeftChild->LeftChild->color == 0) && (p->Parent->LeftChild->RightChild != NULL && p->Parent->LeftChild->RightChild->color == 1)) {
		int color = p->Parent->LeftChild->color;
		p->Parent->LeftChild->color = p->Parent->LeftChild->RightChild->color;
		p->Parent->LeftChild->RightChild->color = color;
		this->LeftRotate(_root, p->Parent->LeftChild);
		return  ;
	}
	

	//兄弟节点为黑色，且远侄子节点为红色
	// 将父亲和兄弟颜色对调，然后对父亲左旋，最后把远侄子变为黑色
	if (p == p->Parent->LeftChild && p->Parent->RightChild->color == 0 && (p->Parent->RightChild->RightChild != NULL && p->Parent->RightChild->RightChild->color == 1)) {
		
		int color = p->Parent->color;
		p->Parent->color = p->Parent->RightChild->color;
		p->Parent->RightChild->color = color;
		p->Parent->RightChild->RightChild->color = 0;  //多此一步
		this->LeftRotate(_root, p->Parent);
		return ;
	}
	if (p == p->Parent->RightChild && p->Parent->LeftChild->color == 0 && (p->Parent->LeftChild->LeftChild != NULL && p->Parent->LeftChild->LeftChild->color == 1)) {
		int color = p->Parent->color;
		p->Parent->color = p->Parent->LeftChild->color;
		p->Parent->LeftChild->color = color;
		p->Parent->LeftChild->LeftChild->color = 0;
		this->RightRotate(_root, p->Parent);
		return  ;
	}

	
}

int RBtree::remove(TreeNode* p)
{
	if (p == NULL) return -1;

	int _data;

	// 删除红色节点
	if (p->color == 1) {

		//1、删除节点为叶子节点的parent，直接删除
		if (p->LeftChild == NULL && p->RightChild == NULL) {

			if (p == p->Parent->LeftChild) {    //左孩子
				p->Parent->LeftChild = NULL;
				_data = p->data;
				delete p;
				_size--;
				return _data;
			}
			else {   //右孩子
				p->Parent->RightChild = NULL;
				_data = p->data;
				delete p;
				_size--;
				return _data;
			}
		}
		//2、删除红色的非1情况节点，根据红黑树的性质只会出现节点左右子树均存在，先找到其直接后继（next）并用它的值取代被删除节点的值，然后按情况1删除
		if (p->LeftChild != NULL && p->RightChild != NULL)
		{
			TreeNode* next = this->find_next(p);
			swap(p, next);

			return remove(next);
		}

		if (p->LeftChild != NULL && p->RightChild == NULL) {

			if (p == p->Parent->LeftChild) {
				p->Parent->LeftChild = p->LeftChild;
				p->LeftChild->Parent = p->Parent;
				_data = p->data;
				delete p;
				_size--;
				return _data;
			}
			else {
				p->Parent->RightChild = p->LeftChild;
				p->LeftChild->Parent = p->Parent;
				_data = p->data;
				delete p;
				_size--;
				return _data;
			}
		}

		if (p->LeftChild == NULL && p->RightChild != NULL) {
			if (p = p->Parent->LeftChild) {
				p->Parent->LeftChild = p->RightChild;
				p->RightChild->Parent = p->Parent;
				_data = p->data;
				delete p;
				_size--;
				return _data;
			}
			else {
				p->Parent->RightChild = p->RightChild;
				p->RightChild->Parent = p->Parent;
				_data = p->data;
				delete p;
				_size--;
				return _data;
			}
		}
	}

	//删除黑色节点
	else  {

		// 待删除黑色节点左右子树至少存在一个
		if (p->LeftChild != NULL || p->RightChild != NULL) {

			if (p->LeftChild != NULL && p->RightChild != NULL) {  //左右子树都存在
				TreeNode* next = this->find_next(p);
				swap(p, next);
			//	this->_root->color = 0;
				return remove(next);
			}
			else if (p->LeftChild == NULL) {  //左子树为空
				if (p == this->_root) {   //如果是根
					_root = p->RightChild;
					p->RightChild->Parent = NULL;
					_data = p->data;
					delete p;
					//_root->color = 0;
					_size--;
					return _data;
				}
				if (p != this->_root) {    //不是根
					if (p == p->Parent->LeftChild) {
						p->Parent->LeftChild = p->RightChild;
						p->RightChild->color = 0;
						p->RightChild->Parent = p->Parent;
						_data = p->data;
						delete p;
						_size--;
						return _data;
					}
					else {
						p->Parent->RightChild = p->RightChild;
						p->RightChild->color = 0;
						p->RightChild->Parent = p->Parent;
						_data = p->data;
						delete p;
						_size--;
						return _data;
					}
				}

			}
			else {  //右子树为空
				if (p == this->_root) {
					this->_root = p->LeftChild;
					p->LeftChild->Parent = NULL;
					_data = p->data;
					this->_root->color = 0;
					delete p;
					_size--;
					return _data;
				}
				else {
					if (p == p->Parent->LeftChild) {    //p是左孩子
						p->Parent->LeftChild = p->LeftChild;
						p->LeftChild->color = 0;
						p->LeftChild->Parent = p->Parent;
						_data = p->data;
						delete p;
						_size--;
						return _data;
					}
					else {  //p是右孩子
						p->Parent->RightChild = p->LeftChild;
						p->LeftChild->color = 0;
						p->LeftChild->Parent = p->Parent;
						_data = p->data;
						delete p;
						_size--;
						return _data;
					}

				}
			}
		}

		// 删除黑色的叶子节点parent
		if (p->LeftChild == NULL && p->RightChild == NULL) {

			//整棵树只有根
			if (this->_size == 1) {
				_data = p->data;
				delete p;
				_size--;
				_root = NULL;
				return _data;
			}
          
			//父亲、兄弟和兄弟的孩子（只能是叶子）都为黑色
			if (p->Parent->color == 0) {
				//将兄弟改为红色，并将父亲作为待平衡的节点往上回溯；
				if (p == p->Parent->LeftChild && p->Parent->RightChild->color == 0 && (p->Parent->RightChild->LeftChild == NULL || p->Parent->RightChild->LeftChild ->color == 0) && ( p->Parent ->RightChild ->RightChild ==NULL || p->Parent ->RightChild ->RightChild ->color ==0)) {

					p->Parent->RightChild->color = 1;

					this->Balance(p->Parent);

					p->Parent->LeftChild = NULL;
					_data = p->data; 
					p->Parent = NULL;
					_size--;
					delete p;
					return _data;

				}

				else if (p == p->Parent->RightChild && p->Parent->LeftChild->color == 0 && (p->Parent ->LeftChild ->LeftChild ==NULL || p->Parent ->LeftChild ->LeftChild ->color ==0) && (p->Parent ->LeftChild ->RightChild ==NULL || p->Parent ->LeftChild ->RightChild ->color ==0)) {

					p->Parent->LeftChild->color = 1;

					this->Balance(p->Parent);

					_data = p->data;
					p->Parent->RightChild = NULL;
					p->Parent = NULL;
					_size--;
					delete p;
					return _data;
					
				}
			}
			
			 
			//兄弟节点是黑色，远侄子节点是黑色，且近侄子节点是红色
			if (p == p->Parent->LeftChild && p->Parent->RightChild->color == 0 && (p->Parent->RightChild->RightChild == NULL || p->Parent->RightChild->RightChild->color == 0) && (p->Parent->RightChild->LeftChild != NULL && p->Parent->RightChild->LeftChild->color == 1)) {
				//
				// 对兄弟右旋，并将兄弟与它的左孩子颜色互换，则变为情况2
				int color = p->Parent->RightChild->color;
				p->Parent->RightChild->color = p->Parent->RightChild->LeftChild->color;
				p->Parent->RightChild->LeftChild->color = color;
				this->RightRotate(_root, p->Parent->RightChild);
				return remove(p);

			}
			if (p == p->Parent->RightChild && p->Parent->LeftChild->color == 0 && (p->Parent->LeftChild->LeftChild == NULL || p->Parent->LeftChild->LeftChild->color == 0) && (p->Parent->LeftChild->RightChild != NULL && p->Parent->LeftChild->RightChild->color == 1)) {
				int color = p->Parent->LeftChild->color;
				p->Parent->LeftChild->color = p->Parent->LeftChild->RightChild->color;
				p->Parent->LeftChild->RightChild->color = color;
				this->LeftRotate(_root, p->Parent->LeftChild);
				return remove(p);
			}



			this->Balance(p);
			if (p == p->Parent->LeftChild) return this->remove_left(p);
			else  return this->remove_right(p);


		

		}

	}


	cout << "出乎所有情况！";
	cout << "父节点是：" << p->Parent->data << " " << "颜色是：" << p->Parent->color << endl;
	return -1;
}

int RBtree::remove_left(TreeNode* p)
{
	int _data;
	_data = p->data;
	p->Parent->LeftChild = NULL;
	_size--;
	delete p;
	return _data;
}

int RBtree::remove_right(TreeNode* p)
{
	int _data;
	_data = p->data;
	p->Parent->RightChild = NULL;
	_size--;
	delete p;
	return _data;
}

void RBtree::GetPosi(vector<TreeNode*>& Posi)
{
	TreeNode* *Stack;
	Stack = new TreeNode*[_size];
	int top = -1;
	TreeNode* temp = this->_root;

	while (1) {

		while (temp != NULL) {
			top++;
			Stack[top] = temp;
			temp = temp->LeftChild;
		}

		if (top == -1) break;

		temp = Stack[top];
		top--;

		Posi.push_back(temp);

		temp = temp->RightChild;
	}
}

void RBtree::Print(TreeNode* p)
{
	if (p == NULL) return;

	cout << "数据是：" << p->data << " 颜色是：" << p->color<<"(";

	if (p->LeftChild != NULL) {
		cout << "左孩子是:" << p->LeftChild->data << "颜色是：" ;
		if (p->LeftChild->color == 0) cout << "黑";
		else  cout << "红";
	}
	else
		cout << "左孩子为空";

	cout << ",";

	if (p->RightChild != NULL) {
		cout << "右孩子是：" << p->RightChild->data << " 颜色是:" ;
		if (p->RightChild->color == 0) cout << "黑";
		else cout << "红";
	}
	else
		cout << "右孩子为空";

	cout << ")" << endl;
}

void RBtree::Count_num(TreeNode* root, int* nums,int k)
{
	if (root == NULL) return;

	nums[k]++;

	Count_num(root->LeftChild, nums, k + 1);
	Count_num(root->RightChild, nums, k + 1);
}

void RBtree::ASL(TreeNode* root,int* nums)
{
	int sumsucc = 0;
	int sumunsucc = 0;
	for (int i = 0; i < 10; i++) {

		if (nums[i] == 0) break;

		sumsucc = sumsucc + (i + 1) * nums[i];
		sumunsucc = sumunsucc +(2*nums[i] - nums[i+1]) * (i+1);
	}

	cout << "ASL_succ=" << sumsucc << "/" << this->_size << endl;
	cout << "ASL_unsucc=" << sumunsucc<< "/" << this->_size + 1 << endl;
}

