#include <iostream>
#include <limits>
#include <string>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int val) : data(val), next(NULL) {}
};

class CircularList
{
private:
    Node *head;

    void printState(string msg)
    {
        if (!head)
        {
            cout << msg << " List is Empty" << endl;
            return;
        }
        cout << msg << " [Current Head: " << head->data << "] -> ";

        Node *t = head->next;
        while (t != head)
        {
            cout << t->data << " -> ";
            t = t->next;
        }
        cout << "(" << head->data << ")" << endl;
    }

public:
    CircularList() { head = NULL; }

    void insertFixed(int val)
    {
        cout << "\n---------------------------------" << endl;
        cout << "INPUT: " << val << endl;
        Node *newNode = new Node(val);

        if (!head)
        {
            head = newNode;
            head->next = head;
            printState("Done (Init):");
            return;
        }

        if (val < head->data)
        {
            cout << "  -> Val < Head: SWAP!" << endl;
            newNode->data = head->data;
            newNode->next = head->next;
            head->data = val;
            head->next = newNode;
            printState("Done (Swapped):");
            return;
        }

        if (head->next == head)
        {
            cout << "  -> Single Node detected. Appending..." << endl;
            head->next = newNode;
            newNode->next = head;
            printState("Done (Single append):");
            return;
        }

        while (true)
        {
            if (head->data <= val && head->next->data >= val)
            {
                break;
            }

            if (head->data > head->next->data)
            {
                if (val >= head->data || val <= head->next->data)
                {
                    break;
                }
            }

            head = head->next;
            printState("  ...Head moving forward...");
        }

        newNode->next = head->next;
        head->next = newNode;

        printState("Done (Inserted):");
    }
};

int main()
{
    CircularList list;
    int n;

    cout << "=== DEBUG MODE: SORTED CIRCULAR LIST ===" << endl;
    cout << "Nhap day so cach nhau boi dau cach (VD: 5 2 8 1 9 -1):" << endl;

    while (true)
    {
        cin >> n;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (n == -1)
            break;

        list.insertFixed(n);
    }

    return 0;
}