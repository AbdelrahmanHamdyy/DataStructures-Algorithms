#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left, * right;
};

struct Dep_Node {
    int key;
    Dep_Node* left, * right;
    Node* root = NULL;
};

template<class T>
T* createNode(int val)
{
    T* new_node = new T;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->key = val;
    return new_node;
}

template<class T>
T* insert(T*& root, int val)
{
    T* new_node = createNode<T>(val);
    T* x = root;
    T* y = NULL;

    while (x != NULL) {
        y = x;
        if (val < x->key)
            x = x->left;
        else
            x = x->right;
    }
    if (y == NULL)
        y = new_node;
    else if (val < y->key)
        y->left = new_node;
    else
        y->right = new_node;
    return new_node;
}

int m = 0;
template<class T>
T*& Search(T*& x, int val)
{
    if (x == NULL || val == x->key)
        return x;
    if (val < x->key)
    {
        m++;
        return Search(x->left, val);
    }
    else
    {
        m++;
        return Search(x->right, val);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N, Q;
    cin >> N >> Q;
    Dep_Node* dep = NULL;
    int key, id;
    for (int i = 0; i < N; i++)
    {
        cin >> key >> id;
        Dep_Node* n = Search(dep, key);
        if (n != NULL)
        {
            if (n->root == NULL)
                n->root = insert(n->root, id);
            else
                insert(n->root, id);
        }
        else
        {
            if (i == 0)
            {
                dep = insert(dep, key);
                dep->root = insert(dep->root, id);
            }
            else
            {
                Dep_Node* N = insert(dep, key);
                N->root = insert(N->root, id);
            }

        }
    }
    vector<pair<int, int>> q;
    for (int i = 0; i < Q; i++)
    {
        cin >> key >> id;
        q.push_back(make_pair(key, id));
    }
    for (int i = 0; i < Q; i++)
    {
        int moves = 0;
        m = 0;
        bool found = 0;
        key = q[i].first;
        id = q[i].second;
        Dep_Node* node = Search(dep, key);
        if (node != NULL)
        {
            moves += (m + 1);
            m = 0;
            Node* x = Search(node->root, id);
            if (x == NULL)
                moves += m;
            else moves += (m + 1);
            if (x)
                found = 1;
        }
        else
            moves += m;

        cout << moves << " " << found << endl;
    }
}
