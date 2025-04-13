//Exercise 5: Given an array , check whether the array is in sorted order with recursion.
#include<iostream>
using namespace std;
bool checksort(int a[], int n) {
	if (n == 1 || n == 0) return true;
	if (a[0] > a[1]) return false;
	return checksort(a + 1, n - 1);
}
int main() {
	int a[100], n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (checksort(a, n)) {
		cout << "The array is sorted.";
	}
	else {
		cout << "The array is not sorted.";
	}
	return 0;
}