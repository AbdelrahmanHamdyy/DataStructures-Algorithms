#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;
using namespace std::chrono;

// Insertion
void InsertionSort(vector<int>& v, int p, int r);

// Selection
void SelectionSort(vector<int>& v);

// Quick
int Partition(vector<int>& v, int p, int r);
int Randomized_Partition(vector<int>& v, int p, int r);
void QuickSort(vector<int>& v, int p, int r);

// Merge
void Merge(vector<int>& v, int p, int q, int r);
void MergeSort(vector<int>& v, int p, int r);

// Hybrid
void Hybrid(vector<int>& v, int p, int r);
bool isSorted(vector<int>& v);

int main(int argc, char** argv)
{
    vector<int> v;
    string x = argv[1]; // 0, 1, 2, 3, 4
    int s; // data

    ifstream input(argv[2]);
    while (input >> s)
        v.push_back(s);

    if (x == "0")
    {
        auto start = high_resolution_clock::now();
        SelectionSort(v);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        ofstream time(argv[4]);
        time << to_string(duration.count() / 1000000.0);
    }
    else if (x == "1")
    {
        auto start = high_resolution_clock::now();
        InsertionSort(v, 0, v.size() - 1);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        ofstream time(argv[4]);
        time << to_string(duration.count() / 1000000.0);
    }
    else if (x == "2")
    {
        auto start = high_resolution_clock::now();
        MergeSort(v, 0, v.size() - 1);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        ofstream time(argv[4]);
        time << to_string(duration.count() / 1000000.0);
    }
    else if (x == "3")
    {
        auto start = high_resolution_clock::now();
        QuickSort(v, 0, v.size() - 1);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        ofstream time(argv[4]);
        time << to_string(duration.count() / 1000000.0);
    }
    else
    {
        auto start = high_resolution_clock::now();
        Hybrid(v, 0, v.size() - 1);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        ofstream time(argv[4]);
        time << to_string(duration.count() / 1000000.0);
    }

    ofstream output(argv[3]);
    for (int i = 0; i < v.size(); i++)
        output << to_string(v[i]) << endl;
}

void InsertionSort(vector<int>& v, int p, int r)
{
    for (int i = p; i < r + 1; i++)
    {
        int j = i - 1; // walker 
        int key = v[i];
        while (j >= p && v[j] > key) // Stop when key is greater than all previous values
        {
            v[j + 1] = v[j]; // shift
            j--; // decrement walker
        }
        v[j + 1] = key; // Insert the element in its correct position
    }
}

void SelectionSort(vector<int>& v)
{
    int min;
    for (int i = 0; i < v.size(); i++)
    {
        min = v[i];
        int index = i; // Index of the min
        for (int j = i; j < v.size(); j++) // Get the minimum in this sub-vector
        {
            if (v[j] < min)
            {
                min = v[j];
                index = j;
            }
        }
        swap(v[i], v[index]); // Swap the min with the original element
    }
}

int Partition(vector<int>& v, int p, int r)
{
    int i = p - 1; // End of the first half
    int x = v[r]; // pivot
    for (int j = p; j < r; j++) // Loop until j reaches r (the pivot)
    {
        if (v[j] <= x)
        {
            i++;
            swap(v[i], v[j]); // Swap the value to the left half and increment i
        }
    }
    swap(v[i + 1], v[r]); // Place the pivot in its correct position 
    // where its left is less and its right is greater than it
    return (i + 1);
}

int Randomized_Partition(vector<int>& v, int p, int r)
{
    srand(time(0));
    int i = (rand() % (r - p + 1)) + p; // Random(i) between p & r
    swap(v[i], v[r]); // Make i the pivot and then partition normally
    return Partition(v, p, r);
}

void QuickSort(vector<int>& v, int p, int r)
{
    if (p < r)
    {
        int q = Randomized_Partition(v, p, r); // Pivot after it has been placed correctly
        QuickSort(v, p, q - 1); // Sort left sub-vector
        QuickSort(v, q + 1, r); // Sort right sub-vector
    }
}

void Merge(vector<int>& v, int p, int q, int r)
{
    int LSize = q - p + 1; // Length of L
    int RSize = r - q; // Length of R

    vector<int> L(LSize + 1); // Left sub-vector
    vector<int> R(RSize + 1); // right sub-vector

    // Infinity in the end of each sub-vector to minimize comparisons
    L[LSize] = INT_MAX;
    R[RSize] = INT_MAX;

    for (int i = 0; i < LSize; i++)
        L[i] = v[p + i]; // Fill L
    for (int i = 0; i < RSize; i++)
        R[i] = v[q + i + 1]; // Fill R

    int i = 0; // index of L
    int j = 0; // index of R

    for (int k = p; k <= r; k++)
    {
        // Merge both vectors (Place the lower value in the list first) until they reach INT_MAX
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
    }
}

void MergeSort(vector<int>& v, int p, int r)
{
    if (p < r)
    {
        int q = (r + p) / 2; // Middle
        MergeSort(v, p, q); 
        MergeSort(v, q + 1, r); // Split the list
        Merge(v, p, q, r); // Merge all together
    }
}

void Hybrid(vector<int>& v, int p, int r) // A hybrid algorithm between insertion and quick sort
{
    if (p < r)
    {
        // Use quick sort normally to partition the data and once we reach a certain size
        // where inserion is better than quick sort --> Use insertion sort
        if (r - p + 1 <= 50)
            InsertionSort(v, p, r);
        else
        {
            int q = Randomized_Partition(v, p, r);
            Hybrid(v, p, q - 1);
            Hybrid(v, q + 1, r);
        }
    }
}

bool isSorted(vector<int>& v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        if (v[i] > v[i + 1])
            return false;
    }
    return true;
}
