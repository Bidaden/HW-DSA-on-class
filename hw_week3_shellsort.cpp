#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Pause until user presses Enter
void waitForEnter()
{
    cout << "\nPress ENTER to continue...";
    cin.ignore();
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

    vector<int> arr;
    stringstream ss(str);
    string temp;
    while (getline(ss, temp, ','))
    {
        arr.push_back(stoi(temp));
    }

    // Shell Sort Debug
    cout << "\n===== Shell Sort Debug Mode =====\n";

    int step = 1;
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        cout << "\n--- GAP = " << gap << " ---\n";
        waitForEnter();

        for (int i = gap; i < n; i++)
        {
            int tempVal = arr[i];
            int j = i;

            cout << "\nStep " << step++ << ": i = " << i
                 << ", value = " << tempVal << "\n";

            while (j >= gap && arr[j - gap] > tempVal)
            {
                arr[j] = arr[j - gap];
                j -= gap;

                // Show intermediate state
                cout << "  Moved " << arr[j]
                     << " to position " << j + gap << "\n";

                waitForEnter();
            }
            arr[j] = tempVal;

            // Show array after insertion
            cout << "Array: ";
            for (int k = 0; k < n; k++)
                cout << arr[k] << " ";
            cout << "\n";

            waitForEnter();
        }
    }

    cout << "\n===== Sorted Array =====\n";
    for (int x : arr)
        cout << x << " ";
    cout << "\n";

    return 0;
}
