#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <algorithm>
#include <unordered_map>

typedef long long ll;
using namespace std;

struct Node
{
    int index;
    int rating;
    Node* parent;
    vector<Node*> children;
};

map<Node*, ll> dp;
ll maximumSum(Node* root)
{
    if (root->children.size() == 0)
    {
        return root->rating;
    }

    auto it = dp.find(root);
    if (it != dp.end())
        return it->second;

    ll s1 = 0, s2 = root->rating;
    for (int i = 0; i < root->children.size(); i++)
    {
        s1 += maximumSum(root->children[i]);
        for (int j = 0; j < root->children[i]->children.size(); j++)
            s2 += maximumSum(root->children[i]->children[j]);
    }
    return dp[root] = max(s1, s2);
}

/* if (root->children.size() == 0)
{
    return root->rating;
}

// Make dp index & int

auto it = dp.find(root);
if (it != dp.end())
return it->second;

ll s1 = 0, s2 = root->rating;
for (int i = 0; i < root->children.size(); i++)
{
    s1 += maximumSum(root->children[i]);
}
return dp[root] = max(s1, s2); */

ll MaxSum(Node* root)
{
    ll max = 0;
    maximumSum(root);
    for (auto it = dp.begin(); it != dp.end(); it++)
    {
        // cout << it->second << " ";
        if (it->second > max)
            max = it->second;
    }
    // cout << endl;
    return max;
}

int main() {

    // Number of nodes in the tree
    int N;
    cin >> N;

    

    vector<Node*> nodes(N);
    for (int i = 0; i < N; i++) {
        nodes[i] = new Node;
        nodes[i]->index = i;
        cin >> nodes[i]->rating;
    }

    // Iterating over all edges
    int parent, child;
    for (int i = 0; i < N - 1; i++) {
        cin >> parent >> child;
        nodes[child]->parent = nodes[parent];
        nodes[parent]->children.push_back(nodes[child]);
    }

    if (N == 1)
        cout << nodes[0]->rating << endl;
    else
        cout << MaxSum(nodes[0]) << endl;

    return 0;
}