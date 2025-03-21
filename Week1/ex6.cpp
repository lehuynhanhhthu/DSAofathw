
#include<iostream>
using namespace std;
int x[100], y[100], ct[100], cn[100], a[100][100], n;
int kk= 0;
void xuat() {
	memset(a, 0, sizeof(a));
	for (int i = 1; i <= n; i++) {
		a[i][x[i]] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void tryy (int i) {
	for (int j = 1; j <= n; j++) {
		if (y[j] == 1 && ct[i - j + n] == 1 && cn[i + j - 1] == 1) {
			x[i] = j;
			y[j] = cn[i + j - 1] = ct[i - j + n] = 0;
			if (i == n) {
				kk++;
				xuat();
				
			}
			else {
				tryy(i + 1);
			}
			y[j] = cn[i + j - 1] = ct[i - j + n] = 1;
			
		}
	}
}
int main() {
	cin >> n;
	for (int i = 1; i < 3 * n; i++) {
		y[i] = cn[i] = ct[i] = 1;
	}
	tryy(1);
	cout << kk;
	return 0;
}