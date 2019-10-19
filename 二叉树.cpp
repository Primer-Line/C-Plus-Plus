#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<vector>
using namespace std;
/*
二叉树的简单实现
*/
class BinaryTree
{
public:
	BinaryTree* left;
	BinaryTree* right;
	int val;
	BinaryTree()
	{
	}
	BinaryTree(int val)
	{
		this->val=val;
	}
	~BinaryTree()
	{
	}
	void createTree(BinaryTree*& root);
	void preOrder(BinaryTree* root);
	void levelOrder(BinaryTree* root);

};
//递归前序遍历创建二叉树
void BinaryTree::createTree(BinaryTree*& root)
{
	cout<<"input node's val:"<<endl;
	int val;
	cin>>val;
	if(val==0)
	{
		root=NULL;
		return;
	}
	root=new BinaryTree(val);
	createTree(root->left);
	createTree(root->right);
}
//前序遍历
void BinaryTree::preOrder(BinaryTree* root)
{
	stack<BinaryTree*>*s=new stack<BinaryTree*>();
	if(!root)
	{
		return;
	}
	s->push(root);
	BinaryTree* node;
	while(!(s->empty()))
	{
		node=s->top();
		s->pop();
		cout<<node->val<<" ";
		if(node->right)
		{
			s->push(node->right);
		}
		if(node->left)
		{
			s->push(node->left);
		}
	}
	cout<<endl;
	delete s;
}
//广度优先遍历
void BinaryTree::levelOrder(BinaryTree* root)
{
	queue<BinaryTree*>q;
	if(!root)return;
	q.push(root);
	while(!q.empty())
	{
		BinaryTree* node=q.front();
		cout<<node->val<<" ";
		q.pop();
		if(node->left)
		{
			q.push(node->left);
		}
		if(node->right)
		{
			q.push(node->right);
		}
	}
	cout<<endl;
}
//销毁二叉树
void destoryTree(BinaryTree* root)
{
	if(!root)return;
	BinaryTree* left = root->left;
	BinaryTree* right = root->right;
	delete root;
	destoryTree(left);
	destoryTree(right);
}
int main()
{
	BinaryTree* binaryTree=new BinaryTree();
	BinaryTree* root;
	binaryTree->createTree(root);
	binaryTree->preOrder(root);
	binaryTree->levelOrder(root);
	destoryTree(root);
	delete binaryTree;
	return 0;
}