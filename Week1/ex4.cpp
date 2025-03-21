//Exercise 4: Towers of Hanoi puzzle
#include<iostream>
using namespace std;
void TowersHN(int n, char A, char B, char C) {
	if (n == 1) {
		cout << "Move disk 1 from " << A << " to " << C << endl;
		return;
	}
	TowersHN(n - 1, A, C, B);
	cout << "Move disk " << n << " from " << A << " to " << C << endl;
	TowersHN(n - 1, B, A, C);

}
int main() {
	int n;
	cin >> n;
	TowersHN(n, 'A', 'B', 'C');
	return 0;
}