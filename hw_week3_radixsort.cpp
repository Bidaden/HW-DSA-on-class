#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// Wait for user to press Enter
void waitForEnter()
{
    cout << "\n Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    int n;
    string str;

    cout << "Enter n: ";
    cin >> n;
    cin.ignore();
    cout << "Enter " << n << " numbers separated by commas: ";
    getline(cin, str);

    cout << " Parsing input string...\n";
    vector<int> arr;
    stringstream ss(str);
    string token;

    while (getline(ss, token, ','))
    {
        if (!token.empty())
        {
            cout << " Found number: " << token << "\n";
            arr.push_back(stoi(token));
        }
    }

    if (arr.size() != n)
    {
        cout << " Number count does not match n.\n";
        return 1;
    }

    cout << "\n Initial Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << "\n";

    waitForEnter();

    cout << " Finding maximum value...\n";
    int maxVal = *max_element(arr.begin(), arr.end());
    cout << " Max value = " << maxVal << "\n";

    int exp = 1;
    int pass = 1;

    // Radix sort
    while (maxVal / exp > 0)
    {

        cout << "\n====================\n";
        cout << "  PASS " << pass << " (exp = " << exp << ")\n";
        cout << "====================\n";

        vector<vector<int>> buckets(10);

        cout << " Distributing numbers into buckets...\n";

        // Place into buckets
        for (int num : arr)
        {
            int digit = (num / exp) % 10;
            cout << " Number " << num << " -> Bucket[" << digit << "]\n";
            buckets[digit].push_back(num);
        }

        // Show bucket contents
        cout << "\n Bucket status:\n";
        for (int i = 0; i < 10; i++)
        {
            cout << "Bucket[" << i << "]: ";
            for (int x : buckets[i])
                cout << x << " ";
            cout << "\n";
        }

        waitForEnter();

        // Rebuild array from buckets
        cout << " Collecting numbers from buckets back to array...\n";
        int index = 0;
        for (int i = 0; i < 10; i++)
        {
            for (int x : buckets[i])
            {
                cout << " Putting " << x << " into arr[" << index << "]\n";
                arr[index++] = x;
            }
        }

        // Show array after collecting
        cout << "\n Array after collecting:\n";
        for (int x : arr)
            cout << x << " ";
        cout << "\n";

        waitForEnter();

        exp *= 10;
        pass++;
    }

    cout << "\n FINAL SORTED ARRAY\n";
    for (int x : arr)
        cout << x << " ";
    cout << "\n";

    return 0;
}
