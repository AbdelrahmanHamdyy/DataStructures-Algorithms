#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int getSum(vector<int> v)
{
	int sum = 0;
	for (int i = 0; i < v.size(); i++)
		sum += v[i];
	return sum;
}

void solve(int N, vector<bool>& isused,  vector<int>& v, vector<int>& result, vector<int>& Max)
{
	if (getSum(result) <= N)
	{
		if (getSum(Max) < getSum(result))
			Max = result;
		else if (getSum(Max) == getSum(result))
		{
			if (Max.size() == 0 || (Max.size() < result.size()))
				Max = result;
		}
	}
	else
		return;
	for (int i = 0; i < v.size(); i++)
	{
		if (!isused[i])
		{
			isused[i] = 1;
			result.push_back(v[i]);
			solve(N, isused, v, result, Max);
			result.pop_back();
			isused[i] = 0;
		}
	}
}

int main() {
	int N, size;
	cin >> N >> size;
	vector<int> v(size);
	for (auto it = v.begin(); it != v.end(); it++)
		cin >> *it;
	vector<bool> isused(size, 0);
	vector<int> Max;
	vector<int> result;
	solve(N, isused, v, result, Max);
	for (int i = 0; i < Max.size(); i++)
		cout << Max[i] << " ";
	cout << endl;
	cout << getSum(Max) << endl;
	return 0;
}