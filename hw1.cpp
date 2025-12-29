#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

void bubble(vector<double> &a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

void selectionsort(vector<double> &a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        int m = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[m])
                m = j;
        swap(a[i], a[m]);
    }
}

void mergesort(vector<double> &a)
{
    if (a.size() <= 1)
        return;
    int mid = a.size() / 2;
    vector<double> L(a.begin(), a.begin() + mid), R(a.begin() + mid, a.end());
    mergesort(L);
    mergesort(R);
    merge(L.begin(), L.end(), R.begin(), R.end(), a.begin());
}

void quicksort(vector<double> &a, int l, int r)
{
    if (l >= r)
        return;
    double p = a[(l + r) / 2];
    int i = l, j = r;
    while (i <= j)
    {
        while (a[i] < p)
            i++;
        while (a[j] > p)
            j--;
        if (i <= j)
            swap(a[i++], a[j--]);
    }
    if (l < j)
        quicksort(a, l, j);
    if (i < r)
        quicksort(a, i, r);
}

int main()
{
    int n = 200000;
    vector<double> a(n);
    for (auto &x : a)
        x = rand();

    vector<double> b = a, c = a, d = a, e = a;

    auto t1 = high_resolution_clock::now();
    bubble(b);
    auto t2 = high_resolution_clock::now();
    cout << "Bubble: " << duration<double>(t2 - t1).count() << "s\n";

    t1 = high_resolution_clock::now();
    selectionsort(c);
    t2 = high_resolution_clock::now();
    cout << "Selection: " << duration<double>(t2 - t1).count() << "s\n";

    t1 = high_resolution_clock::now();
    mergesort(d);
    t2 = high_resolution_clock::now();
    cout << "Merge: " << duration<double>(t2 - t1).count() << "s\n";

    t1 = high_resolution_clock::now();
    quicksort(e, 0, e.size() - 1);
    t2 = high_resolution_clock::now();
    cout << "Quick: " << duration<double>(t2 - t1).count() << "s\n";
}
