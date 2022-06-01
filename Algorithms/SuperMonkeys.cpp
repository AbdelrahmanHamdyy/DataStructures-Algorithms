#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <algorithm>
#include <unordered_map>

typedef long long ll;
using namespace std;

void GetMin(int bucket, int& minB, vector<int> monkeys, int current, int bites, int& min, bool& flag)
{
	if (bucket == 0)
	{
		if (!flag || bites < min)
		{
			min = bites;
			minB = bucket;
			flag = true;
		}
		return;
	}
	if (bucket < 0 && !flag)
	{
		if (bites < min)
		{
			min = bites - 1;
			minB = bucket + monkeys[current];
		}
		return;
	}
	for (int i = 0; i < monkeys.size(); i++)
	{
		if (bucket > 0)
			GetMin(bucket - monkeys[i], minB, monkeys, i, bites + 1, min, flag);
	}
}

int GetMin_dp(int bucket, vector<int> monkeys, int current, int& remaining, int& minR, int& min, bool& flag)
{
	if (bucket == 0)
	{
		remaining = 0;
		flag = true; // Wsl ll zero
		return 0;
	}
	if (bucket < 0 && !flag)
	{
		remaining = bucket + monkeys[current];
		return -1;
	}
	int bites = INT_MAX;
	bool found = false;
	for (int i = 0; i < monkeys.size(); i++)
	{
		bites = 1 + GetMin_dp(bucket - monkeys[i], monkeys, i, remaining, min, flag);
		if (!flag && !found)
		{
			if (remaining < minR)
				minR = remaining;

		}

	}
	return min;
}

/*map<int, int> dp;
int GetMin_dp(int bucket, vector<int> monkeys, int& min)
{
	auto it = dp.find(bucket);
	if (it != dp.end())
		return it->second;

	if (bucket == 0)
		return 1;

	if (bucket < 0)
		return INT_MAX;
	for (int i = 0; i < monkeys.size(); i++)
	{
		int bites = GetMin_dp(bucket - monkeys[i], monkeys, min);
		if (bites < min)
			dp[bucket] = 1 + bites;
	}
	return dp[bucket];
}*/

int main()
{
	int N; // Number of buckets
	cin >> N;
	vector<int> buckets(N);
	for (int i = 0; i < N; i++)
		cin >> buckets[i]; // Bananas in each bucket
	int M; // Number of Monkeys
	cin >> M;
	vector<int> monkeys(M);
	for (int i = 0; i < M; i++)
	{
		int in;
		cin >> in;
		if (in > 0)
			monkeys[i] = in; // Bananas in 1 bite
	}
	/*for (int i = 0; i < N; i++)
	{
		bool flag = false;
		int min = INT_MAX;
		int minB = INT_MAX;
		GetMin(buckets[i], minB, monkeys, 0, 0, min, flag);
		cout << minB << " " << min << endl;
	}*/

	for (int i = 0; i < N; i++)
	{
		int min = INT_MAX;
		int minB = INT_MAX;
		bool flag = false;
		GetMin_dp(buckets[i], monkeys, 0, minB, min, flag);
		cout << minB << " " << min << endl;
	}
}