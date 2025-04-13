//Exercise 1
//Given an array of N integers and a target integer K, implement a program to find the first
//occurrence of K in the array using the** Linear Search** algorithm.If K is found, return
//its index(0 - based).Otherwise, return -1.

#include<iostream>
using namespace std;
int linearsearch(int a[], int n, int K) {
	for (int i = 0; i < n; i++) {
		if (a[i] == K) return i;
	}
	return -1;
}
int main() {
	int n, k, a[100];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cin >> k;
	cout << linearsearch(a, n,k);
	return 0;
}