1//Exercise 2: Factorial of a Number
#include<iostream>
using namespace std;
long long giaithua(int n) {
	if (n == 1 || n == 0) return 1;
	return n * giaithua(n - 1);
}
int main() {
	int n;
	cin >> n;
	cout << giaithua(n);
	return 0;
}