#include<iostream>
#include<vector>
#include<queue>
#include<map>
using namespace std;
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
class Solution {
public:
    Node* cloneGraph(Node* node) {
        queue<Node*>queue1;
		queue<Node*>queue2;
		vector<Node*>v;
		Node* newNode = new Node(node->val, v);
		map<int, Node*>m;
		map<int, Node*>::iterator i;
		queue1.push(node);
		queue2.push(newNode);
		while ( ! queue1.empty()) {
			Node* n1 = queue1.front();
			Node* n2 = queue2.front();
			queue1.pop();
			queue2.pop();
			vector<Node*>::iterator iter;//数组形式存储 Node** arr::*arr == arr[0]
			for (iter = n1->neighbors.begin(); iter != n1->neighbors.end(); iter++) {
				Node* n = *iter;
				Node* k;
				vector<Node*>vec;
				i = m.find(n->val);
				if (i == m.end()) {
					queue1.push(n);
					k = new Node(n->val, vec);
					queue2.push(k);
				} else {
					k = i->second;
				}
				n2->neighbors.push_back(k);
			}
			m.insert(pair<int, Node*>(n2->val, n2));
		}
		return newNode;
    }
};
int main()
{
	return 0;
}