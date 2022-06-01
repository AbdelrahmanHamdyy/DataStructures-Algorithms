#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <algorithm>
#include <unordered_map>

typedef long long ll;
using namespace std;

//Catalan
int cat(int n)
{
	vector<int> dp(n + 1, 0);
	dp[0] = 1;
	dp[1] = 1;
	for (int i = 2; i < n; i++)
		for (int j = 0; j < i; j++)
			dp[i] += dp[j] * dp[i - j];
	return dp[n];
}

int LIS_TopDown(vector<int> v, int index, vector<int>& dp)
{
	if (index == 0)
		return dp[0] = 1;
	dp[index] = 1;
	for (int i = 0; i < index; i++)
	{
		if (dp[i] < 0)
			dp[i] = LIS_TopDown(v, i, dp);
		if (v[index] > v[i] && (dp[i] + 1) > dp[index])
			dp[index] = dp[i] + 1;
	}
	return dp[index];
}

int LIS(vector<int> v, int n)
{
	vector<int> dp(n, -1);
	LIS_TopDown(v, n, dp);
	int max = *max_element(dp.begin(), dp.end());
	return max;
}

int LIS_BottomUp(vector<int> v, int n, vector<int>& dp)
{
	dp[0] = 1;
	for (int i = 0; i < n; i++)
	{
		dp[i] = 1;
		for (int j = 0; j < i; j++)
		{
			if (v[i] > v[j] && (dp[j] + 1) > dp[i])
				dp[i] = dp[j] + 1;
		}
	}
	int max = *max_element(dp.begin(), dp.end());
	return max;
}

int Sort(vector<int> v, int n)
{
	return (n - LIS(v, n));
}

int editDist(string s1, string s2, int m, int n)
{
	if (m == 0)
		return n;
	if (n == 0)
		return m;
	if (s1[m - 1] == s2[n - 1])
		return editDist(s1, s2, m - 1, n - 1);
	/* return 1 + min(editDist(s1, s2, m - 1, n - 1), // Replace
				   editDist(s1, s2, m, n - 1),     // Insert
			       editDist(s1, s2, m - 1, n));    // Remove*/
}


// Knapsack
int solve(int i, vector<vector<int>>& p, int W, int N, vector<vector<int>>& dp)
{
	if (i == N)
		return 0;
	if (dp[i][W] != -1)
		return dp[i][W];
	int ans = solve(i + 1, p, W, N, dp);
	if (p[i][0] <= W)
		ans = max(ans, p[i][1] + solve(i + 1, p, W - p[i][0], N, dp));
	return dp[i][W] = ans;
}

void price(vector<int>& p, vector<int>& mem)
{
	for (int i = 0; i < p.size(); i++)
	{
		for (int j = i + 1; j < p.size(); j++)
		{
			int profit = p[j] - p[i];
			if (p[j] > p[i] && profit > mem[i])
				mem[i] = profit;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	/*int N, W;
	cin >> N >> W;
	vector<vector<int>> p(N, vector<int>(2));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> p[i][j];
		}
	}
	vector<vector<int>> dp(1000, vector<int>(1000, -1));
	cout << solve(0, p, W, N, dp);*/
	int n; cin >> n;
	vector<int> pr(n);
	for (int i = 0; i < n; i++)
		cin >> pr[i];
	vector<int> mem(n, 0);
	price(pr, mem);
	cout << *max_element(mem.begin(), mem.end());
}