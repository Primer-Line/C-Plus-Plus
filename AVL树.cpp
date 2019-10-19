#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
/*
平衡二叉树的实现(待完善...)
*/
//平衡二叉树的存储结构
typedef struct BinaryTree
{
	int bf;
	int key;
	struct BinaryTree* left;
	struct BinaryTree* right;
}TreeNode,*Node;
//定义avl树类
class AVL
{
public:
	int bf;
	int val;
	AVL* left;
	AVL* right;
	AVL* parent;
	AVL()
	{
	}
	AVL(AVL*) : val(val)
	{
	}
	AVL(int val) 
	{
		this->val=val;
	}
	~AVL()
	{
	}
	void const insertNode(AVL*& root,int);
	void preOrder(const AVL*);
	int getHeight(const AVL*);
	bool operator < (const AVL* node) const;
	int operator - (AVL*&) const;
	const bool operator > (const AVL*) const; 
	void destoryTree(AVL*&);
};
//求树高
int AVL::getHeight(const AVL* root)
{
	if(!root)return 0;
	int left = getHeight(root->left) + 1;
	int right = getHeight(root->right) + 1;
	return left > right ? left : right;
}
//运算符重载 比较节点键值大小
bool AVL::operator < (const AVL* node) const
{
	return this->val<node->val;;
}
int AVL::operator - (AVL*& root) const
{
	return this->bf-root->bf;
}
//插入节点
void const AVL::insertNode(AVL*& root,int val)
{
	if(!root)
	{
		root = new AVL(val);
		root->bf = 0;
		root->left = NULL;
		root->right = NULL;
		return;
	}
	AVL* node = new AVL(val),*q = root,*p;
	node->left = NULL;
	node->right = NULL;
	while(q)
	{
		p = q;
		q = node < q ? q->left : q->right;
	}
	node->parent = p;
	if(node < p)p->left = node;
	else p->right = node;
}
//前序遍历
void AVL::preOrder(const AVL* root)
{
	if(!root)return;
	cout<<root->val<<" ";
	preOrder(root->left);
	preOrder(root->right);

}
//销毁二叉树
void AVL::destoryTree(AVL*& root)
{
	if(!root)return;
	AVL* left = root->left;
	AVL* right = root->right;
	delete root;
	destoryTree(left);
	destoryTree(right);
}
int main()
{
	AVL* avl = new AVL(),*root = NULL;
	int nums[] = {6,3,1,8,4,5,2,7},len = sizeof(nums)/sizeof(int);
	int* p = nums,*q=nums+len;
	for (;p < q; p++) {
		avl->insertNode(root,*p);
	}
	avl->preOrder(root);
	cout<<endl;
	avl->destoryTree(root);
	delete avl;
	return 0;
}