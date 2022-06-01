#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int ArithmeticSub(vector<int>& v, int D, int M)
{
    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < v.size(); i++)
        mp[v[i]].push_back(i); // Insert each element with all its available indices in a vector
    vector<int> r;
    int count = 0; // Result
    // 1 1 3 3 5
    for (auto it = mp.begin(); it != mp.end(); it++) // Traverse the map
    {
        int n = it->first; // 1
        n += D;
        auto S = mp.find(n); // 3
        if (S != mp.end()) // if 3 is found
        {
            int c = 0;
            while (c < it->second.size()) // Loop through all indices of 1
            {
                int index = it->second[c];
                vector<int> r = S->second; // indices of the following number (3)
                int m = 0;
                while (m < r.size()) // Loop through them all and check
                {
                    if (r[m] > index) // Compare indices
                    {
                        if (M == 3) // Do the same thing one more time if M == 3
                        {
                            int y = n + D;
                            auto it2 = mp.find(y);
                            if (it2 != mp.end())
                            {
                                vector<int> third = it2->second;
                                int x = 0;
                                while (x < third.size())
                                {
                                    if (third[x] > r[m])
                                        count++;
                                    x++;
                                }
                            }
                        }
                        else
                            count++;
                    }
                    m++;
                }
                c++;
            }
        }
    }
    return count;
}

int main()
{
    int N, D, M;
    cin >> N >> D >> M;
    vector<int> v(N);
    for (int i = 0; i < N; i++)
        cin >> v[i];
    cout << ArithmeticSub(v, D, M) << endl;
}
