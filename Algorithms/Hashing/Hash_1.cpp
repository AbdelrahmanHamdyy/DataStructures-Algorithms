#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void ReadInput(vector<string>& A)
{
    ifstream input("words20K.txt");
    string s;
    while (input >> s)
        A.push_back(s);
}

void Resolve(int& i, vector<string>& H)
{
    if (H[i] == "")
        return;
    i = (i + 1) % H.size();
    Resolve(i, H);
}

int h(string s)
{
    int key;
    if (s.size() == 1)
        key = 39 * int(s[0]);
    else if (s.size() == 2)
        key = (39 * int(s[0])) + (392 * int(s[1]));
    else if (s.size() == 3)
        key = (39 * int(s[0])) + (392 * int(s[1])) + (393 * int(s[2]));
    else
        key = (39 * int(s[0])) + (392 * int(s[1])) + (393 * int(s[2])) + (394 * int(s[3]));
    
    return (key % 24000);
}

void Hash(vector<string>& A, vector<string>& H)
{
    vector<double> Time;
    int index = 0;
    for (int i = 0; i < 40; i++)
    {
        auto start = high_resolution_clock::now();
        for (int j = 0; j < 500; j++)
        {
            string s = A[index];
            int key = h(s);
            Resolve(key, H); // Linear Probing
            H[key] = s;
            index++;
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << i + 1 << ") Time = " << double(duration.count() / 1000000.0) << " ms" << endl;
        Time.push_back(double(duration.count()) / 1000000.0);
    }
    cout << "Average Time for each set of 500 strings: ";
    double sum = 0;
    for (double t : Time)
        sum += t;
    cout << sum / Time.size() << " ms" << endl;
}

int Delete(vector<string>& H, string s)
{
    int index = h(s);
    int probes = 0;
    string v = H[index];
    while (v != s)
    {
        if (v == "")
            return -1; // Not found
        v = H[++index];
        if (index == H.size())
            index = 0;
        probes++;
    }
    H[index] = "$"; // Deleted
    return probes;
}

void Delete_1000_fromH(vector<string>& A, vector<string>& H)
{
    vector<int> probes;
    for (int i = 14000; i <= 14999; i++)
    {
        probes.push_back(Delete(H, A[i]));
    }
    int min = *min_element(probes.begin(), probes.end());
    int max = *max_element(probes.begin(), probes.end());
    int sum = 0;
    for (int p : probes)
        sum += p;
    cout << "Minimum Number of probes across the 1000 searches = " << min << endl;
    cout << "Maximum Number of probes across the 1000 searches = " << max << endl;
    cout << "Average Number of probes across the 1000 searches = " << sum / probes.size() << endl;
}

int main() {
    vector<string> A;
    ReadInput(A);
    vector<string> H(24000, "");
    Hash(A, H);
    Delete_1000_fromH(A, H);
}
