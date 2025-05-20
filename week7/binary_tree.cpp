#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* createNode(int data) {
	NODE* p = new NODE;
	p->key = data;
	p->p_left = NULL;
	p->p_right = NULL;
	return p;
}
vector<int> NLR(NODE* pRoot) {
	vector<int>NLR_new;
	if (!pRoot)return NLR_new;
	NLR_new.push_back(pRoot->key);
	vector<int>left = NLR(pRoot->p_left);
	for (int i = 0; i < left.size(); i++) {
		NLR_new.push_back(left[i]);
	}
	vector<int>right = NLR(pRoot->p_right);
	for (int i = 0; i < right.size(); i++) {
		NLR_new.push_back(right[i]);
	}
	
	return NLR_new;
}
vector<int> LNR(NODE* pRoot) {
	vector<int>LNR_new;
	if (!pRoot)return LNR_new;

	vector<int>left = LNR(pRoot->p_left);
	for (int i = 0; i < left.size(); i++) {
		LNR_new.push_back(left[i]);
	}
	LNR_new.push_back(pRoot->key);
	vector<int>right = LNR(pRoot->p_right);
	for (int i = 0; i < right.size(); i++) {
		LNR_new.push_back(right[i]);
	}
	

	return LNR_new;

}
vector<int> LRN(NODE* pRoot) {
	vector<int>LRN_new;
	if (!pRoot)return LRN_new;

	vector<int>left = LRN(pRoot->p_left);
	for (int i = 0; i < left.size(); i++) {
		LRN_new.push_back(left[i]);
	}
	
	vector<int>right = LRN(pRoot->p_right);
	for (int i = 0; i < right.size(); i++) {
		LRN_new.push_back(right[i]);
	}
	LRN_new.push_back(pRoot->key);

	return LRN_new;
}

vector<vector<int>> LevelOrder(NODE* pRoot) {
	
	vector<vector<int>>BFS;
	if (pRoot == NULL)return BFS;
	queue<NODE*>q;
	q.push(pRoot);
	while (!q.empty()) {
		int size_q = q.size();
		vector<int>level;
		for (int i = 0; i < size_q; i++) {
			NODE* p = q.front();
			q.pop();
			level.push_back(p->key);
			if (p->p_left != NULL) {
				q.push(p->p_left);
			}
			if (p->p_right) {
				q.push(p->p_right);
			}
		}
		BFS.push_back(level);
	}
	return BFS;
}



int countNode(NODE* pRoot) {
	if (!pRoot)return 0;
	int left = countNode(pRoot->p_left);
	int right = countNode(pRoot->p_right);
	return 1 + left + right;
}
int sumNode(NODE* pRoot) {
	if (!pRoot)return 0;
	int left = sumNode(pRoot->p_left);
	int right = sumNode(pRoot->p_right);
	return pRoot->key + left + right;
}


int height(NODE* pRoot) {
	if (pRoot == NULL) return -1;
	int left = height(pRoot->p_left);
	int right = height(pRoot->p_right);
	return 1 + max(left, right);
}
NODE* find(NODE* pRoot, int value) {
	
	if (pRoot == NULL)return NULL;
	if (pRoot->key == value)return pRoot;
	NODE* left = find(pRoot->p_left,value);
	if (left != NULL)return left;
	return find(pRoot->p_right, value);
}
int heightNode(NODE* pRoot, int value) {
	NODE* x = find(pRoot, value);
	if (x == NULL)return -1;
	int h = height(x);
	return h;
}
int _level(NODE* pRoot, NODE* p, int level) {
	if (pRoot == NULL)return -1;
	if (pRoot == p)return level;
	int left = _level(pRoot->p_left, p, level + 1);
	if (left != -1)return left;
	int right = _level(pRoot->p_right, p, level + 1);
	return right;
}
int Level(NODE* pRoot, NODE* p) {
	if (pRoot == NULL || p == NULL)return -1;
	return _level(pRoot, p, 0);

}
int countLeaf(NODE* pRoot) {
	if (pRoot == NULL)return 0;
	if (pRoot->p_left == NULL && pRoot->p_right == NULL)return 1;
	int left = countLeaf(pRoot->p_left);
	int right = countLeaf(pRoot->p_right);
	return left + right;
}
