#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <unordered_map>

typedef long long ll;
using namespace std;

void print(vector<int> v)
{
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

/* Dynamic Programming: Large problem decomposing it
   into smaller instances of the same problem and we also 
   have an overlapping structure in the recursion */

/* Memoization: Store some duplicate subproblems and in that
   way I can get their results later on */

// Fibonacci --> 1 1 2 3 5 8 13 21 34 ....
int fib(int n)
{
	if (n <= 2)
		return 1;
	return fib(n - 1) + fib(n - 2);
}

map<int, ll> mem1;
ll fib_dp(int n)
{
	if (n <= 2)
		return 1;
	auto it = mem1.find(n);
	if (it != mem1.end())
		return it->second;
	else
		mem1[n] = fib_dp(n - 1) + fib_dp(n - 2);
	return mem1[n];
}

// GridTraveler (Down/Right in a mxn grid)
int gridTraveler(int m, int n)
{
	if (m == 1 || n == 1)
		return 1;
	if (m == 0 || n == 0)
		return 0;
	return gridTraveler(m - 1, n) + gridTraveler(m, n - 1);
}

map<pair<int, int>, ll> mem2;
ll gridTraveler_dp(int m, int n)
{
	if (m == 1 || n == 1)
		return 1;
	if (m == 0 || n == 0)
		return 0;
	auto it = mem2.find({ m,n });
	if (it != mem2.end())
		return it->second;
	mem2[{m,n}] = gridTraveler_dp(m - 1, n) + gridTraveler_dp(m, n - 1);
	return mem2[{m, n}];
}

/* Memoization Recipe
1. Make it work
    - Visualize the problem as a tree
	- Implement the tree using recursion
	- Test it
2. Make it efficient
    - Add a memo object
	- Add a base case to return memo values (Do not remove
	  other base cases)
	- Store return values into the memo
*/

// CanSum(targetNumber, array of numbers) --> return bool
bool canSum(int n, vector<int> v)
{
	if (n == 0)
		return 1;
	if (n < 0)
		return 0;
	for (auto i : v)
		if (canSum(n - i, v))
			return 1;
	return 0;
}

map<int, bool> mem3;
bool canSum_dp(int n, vector<int> v)
{
	if (n == 0)
		return 1;
	if (n < 0)
		return 0;
	auto it = mem3.find(n);
	if (it != mem3.end())
		return it->second;
	for (auto i : v)
	{
		if (canSum_dp(n - i, v))
		{
			mem3[n - i] = true;
			return true;
		}
	}
	mem3[n] = false;
	return false;
}

// HowSum(targetSum, array of numbers) --> return any combination
// that sums to n
// 0 returns empty array
vector<int> result;
vector<int> howSum(int n, vector<int> v, bool& flag)
{
	flag = 1;
	if (n == 0)
		return result;
	if (n < 0)
	{
		flag = 0;
		return result;
	}
	for (auto i : v)
	{
		result = howSum(n - i, v, flag);
		if (flag)
		{
			result.push_back(i);
			return result;
		}
	}
	flag = 0;
	return result;
}

map<int, vector<int>> mem4;
vector<int> howSum_dp(int n, vector<int> v, bool& flag)
{
	flag = 1;
	if (n == 0)
		return mem4[n];
	else
		flag = 0;
	if (n < 0)
	{
		flag = 0;
		return mem4[n];
	}
	auto it = mem4.find(n);
	if (it != mem4.end())
		return it->second;
	for (auto i : v)
	{
		mem4[n] = howSum_dp(n - i, v, flag);
		if (flag)
		{
			mem4[n].push_back(i);
			return mem4[n];
		}
	}
	flag = 0;
	if (mem4[n].size() < 1)
		mem4[n].push_back(-1); // NULL
	return mem4[n];
}

// BestSum (return Shortest combination)

// canConstruct
map<string, bool> mp;
bool canConstruct(string target, vector<string> wordBank)
{
	if (target == "") return true;
	auto it = mp.find(target);
	if (it != mp.end())
		return it->second;
	for (string s : wordBank)
	{
		if (target.substr(0, s.size()) == s)
		{
			string str = target.substr(s.size(), target.size());
			mp[str] = canConstruct(str, wordBank);
			if (mp[str])
				return true;
		}
	}
	return false;
}

// countConstruct
map<string, int> w;
int countConstruct(string target, vector<string> wordBank)
{
	if (target == "") return 1;
	auto it = w.find(target);
	if (it != w.end())
		return w[target];
	int sum = 0;
	for (string s : wordBank)
	{
		if (target.substr(0, s.size()) == s)
		{
			string str = target.substr(s.size(), target.size());
			sum += countConstruct(str, wordBank);
		}
	}
	w[target] = sum;
	return w[target];
}

// Tabulation
// Fibonacci
ll Tfib(int n)
{
	vector<ll> dp(n + 1, 0);
	dp[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	return dp[n];
}



int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	/////////////////////////////
	cout << "Fib" << endl;
	cout << fib(6) << endl;
	cout << fib(7) << endl;
	cout << fib(8) << endl;
	cout << fib_dp(50) << endl;
	/////////////////////////////
	cout << "Grid" << endl;
	cout << gridTraveler(3, 3) << endl;
	cout << gridTraveler_dp(18, 18) << endl;
	/////////////////////////////
	cout << "CanSum" << endl;
	vector<int> C1 = { 2, 4 };
	cout << canSum(8, C1) << endl;
	vector<int> C2 = { 14, 7 };
	cout << canSum_dp(300, C2) << endl;
	/////////////////////////////
	cout << "HowSum" << endl;
	vector<int> C3 = { 2, 3, 5 };
	bool flag = 1;
	vector<int> result = howSum(8, C3, flag);
	print(result);
	vector<int> C4 = { 200, 100, 150 };
	result = howSum_dp(300, C4, flag);
	print(result);
	/////////////////////////////
	cout << "canConstruct" << endl;
	string s = "skateboard";
	vector<string> S1 = { "ska", "te", "board" };
	cout << canConstruct(s, S1) << endl;
	/////////////////////////////
	cout << "countConstruct" << endl;
	string s2 = "purple";
	vector<string> S2 = { "purp", "p", "ur", "le", "purpl" };
	cout << countConstruct(s2, S2) << endl;
	/////////////////////////////
	cout << "Tfib" << endl;
	cout << Tfib(50) << endl;
}
