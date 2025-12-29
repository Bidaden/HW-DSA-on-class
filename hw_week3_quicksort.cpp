#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

int recursionLevel = 0;

void printArray(const vector<double> &arr)
{
    for (double x : arr)
        cout << x << " ";
    cout << "\n";
}

int partition(vector<double> &arr, int low, int high)
{
    cout << string(recursionLevel * 2, ' ')
         << "[partition] low=" << low << " high=" << high << "\n";

    double pivot = arr[high];

    cout << string(recursionLevel * 2, ' ')
         << "Pivot = " << pivot << "\n";

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);

            cout << string(recursionLevel * 2, ' ')
                 << " swap(arr[" << i << "], arr[" << j << "])  →  ";
            printArray(arr);
        }
    }

    swap(arr[i + 1], arr[high]);

    cout << string(recursionLevel * 2, ' ')
         << " swap pivot with arr[" << i + 1 << "] → ";
    printArray(arr);

    cout << string(recursionLevel * 2, ' ')
         << "Array after partition: ";
    printArray(arr);

    return i + 1;
}

void quickSort(vector<double> &arr, int low, int high)
{
    cout << string(recursionLevel * 2, ' ')
         << ">> Enter quickSort(low=" << low << ", high=" << high << ")\n";

    cout << string(recursionLevel * 2, ' ')
         << "Current array: ";
    printArray(arr);

    if (low >= high)
    {
        cout << string(recursionLevel * 2, ' ')
             << "<< Return because low >= high (STOP branch)\n";
        return;
    }

    recursionLevel++;
    int pivotIndex = partition(arr, low, high);
    recursionLevel--;

    cout << string(recursionLevel * 2, ' ')
         << "Pivot fixed at index " << pivotIndex << "\n";

    // LEFT
    cout << string(recursionLevel * 2, ' ')
         << "--> RECURSE LEFT (" << low << " , " << pivotIndex - 1 << ")\n";

    recursionLevel++;
    quickSort(arr, low, pivotIndex - 1);
    recursionLevel--;

    // RIGHT
    cout << string(recursionLevel * 2, ' ')
         << "--> RECURSE RIGHT (" << pivotIndex + 1 << " , " << high << ")\n";

    recursionLevel++;
    quickSort(arr, pivotIndex + 1, high);
    recursionLevel--;

    cout << string(recursionLevel * 2, ' ')
         << "<< Exit quickSort(low=" << low << ", high=" << high << ")\n";
}

int main()
{
    string str;
    getline(cin, str);

    vector<double> arr;
    string token;
    stringstream ss(str);

    while (getline(ss, token, ','))
    {
        arr.push_back(stod(token));
    }

    cout << "Original array: ";
    printArray(arr);

    cout << "\n===== START QUICK SORT RECURSION =====\n\n";

    quickSort(arr, 0, arr.size() - 1);

    cout << "\n===== END QUICK SORT =====\n";

    cout << "Sorted array: ";
    printArray(arr);
}
