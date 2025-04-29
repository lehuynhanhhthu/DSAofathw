#include<iostream>
#include <fstream>
using namespace std;
struct NODE {
	int key;
	NODE* p_next;
};
struct Stack {
	NODE* top;
};
void addnode(NODE*top,int data) {
	NODE* p = new NODE;
	p->key = data;
	p->p_next = NULL;
	if (top == NULL) {
		top = p;
		return;
	}
	p->p_next = top;
	top = p;
}
Stack * initializeStack() {
	Stack* s = new Stack;
	s->top = NULL;
	return s;
}
void push(Stack& s, int key) {
	NODE* p = new NODE;
	p->key = key;
	p->p_next = s.top;
	s.top = p;
}
void reve(Stack* s,NODE*neww) {
	if (s->top == NULL) return ;
	NODE* temp = s->top;
	
	while (temp != NULL) {
		addnode(neww, temp->key);
		temp = temp->p_next;
	}
	return;
}
NODE* reverseStack(NODE* head) {
	NODE* prev = NULL;
	NODE* curr = head;
	NODE* next = NULL;
	while (curr != NULL) {
		next = curr->p_next;
		curr->p_next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}
int pop(Stack& s) {
	if (s.top == NULL) {
		return -1;
	}
	int value = s.top->key;
	NODE* temp = s.top;
	s.top = s.top->p_next;
	delete temp;
	return value;

}
int size(Stack s) {
	NODE* cur = s.top;
	int count = 0;
	while (cur != NULL) {
		count++;
		cur = cur->p_next;
	}
	return count;
}
bool isEmpty(Stack s) {
	if (s.top == NULL)return true;
	else return false;
}
void printStack(NODE*top, ofstream& fout) {
	NODE* temp = top;
	while (temp != NULL) {
		fout << temp->key << " ";
		temp = temp->p_next;
	}
	fout << endl;
}
int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	Stack* s =NULL;
	string cmt;
	while (fin >> cmt) {
		if (cmt == "init") {
			s = initializeStack();
			fout << "EMPTY" << endl;
		}
		else if (cmt == "push") {
			int key;
			fin >> key;
			push(*s, key);

			NODE* temp = reverseStack(s->top); // đảo tạm thời
			NODE* cur = temp;
			while (cur != NULL) {
				fout << cur->key << " ";
				cur = cur->p_next;
			}
			fout << endl;
			s->top = reverseStack(temp);

		}
		else if (cmt == "pop") {
			if (isEmpty(*s)) {
				fout<<"EMPTY";
			}
			else {
				int k = pop(*s);
				if (isEmpty(*s)) {
					fout << "EMPTY";
				}
				NODE* temp = reverseStack(s->top); // đảo tạm thời
				NODE* cur = temp;
				while (cur != NULL) {
					fout << cur->key << " ";
					cur = cur->p_next;
				}
				fout << endl;
				s->top = reverseStack(temp);
			}
		}
	}
	fin.close();
	fout.close();
	return 0;

}