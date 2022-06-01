#include <iostream>
#include <vector>
#include <stack>

typedef long long ll;
using namespace std;

stack<int> s;
void TSort(vector<vector<int>>& graph, vector<bool>& check, int i)
{
	check[i] = true;
	for (int j = 0; j < graph[i].size(); j++)
	{
		if (!check[graph[i][j]])
			TSort(graph, check, graph[i][j]);
	}
	s.push(i);
}

void printStack(stack<int>& s)
{
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
}

int main()
{
	int N; cin >> N;
	int t1, t2;
	vector<vector<int>> adj_list(N);
	for (int i = 0; i < N; i++)
	{
		cin >> t1 >> t2;
		if (t1 != -1)
		{
			adj_list[t1].push_back(i);
		}
		if (t2 != -1)
		{
			adj_list[t2].push_back(i);
		}
	}
	vector<bool> check(N, 0);
	for (int i = 0; i < N; i++)
	{
		if (!check[i])
			TSort(adj_list, check, i);
	}
	printStack(s);
}