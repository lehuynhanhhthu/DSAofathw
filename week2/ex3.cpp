//Exercise 3
#include<iostream>
using namespace std;
int minimum(int a[], int n) {
	int left = 0;
	int right = n - 1;
	if (left == right) return a[right];
	if (a[left] < a[right])return a[left];
	while (left < right) {
		if (a[left] < a[right])return a[left];
		else {
			int m = (left + right) / 2;
			if (a[m] > a[right]) {
				left = m + 1;
			}
			else if (a[m] < a[right]) {
				right = m;
			}
			else return a[right];
		}
	}
	return a[left];
}
int main() {
	int n, a[100];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << minimum(a, n);
	return 0;
}