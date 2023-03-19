
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
	 color = 1;  //Ĭ�Ͻڵ�Ϊ��ɫ
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
	//1����x���Һ���y��Ϊx��parent�ڵ�,x��Ϊy�����ӣ�
	//2����y����������Ϊx��������

	TreeNode* y = x->RightChild;

	x->RightChild = y->LeftChild;

	if(y->LeftChild !=NULL)  y->LeftChild->Parent = x;

	y->Parent = x->Parent;

	if (x == _root)    _root= y; //���x�Ǹ�
	else if (x == x->Parent->LeftChild)   x->Parent->LeftChild = y;  //x������
	else x->Parent->RightChild = y;          //x���Һ���

	y->LeftChild = x;
	x->Parent = y;
}

void RBtree::RightRotate(TreeNode* root, TreeNode* x)
{
	//1����x������y��Ϊx��parent�ڵ�,x��Ϊy���Һ��ӣ�
	//2����y����������Ϊx��������

	TreeNode* y = x->LeftChild;

	x->LeftChild = y->RightChild;

	if( y->RightChild !=NULL) y->RightChild->Parent = x;

	y->Parent = x->Parent;

	if (x == _root)   _root = y; //���x�Ǹ�
	else if (x == x->Parent->LeftChild)   x->Parent->LeftChild = y;  //x������
	else x->Parent->RightChild = y;          //x���Һ���

	y->RightChild = x;
	x->Parent = y;

}

void RBtree::LeftRightRotate(TreeNode* root, TreeNode* x)  //����ڵ�A
{
	this->LeftRotate(root, x->LeftChild);  //B����
	this->RightRotate(root, x);           //A����
}  

void RBtree::RightLeftRotate(TreeNode* root, TreeNode* x)   //����A
{
	this->RightRotate(root, x->RightChild); //B����
	this->LeftRotate(root, x);              //A����
}

TreeNode* RBtree::find(TreeNode* p,int& e)
{   
	if (p == NULL) {

		cout << "δ�ҵ���" << endl;
		return p;
	}

	if (p->data == e)   //�ҵ�
	{
		cout << p->data << "==" << e << endl;
		cout << "���ҵ���" << endl;
		return p;
	}
	else {

		if (p->data > e) { //�ڵ�ǰ�������
	           
			 cout << e << "<" << p->data << " " << endl;
			  return find(p->LeftChild, e);     //ȥ���Ѱ��
		}

		else {       //�ڵ�ǰ�����ұ�
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

	if (p->data == e)   //�ҵ�
	{
		return p;
	}
	else {

		if (p->data > e) { //�ڵ�ǰ�������

			if (p->LeftChild == NULL)  return p;     //û��������
			else   return FindPosi(p->LeftChild, e);     //ȥ���Ѱ��
		}

		else {       //�ڵ�ǰ�����ұ�

			if (p->RightChild == NULL)  return p;    //û��������
			else  return FindPosi(p->RightChild, e);
		}

	}
}

TreeNode* RBtree::insert(TreeNode* p,int e)
{
	
	if (this->_size == 0) {  //������ڵ�

		TreeNode* RBtree_root = new TreeNode;
		RBtree_root->data = e;
		RBtree_root->color = 0;
		_root = RBtree_root;
		_size++;
		return  _root;
	}

	TreeNode* posi = FindPosi(p, e);   

	//1�����뵽������
	 if ( e<=posi->data ) {    
		if (posi->LeftChild == NULL) {    //������Ϊ��
                                       // ֱ�Ӳ���
			_size++; 
			return posi->InsertAsLC(e);
		}
		else {                             //����ȥ������
			return insert(posi->LeftChild,e);
		}
	
	}
	 //2�����뵽������ͬ��
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
		//cout << "��������" << endl;
		return;
	}

	if (p == _root) { //1�����������Ǹ��ڵ㣬Ⱦ�ڼ���
		p->color = 0;  
		return ; 
	}
	 
	if (p->Parent->color == 0) {    //2���������ڵ�ĸ����Ǻ�ɫ�� �����д���
		return ;
	}

	//  ����ڵ�ĸ����Ǻ�ɫ
	if (p->Parent->color == 1  && p->Parent->Parent !=NULL) {
		 //3�����ҵ�ǰ�ڵ������ڵ��Ǻ�ɫ�� 
	    //�Ѹ��ڵ������ڵ��Ϊ��ɫ�����游�ڵ��Ϊ��ɫ�����游�ڵ���Ϊ��ǰ�ڵ㣬�����ж�

		 //1������Ϊ�Һ��ӣ������������Ϊ��
		if ( p->Parent == p->Parent->Parent->RightChild && p->Parent->Parent->LeftChild != NULL && p->Parent->Parent->LeftChild->color == 1) {

			p->Parent->color = 0;
			p->Parent->Parent->LeftChild->color = 0;
			p->Parent->Parent->color = 1;

		return  ChageColor(p->Parent->Parent);
		}
		//2������Ϊ���ӣ������������Ϊ��
		if (p->Parent == p->Parent->Parent->LeftChild && p->Parent->Parent->RightChild != NULL && p->Parent->Parent->RightChild->color == 1) {
			p->Parent->color = 0;
			p->Parent->Parent->RightChild->color = 0;
			p->Parent->Parent->color = 1;

		 return  ChageColor(p->Parent->Parent);
		}

		//��ǰ�ڵ������ڵ㲻�Ǻ�ɫ�����Ϊ�������������

		//�������游���Һ��ӣ���ǰ�ڵ��Ǹ��׵��Һ���
		if ((p->Parent->Parent->LeftChild == NULL || p->Parent->Parent->LeftChild->color == 0) && p->Parent->Parent->RightChild == p->Parent && p == p->Parent->RightChild) {

			//�����������ٰѸ��ڵ��Ϊ��ɫ��֮ǰ���游�ڵ��Ϊ��ɫ
			p->Parent->Parent->color = 1;
			p->Parent->color = 0;

			this->LeftRotate(_root, p->Parent->Parent);
			return;
		 }
		//�������游�����ӣ���ǰ�ڵ��Ǹ��׵�����
		if ((p->Parent->Parent->RightChild == NULL || p->Parent->Parent->RightChild->color == 0) && p->Parent->Parent->LeftChild == p->Parent && p == p->Parent->LeftChild) {

			//�����������ٰѸ��ڵ��Ϊ��ɫ��֮ǰ���游�ڵ��Ϊ��ɫ
			p->Parent->Parent->color = 1;
			p->Parent->color = 0;

			this->RightRotate(_root, p->Parent->Parent);
			return ;
		}

		//�������游�����ӣ���ǰ�ڵ��Ǹ��׵��Һ���
		if ((p->Parent->Parent->RightChild == NULL || p->Parent->Parent->RightChild->color == 0) && p->Parent->Parent->LeftChild == p->Parent && p == p->Parent->RightChild) {

			//����������������Ȼ�󽫵�ǰ�ڵ��Ϊ��ɫ��֮ǰ���游�ڵ��Ϊ��ɫ
			p->color = 0;
			p->Parent->Parent->color = 1;

			this->LeftRightRotate(_root, p->Parent->Parent);
			return ;
		}

		//�������游���Һ��ӣ���ǰ�ڵ��Ǹ��׵�����
		if ((p->Parent->Parent->LeftChild == NULL || p->Parent->Parent->LeftChild->color == 0) && p->Parent->Parent->RightChild == p->Parent && p == p->Parent->LeftChild) {

			//����������������Ȼ�󽫵�ǰ�ڵ��Ϊ��ɫ��֮ǰ���游�ڵ��Ϊ��ɫ
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
	TreeNode* Stack[100];   //����ջ
	int top = -1;   //ջ��ָ��
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

			cout << "���Ϊ��" << Posi[i+1]->data;
			return Posi[i + 1];
		 }
	}

	cout << "δ�ҵ���̣�" << endl;
	return NULL;
}

void RBtree::In_Travle(TreeNode* p)
{
	if (p == NULL)  return;

	In_Travle(p->LeftChild);

	//cout << "�����ǣ�" << p->data << "��ɫ�ǣ�" << p->color << endl;
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

	
	//�����Ǻ�ɫ���ֵܺ��ֵܵĺ��ӣ�ֻ����Ҷ�ӣ��Ǻ�ɫ
	if (p->Parent->color == 1) {
		//�����׸�Ϊ��ɫ�����ֵܸ�Ϊ��ɫ
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
		//���ֵܸ�Ϊ��ɫ������������Ϊ��ƽ��Ľڵ����ϻ��ݣ�
		if (p == p->Parent->LeftChild && p->Parent->RightChild->color == 0 && (p->Parent->RightChild->LeftChild == NULL || p->Parent->RightChild->LeftChild->color == 0) && (p->Parent->RightChild->RightChild == NULL || p->Parent->RightChild->RightChild->color == 0)) {

			p->Parent->RightChild->color = 1;
		
			return this->Balance(p->Parent);
		}

		else if (p == p->Parent->RightChild && p->Parent->LeftChild->color == 0 && (p->Parent->LeftChild->LeftChild == NULL || p->Parent->LeftChild->LeftChild->color == 0) && (p->Parent->LeftChild->RightChild == NULL || p->Parent->LeftChild->RightChild->color == 0)) {

			p->Parent->LeftChild->color = 1;
		
			return this->Balance(p->Parent);

		}
	}

	//��ɾ���ڵ���ֵܽڵ��Ǻ�ɫ
	// �����׽ڵ����ֵܽڵ����ɫ������Ȼ��Ը��׽ڵ����������������p�ڵ��ֵܱ�Ϊ��ɫ
	if (p == p->Parent->LeftChild && (p->Parent->RightChild != NULL && p->Parent->RightChild->color == 1)) { //p������
	
		int color = p->Parent->color;
		p->Parent->color = p->Parent->RightChild->color;
		p->Parent->RightChild->color = color;
		this->LeftRotate(_root, p->Parent);
		return  ;
	}
	if (p == p->Parent->RightChild && (p->Parent->LeftChild != NULL && p->Parent->LeftChild->color == 1)) { //p���Һ���
		int color = p->Parent->color;
		p->Parent->color = p->Parent->LeftChild->color;
		p->Parent->LeftChild->color = color;
		this->RightRotate(_root, p->Parent);
		return ;
	}
	
	//�ֵܽڵ��Ǻ�ɫ��Զֶ�ӽڵ��Ǻ�ɫ���ҽ�ֶ�ӽڵ��Ǻ�ɫ
	// ���ֵ������������ֵ�������������ɫ���������Ϊ���2
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
	

	//�ֵܽڵ�Ϊ��ɫ����Զֶ�ӽڵ�Ϊ��ɫ
	// �����׺��ֵ���ɫ�Ե���Ȼ��Ը�������������Զֶ�ӱ�Ϊ��ɫ
	if (p == p->Parent->LeftChild && p->Parent->RightChild->color == 0 && (p->Parent->RightChild->RightChild != NULL && p->Parent->RightChild->RightChild->color == 1)) {
		
		int color = p->Parent->color;
		p->Parent->color = p->Parent->RightChild->color;
		p->Parent->RightChild->color = color;
		p->Parent->RightChild->RightChild->color = 0;  //���һ��
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

	// ɾ����ɫ�ڵ�
	if (p->color == 1) {

		//1��ɾ���ڵ�ΪҶ�ӽڵ��parent��ֱ��ɾ��
		if (p->LeftChild == NULL && p->RightChild == NULL) {

			if (p == p->Parent->LeftChild) {    //����
				p->Parent->LeftChild = NULL;
				_data = p->data;
				delete p;
				_size--;
				return _data;
			}
			else {   //�Һ���
				p->Parent->RightChild = NULL;
				_data = p->data;
				delete p;
				_size--;
				return _data;
			}
		}
		//2��ɾ����ɫ�ķ�1����ڵ㣬���ݺ����������ֻ����ֽڵ��������������ڣ����ҵ���ֱ�Ӻ�̣�next����������ֵȡ����ɾ���ڵ��ֵ��Ȼ�����1ɾ��
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

	//ɾ����ɫ�ڵ�
	else  {

		// ��ɾ����ɫ�ڵ������������ٴ���һ��
		if (p->LeftChild != NULL || p->RightChild != NULL) {

			if (p->LeftChild != NULL && p->RightChild != NULL) {  //��������������
				TreeNode* next = this->find_next(p);
				swap(p, next);
			//	this->_root->color = 0;
				return remove(next);
			}
			else if (p->LeftChild == NULL) {  //������Ϊ��
				if (p == this->_root) {   //����Ǹ�
					_root = p->RightChild;
					p->RightChild->Parent = NULL;
					_data = p->data;
					delete p;
					//_root->color = 0;
					_size--;
					return _data;
				}
				if (p != this->_root) {    //���Ǹ�
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
			else {  //������Ϊ��
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
					if (p == p->Parent->LeftChild) {    //p������
						p->Parent->LeftChild = p->LeftChild;
						p->LeftChild->color = 0;
						p->LeftChild->Parent = p->Parent;
						_data = p->data;
						delete p;
						_size--;
						return _data;
					}
					else {  //p���Һ���
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

		// ɾ����ɫ��Ҷ�ӽڵ�parent
		if (p->LeftChild == NULL && p->RightChild == NULL) {

			//������ֻ�и�
			if (this->_size == 1) {
				_data = p->data;
				delete p;
				_size--;
				_root = NULL;
				return _data;
			}
          
			//���ס��ֵܺ��ֵܵĺ��ӣ�ֻ����Ҷ�ӣ���Ϊ��ɫ
			if (p->Parent->color == 0) {
				//���ֵܸ�Ϊ��ɫ������������Ϊ��ƽ��Ľڵ����ϻ��ݣ�
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
			
			 
			//�ֵܽڵ��Ǻ�ɫ��Զֶ�ӽڵ��Ǻ�ɫ���ҽ�ֶ�ӽڵ��Ǻ�ɫ
			if (p == p->Parent->LeftChild && p->Parent->RightChild->color == 0 && (p->Parent->RightChild->RightChild == NULL || p->Parent->RightChild->RightChild->color == 0) && (p->Parent->RightChild->LeftChild != NULL && p->Parent->RightChild->LeftChild->color == 1)) {
				//
				// ���ֵ������������ֵ�������������ɫ���������Ϊ���2
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


	cout << "�������������";
	cout << "���ڵ��ǣ�" << p->Parent->data << " " << "��ɫ�ǣ�" << p->Parent->color << endl;
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

	cout << "�����ǣ�" << p->data << " ��ɫ�ǣ�" << p->color<<"(";

	if (p->LeftChild != NULL) {
		cout << "������:" << p->LeftChild->data << "��ɫ�ǣ�" ;
		if (p->LeftChild->color == 0) cout << "��";
		else  cout << "��";
	}
	else
		cout << "����Ϊ��";

	cout << ",";

	if (p->RightChild != NULL) {
		cout << "�Һ����ǣ�" << p->RightChild->data << " ��ɫ��:" ;
		if (p->RightChild->color == 0) cout << "��";
		else cout << "��";
	}
	else
		cout << "�Һ���Ϊ��";

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

