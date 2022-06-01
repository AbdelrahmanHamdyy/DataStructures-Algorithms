#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include "string.h"
#include "math.h"
using namespace std;

// A B C D E
void stringGen(int m, int n, int k, string s, vector<string> v, vector<char> g, int& count)
{
	if (s.size() == n)
	{
		int h = k;
		for (int j = 0; j < m; j++)
		{
			if (s.find(v[j]) != string::npos)
				h--;
		}
		if (h <= 0)
			count++;
		return;
	}

	for (int i = 0; i < g.size(); i++)
		stringGen(m, n, k, s + g[i], v, g, count);
}

int main()
{
	int m, n, k;
	cin >> m >> n >> k;
	vector<string> v(m);
	vector<char> g = { 'A', 'B', 'C', 'D', 'E' };
	string s = "";
	for (auto it = v.begin(); it != v.end(); it++)
		cin >> *it;
	int count = 0;
	stringGen(m, n, k, s, v, g, count);
	cout << count;
}