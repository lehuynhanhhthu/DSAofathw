//Exercise 4
#include<iostream>
using namespace std;
bool checkweight(int a[], int n,int day, int model) {
	int sum = 0, countday = 1;
	for (int i = 0; i < n; i++) {
		if (sum +a[i] > model) {
			sum = a[i];
			countday++;
		}
		else {
			sum += a[i];
		}
		if (countday > day)return false;
	}
	
	return true;
}
int tong(int a[], int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i];
	}
	return sum;
}
int mingodonday(int a[], int n ,int day) {
	int left = a[n-1];
	int right = tong(a,n);
	while (left < right) {
		int m = (left + right) / 2;
		if (checkweight(a, n, day, m)) {
			right = m;
		}
		else {
			left = m + 1;
		}
	}
	return left;
}
int main() {
	int n, day, a[100];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cin >> day;
	cout << mingodonday(a, n, day);
	
	return 0;
}


