#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct Node
{
    int key;
    Node* left, * right;
    int height;
};

Node* createNode(int val)
{
    Node* new_node = new Node;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->key = val;
    new_node->height = 0;
    return new_node;
}

Node* Search(Node* x, int val)
{
    if (x == NULL || val == x->key)
        return x;
    else
    {
        Node* n1 = Search(x->left, val);
        if (n1 != NULL)
            return n1;
        Node* n2 = Search(x->right, val);
        if (n2 != NULL)
            return n2;
    }
    return NULL;
}

void GetHeightOfNode(Node* root, int height, int& maxHeight, vector<vector<int>>& levels)
{
    if (root != NULL)
    {
        root->height = height;
        maxHeight = max(maxHeight, height);
        levels[height].push_back(root->key);
        GetHeightOfNode(root->left, height + 1, maxHeight, levels);
        GetHeightOfNode(root->right, height + 1, maxHeight, levels);
    }
    return;
}

Node* insert(Node* root, int n, char ch, int p, int c, vector<Node*>& mp)
{
    if (ch == 'L')
        mp[p]->left = mp[c];
    else
        mp[p]->right = mp[c];
    return mp[c];
}

int findSum(const vector<int>& v)
{
    int sum = 0;
    for (int i = 0; i < v.size(); i++)
        sum += v[i];
    return sum;
}
void inorder(Node* root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}
int main()
{
    int N;
    cin >> N;
    vector<int> v;
    vector<Node*> mp(N);
    int key;
    for (int i = 0; i < N; i++)
    {
        cin >> key;
        v.push_back(key);
        mp[i] = createNode(key);
    }

    Node* root = NULL;
    root = mp[0];
    root->height = 0;

    int E;
    cin >> E;
    char c;
    int ParentIndex, ChildIndex;
    for (int i = 0; i < E; i++)
    {
        cin >> c;
        cin >> ParentIndex >> ChildIndex;
        insert(root, N, c, ParentIndex, ChildIndex, mp);
    }

    int height = 0;
    vector<vector<int>> levels(N);
    GetHeightOfNode(root, 0, height, levels);
    height++;

    int L = v[0] % height;
    int min = *min_element(levels[L].begin(), levels[L].end());
    int k = min % height;
    if (k == 0)
        k = k + 1;
    string s;
    int h = 0;
    while (h < height)
    {
        int sum = findSum(levels[h]);
        s += to_string(sum);
        h += k;
    }
    cout << s << endl;
}