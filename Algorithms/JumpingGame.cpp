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

void print(vector<vector<ll>>& dp, int N)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
}

ll getMax(vector<ll>& v, ll i)
{
	ll Max = LLONG_MIN;
	for (ll j = 0; j < i; j++)
	{
		if (v[j] > Max)
			Max = v[j];
	}
	return Max;
}

ll Game(vector<vector<ll>>& Grid, ll N, vector<vector<ll>>& dp)
{
	ll Max = -1;
	ll M1 = -1;
	ll M2 = -1;
	for (ll i = 0; i < N; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (i == 0 && j == 0)
			{
				M1 = Grid[j][i];
				dp[j][i] = Grid[j][i];
			}
			else if (j == 1 && i == 0) 
			{
				M2 = Grid[j][i];
				dp[j][i] = Grid[j][i];
			}
			else if (j == 0)
			{
				M2 = max(M2, dp[1][i - 1]);
				dp[j][i] = Grid[j][i] + M2;
			}
			else if (j == 1)
			{
				M1 = max(M1, dp[0][i - 1]);
				dp[j][i] = Grid[j][i] + M1;
			}
			if (dp[j][i] >= Max)
				Max = dp[j][i];
		}
	}
	//print(dp, N);
	return Max;
}

int main()
{
	// Bottom Up
	ll N;
	cin >> N;
	vector<vector<ll>> Grid(2, vector<ll>(N));
	for (int i = 0; i < 2; i++)
		for (ll j = 0; j < N; j++)
			cin >> Grid[i][j];
	if (N == 0)
		cout << "0" << endl;
	else
	{
		vector<vector<ll>> dp(2, vector<ll>(N));
		//print(Grid, N);
		cout << Game(Grid, N, dp);
	}
}