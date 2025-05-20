#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};
NODE* createNode(int data) {
	NODE* p = new NODE;
	p->key = data;
	p->p_left = NULL;
	p->p_right = NULL;
	p->height = 1;
	return p;

}
int getheight(NODE* pRoot) {
	if (pRoot == NULL)return 0;//dn
	return pRoot->height;
}
void updateheight(NODE* pRoot) {
	if (pRoot == NULL)return ;
	int left = getheight(pRoot->p_left);
	int right = getheight(pRoot->p_right);
	pRoot->height=1 + max(left, right);

}
int getBalance(NODE* pRoot) {
	if (pRoot == NULL)return 0;
	return getheight(pRoot->p_left) - getheight(pRoot->p_right);
}
NODE* rotateRight(NODE* pRoot) {
	NODE* x = pRoot->p_left;
	NODE* y = x->p_right;
	x->p_right = pRoot;
	pRoot->p_left = y;
	updateheight(pRoot);
	updateheight(x);
	return x;
}
NODE* rotateLeft(NODE* pRoot) {
	NODE* x = pRoot->p_right;
	NODE* y = x->p_left;
	x->p_left = pRoot;
	pRoot->p_right = y;
	updateheight(x);
	updateheight(pRoot);
	return x;

}
void Insert(NODE*& pRoot, int x) {
	if (pRoot == NULL) {
		pRoot = createNode(x);
		return;
	}
	else if (x < pRoot->key) {
		Insert(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Insert(pRoot->p_right, x);
	}
	else {
		return;
	}
	updateheight(pRoot);
	int b = getBalance(pRoot);
	if (b > 1 && x < pRoot->p_left->key) {
		pRoot = rotateRight(pRoot);
	}
	else if (b<-1 && x>pRoot->p_right->key) {
		pRoot = rotateLeft(pRoot);
	}
	else if (b > 1 && x > pRoot->p_left->key) {
		pRoot->p_left = rotateLeft(pRoot->p_left);
		pRoot = rotateRight(pRoot);
	}
	else if (b < -1 && x < pRoot->p_right->key) {
		pRoot->p_right = rotateRight(pRoot->p_right);
		pRoot = rotateLeft(pRoot);
	}
}
void Remove(NODE*& pRoot, int x) {
	if (pRoot == NULL)return;
	if (x < pRoot->key) {
		Remove(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Remove(pRoot->p_right, x);
	}
	else {
		if (pRoot->p_left == NULL && pRoot->p_right == NULL) {
			delete pRoot;
			pRoot = NULL;
		}
		else if (pRoot->p_left == NULL) {
			NODE* cur = pRoot;
			pRoot = pRoot->p_right;
			delete cur;
		}
		else if (pRoot->p_right == NULL) {
			NODE* cur = pRoot;
			pRoot = pRoot->p_left;
			delete cur;
		}
		else {
			NODE* temp = pRoot->p_right;
			while (temp->p_left != NULL) {
				temp = temp->p_left;
			}
			pRoot->key = temp->key;
			Remove(pRoot->p_right, temp->key);
		}
	}
	if (pRoot == NULL)return;
	updateheight(pRoot);
	int b = getBalance(pRoot);
	if (b > 1 && getBalance(pRoot->p_left) >= 0) {
		pRoot=rotateRight(pRoot);
	}
	else if (b < -1 && getBalance(pRoot->p_right) <= 0) {
		pRoot = rotateLeft(pRoot);
	}
	else if (b > 1 && getBalance(pRoot->p_left) < 0) {
		pRoot->p_left = rotateLeft(pRoot->p_left);
		pRoot = rotateRight(pRoot);
	}
	else if (b < -1 && getBalance(pRoot->p_right)>0) {
		pRoot->p_right = rotateRight(pRoot->p_right);
		pRoot= rotateLeft(pRoot);
	}

}
bool isAVL(NODE* pRoot) {
	if (pRoot == NULL)return true;
	if (getBalance(pRoot) > 1 || getBalance(pRoot) < -1)return false;
	return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
