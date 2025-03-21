//Exercise 3: Generate All Binary Strings
#include<iostream>
using namespace std;
void generateBinaryStrings(int n, string str) {
	if (str.size() == n) {
		cout << str << endl;
		return;
	}
	generateBinaryStrings(n, str + "0");
	generateBinaryStrings(n, str + "1");

		
}
int main() {
	int n;
	string str;
	cin >> n;
	generateBinaryStrings(n, str);
	return 0;
}