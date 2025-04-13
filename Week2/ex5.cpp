//Excercise 5
#include<iostream>
#include<vector>
using namespace std;
vector<int>vt;
int target;
int n;
int nums[100];
int sizemin = 1e9;
void sm(int i, int sum) {
	if (sum == target) {
		int s = vt.size();
		sizemin = min(sizemin, s);
		return;
	}
	else {
		for (int j = i; j < n; j++) {
			vt.push_back(nums[j]);
			sum += nums[j];
			sm(j + 1, sum);
			sum -= nums[j];
			vt.pop_back();

		}
	}
}
int main() {
	cin >> target >> n;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	sm(0, 0);
	cout <<sizemin;
	return 0;
}