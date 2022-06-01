#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <algorithm>
#include <unordered_map>

typedef long long ll;
using namespace std;

vector<vector<ll>> dp(1001, vector<ll>(1001, -1));
ll solve(vector<vector<ll>>& grid, ll i, ll j, ll r, ll c)
{
	if (i == r - 1 && j == c - 1 && grid[i][j] != -1)
		return 1;
	if (i > r - 1 || j > c - 1)
		return 0;
	if (grid[i][j] == -1)
		return 0;

	// Memoization
	if (dp[i][j] != -1)
		return dp[i][j];

	dp[i][j] = 0;
	// Right/down if no obstacle
	if (grid[i][j] == 0)
	{
		if (j + 1 < c)
			dp[i][j] += solve(grid, i, j + 1, r, c);
		if (i + 1 < r)
			dp[i][j] += solve(grid, i + 1, j, r, c);
	}
	return dp[i][j];
}

int main()
{
	ll r, c;
	cin >> r >> c;
	vector<vector<ll>> grid(r, vector<ll>(c));
	for (ll i = 0; i < r; i++)
		for (ll j = 0; j < c; j++)
			cin >> grid[i][j];
	cout << solve(grid, 0, 0, r, c);
}