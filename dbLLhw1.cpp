#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int val) : data(val), next(NULL) {}
};

class LinkedList
{
private:
    Node *head;

    void print(Node *n)
    {
        while (n)
        {
            cout << n->data << " -> ";
            n = n->next;
        }
        cout << "NULL";
    }

public:
    LinkedList() { head = NULL; }

    void pushBack(int val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
            return;
        }
        Node *t = head;
        while (t->next)
            t = t->next;
        t->next = newNode;
    }

    void reverse()
    {
        Node *prev = NULL;
        Node *next = NULL;

        cout << "Initial: ";
        print(head);
        cout << "\n\n";

        while (head != NULL)
        {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
            cout << "Done: ";
            print(prev);
            cout << " | Todo: ";
            print(head);
            cout << endl;
        }
        head = prev;
    }
};

int main()
{
    LinkedList list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(5);
    list.pushBack(7);

    list.reverse();

    return 0;
}