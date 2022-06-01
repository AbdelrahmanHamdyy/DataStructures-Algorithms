#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <algorithm>
#include <unordered_map>

typedef long long ll;
using namespace std;

int main()
{
	// Set of challenges --> Deadline for each challenge
	// Penalty charged if the challenge was played after the deadline
	// Make a timetable detailing the order in which to play these challenges
	// --> First challenge begins at T = 0 & ends at T = 1
	// --> Second challenge begins at T = 1 & ends at T = 2 and so on...
	// Find a timetable that minimizes the total penalty
	int n;
	cin >> n;
	vector<pair<ll, int>> mp(n);
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		int d;
		cin >> d;
		if (d > max)
			max = d;
		mp[i].second = d;
	}
	vector<ll> t(max + 1, -1);
	for (int i = 0; i < n; i++)
	{
		ll p;
		cin >> p;
		mp[i].first = p;
	}
	sort(mp.begin(), mp.end(), greater<>());
	ll sum = 0;
	for (int i = 0; i < n; i++)
	{
		int index = mp[i].second;
		if (t[index] == -1)
			t[index] = mp[i].first;
		else
		{
			bool flag = false;
			while (!flag && index >= 1)
			{
				if (mp[i].first > t[index])
				{
					flag = true;
					t[index] = mp[i].first;
				}
				index--;
			}
			if (!flag)
				sum += mp[i].first;
		}
	}
	cout << sum << endl;
}