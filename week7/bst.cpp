#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* Search(NODE* pRoot, int x) {
	if (pRoot == NULL)return NULL;
	if (pRoot->key == x)return pRoot;
	NODE* left = Search(pRoot->p_left, x);
	if (left != NULL)return left;
	return Search(pRoot->p_right, x);
}
void Insert(NODE*& pRoot, int x) {
	if (pRoot == NULL) {
		pRoot = new NODE;
		pRoot->key = x;
		pRoot->p_left = NULL;
		pRoot->p_right = NULL;
	}
	else {
		if (x < pRoot->key) {
			Insert(pRoot->p_left, x);
		}
		else if (x > pRoot->key) {
			Insert(pRoot->p_right, x);
		}
	}
}
void Remove(NODE*& pRoot, int x) {
	if (pRoot == NULL) return;
	if (x < pRoot->key) {
		Remove(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Remove(pRoot->p_right, x);
	}
	else {
		if (pRoot->p_right == NULL && pRoot->p_left==NULL) {
			delete pRoot;
			pRoot = NULL;
		}
		else if (pRoot->p_right == NULL) {
			NODE* cur = pRoot;
			pRoot = pRoot->p_left;
			delete cur;
		}
		else if (pRoot->p_left == NULL) {
			NODE* cur = pRoot;
			pRoot = pRoot->p_right;
			delete cur;
		}
		else {
			NODE* temp = pRoot->p_right;
			while (temp->p_left!= NULL) {
				temp = temp->p_left;//đã thấy trái nhất bên phải
			}
			pRoot->key = temp->key;
			Remove(pRoot->p_right, temp->key);
		}

	}
}
NODE* createTree(int a[], int n) {
	NODE* tree = NULL;
	for (int i = 0; i < n; i++) {
		Insert(tree, a[i]);
	}
	return tree;
}

void removeTree(NODE*& pRoot) {
	if (pRoot == NULL)return;
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
}
int Height(NODE* pRoot) {
	if (pRoot == NULL)return -1;
	int left = Height(pRoot->p_left);
	int right = Height(pRoot->p_right);
	return 1 + max(left, right);
}
int countLess(NODE* pRoot, int x) {
	if (pRoot == NULL)return 0;
	if (pRoot->key < x) {
		return 1 + countLess(pRoot->p_left,x) + countLess(pRoot->p_right,x);

	}
	else {
		return countLess(pRoot->p_left,x);
	}
}

int countGreater(NODE* pRoot, int x) {
	if (pRoot == NULL)return 0;
	if (pRoot->key > x) {
		return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
	}
	else {
		return countGreater(pRoot->p_right, x);
	}
}
bool _isBST(NODE* pRoot, int minval, int maxval) {
	if (pRoot == NULL)return true;
	if (pRoot->key <= minval || pRoot->key >= maxval) return false;
	return _isBST(pRoot->p_left, minval, pRoot->key)&&
	_isBST(pRoot->p_right, pRoot->key, maxval);
			
}
bool isBST(NODE* pRoot) {
	return _isBST(pRoot, -2147483648, 2147483647);
}
bool isFull(NODE* pRoot) {
	if (pRoot == NULL)return true;
	if (pRoot->p_left == NULL && pRoot->p_right != NULL || pRoot->p_left != NULL && pRoot->p_right == NULL) return false;
	return isFull(pRoot->p_left) && isFull(pRoot->p_right);
}
bool isFullBST(NODE* pRoot) {
	
	return _isBST(pRoot, -2147483648, 2147483647)&& isFull(pRoot);
}
