#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<vector>
using namespace std;
class BinaryTree
{
public:
	int val;
	BinaryTree* left;
	BinaryTree* right;
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
	void levalOrder(BinaryTree* root);

};
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
		cout<<node->val<<" "<<endl;
		if(node->right)
		{
			s->push(node->right);
		}
		if(node->left)
		{
			s->push(node->left);
		}
	}
}
void BinaryTree::levalOrder(BinaryTree* root)
{
	queue<BinaryTree*>q;
	if(!root)
	{
		return;
	}
	q.push(root);
	while(!q.empty())
	{
		BinaryTree* node=q.front();
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
}
int main()
{
	BinaryTree* binaryTree=new BinaryTree();
	BinaryTree* root;
	binaryTree->createTree(root);
	binaryTree->preOrder(root);
	return 0;
}