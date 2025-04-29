#include<iostream>
#include<fstream>
using namespace std;
struct NODE {
	int key;
	NODE* p_next;
};
struct Queue {
	NODE* head;
	NODE* tail;
};
Queue* initializeQueue() {
	Queue*q = new Queue;
	q->head = q->tail = NULL;
	return q;
}
void enqueue(Queue& q, int key) {
	NODE* k = new NODE;
	k->key = key;
	k->p_next = NULL;
	if (q.head == NULL) {
		q.head = q.tail = k;
		return;
	}
	q.tail->p_next = k;
	q.tail = k;
}
int dequeue(Queue& q) {
	if (q.head == NULL) return -1;
	NODE* temp = q.head;
	int value = q.head->key;
	q.head = q.head->p_next;
	delete temp;
	return value;
}
int size(Queue q) {
	NODE* temp = q.head;
	int count = 0;
	while (temp != NULL) {
		count++;
		temp = temp->p_next;
	}
	return count;
}
bool isEmpty(Queue q) {
	if (q.head == NULL)return true;
	return false;
}
int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	string name;
	Queue* q = NULL;
	while (fin >> name) {
		if (name == "init") {
			q = initializeQueue();
			fout << "EMPTY" << endl;
		}
		else if (name == "enqueue") {
			int key;
			fin >> key;
			enqueue(*q, key);
			NODE* cur = q->head;
			while (cur != NULL) {
				fout << cur->key << " ";
				cur = cur->p_next;
			}
			fout << endl;
			

		}
		else if (name == "dequeue") {
			int kq = dequeue(*q);
			if (q->head == NULL) {
				fout << "EMPTY" << endl;
			}
			else {
				NODE* cur = q->head;
				while (cur != NULL) {
					fout << cur->key << " ";
					cur = cur->p_next;
				}
				fout << endl;

			}
			
			
		}
	}


	fin.close();
	fout.close();
	return 0;




}