//Excercise 7
#include<iostream>
#include<vector>
using namespace std;
vector<int>vt;
int target = 0;
int n;
int nums[100];
int sizemin = 1e9;
void sm(int i, int sum) {
	if (sum == target&&vt.size()==3) {
		cout << "[";
		for (auto x : vt) {
			cout << x << ",";
		}
		cout << "] ";
		return;
	}
	else {
		for (int j = i; j < n; j++) {
			if (j > i && nums[j - 1] == nums[j])break;
			vt.push_back(nums[j]);
			sum += nums[j];
			sm(j + 1, sum);
			sum -= nums[j];
			vt.pop_back();

		}
	}
}
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (nums[j] < nums[i]) {
				int temp = nums[j];
				nums[j] = nums[i];
				nums[i] = temp;
			}
		}
	}
	sm(0, 0);
	
	return 0;
}