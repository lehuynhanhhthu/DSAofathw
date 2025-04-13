//Exercise 6
#include<iostream>
using namespace std;
bool checkpairssumK(int a[], int n, int k) {
	int l = 0; int r = n - 1;
	if (l == r)return false;
	while (l < r) {
		int sum = a[l] + a[r];
		if (sum == k)return true;
		else if (sum > k) r--;
		else l++;
		
	}
	return false;
}
int main() {
	int a[100], n, k;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cin >> k;
	if (checkpairssumK(a, n, k)) {
		cout << "YES";
	}
	else cout << "NO";
	return 0;
}