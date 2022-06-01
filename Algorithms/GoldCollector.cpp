#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <climits>

typedef long long ll;
using namespace std;

/* void Collect(vector<vector<int>> v, int i, int j, int N, int M, int sum, int& max)
{
	sum += v[i][j];
	if (i == N - 1 && j == M - 1)
	{
		if (sum > max)
			max = sum;
		return;
	}
	if (i > N - 1 || j > M - 1)
		return;
	if (i + 1 <= N - 1)
		Collect(v, i + 1, j, N, M, sum, max);
	if (j + 1 <= M - 1)
		Collect(v, i, j + 1, N, M, sum, max);
	if (i + 1 <= N- 1 && j + 1 <= M - 1)
		Collect(v, i + 1, j + 1, N, M, sum, max);
	return;
} */

ll GetMax(ll x, ll y, ll z)
{
	vector<ll> v = { x,y,z };
	return *max_element(v.begin(), v.end());
}

map<pair<int, int>, ll> dp;
ll Collect(vector<vector<ll>>& v, int i, int j, int N, int M)
{
	auto it = dp.find({ i, j });
	if (it != dp.end())
		return it->second;

	if (i == N - 1 && j == M - 1)
		return v[i][j];

	ll sum1 = LLONG_MIN, sum2 = LLONG_MIN, sum3 = LLONG_MIN;
	if (i + 1 <= N - 1)
		sum1 = Collect(v, i + 1, j, N, M);
	if (j + 1 <= M - 1)
		sum2 = Collect(v, i, j + 1, N, M);
	if (i + 1 <= N - 1 && j + 1 <= M - 1)
		sum3 = Collect(v, i + 1, j + 1, N, M);
	dp[{i, j}] = v[i][j] + GetMax(sum1, sum2, sum3);
	return dp[{ i, j }];
}

int main()
{
	//----------------------------
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//----------------------------

	int N, M;
	cin >> N >> M;

	vector<vector<ll>> Grid(N, vector<ll>(M));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> Grid[i][j];

	cout << Collect(Grid, 0, 0, N, M);
}