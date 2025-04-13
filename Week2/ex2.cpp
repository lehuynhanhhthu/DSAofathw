//Exercise 2
//Use * *Linear Search with Sentinel * *to solve Exercise 1.
#include<iostream>
using namespace std;
int linearsearch_S(int a[], int n, int K) {
	int last = a[n - 1];// lưu element cuối
	 a[n - 1] = K;//gán element cuối bằng phần tử cần tìm
	 int i = 0;
	 while (a[i] != K) {//tìm K nếu không có thì cũng stop tại chỉ số n-1;
		 i++;
	 }
	 a[n - 1] = last;//trả lại đúng giá trị 
	 if (i < n && a[i] == K)return i;//kiểm tra xem chỉ số tìm được có thực sự mang value K không
	 return -1;
}
int main() {
	int n, k, a[100];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cin >> k;
	cout << linearsearch_S(a, n, k);
	return 0;
}