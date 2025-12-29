#include <iostream>
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
            cout << msg << " [Empty List]" << endl;
            return;
        }
        cout << msg << " ";
        Node *t = head;
        do
        {
            cout << "[" << t->data << "] -> ";
            t = t->next;
        } while (t != head);
        cout << "(" << head->data << ")" << endl;
    }

public:
    CircularList() { head = NULL; }

    void add(int val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
            head->next = head;
        }
        else
        {
            Node *t = head;
            while (t->next != head)
                t = t->next;
            t->next = newNode;
            newNode->next = head;
        }
    }

    void deleteLastOccurrence(int x)
    {
        cout << "\n---------------------------------" << endl;
        cout << "COMMAND: Delete LAST occurrence of " << x << endl;

        if (!head)
        {
            cout << "List is empty. Nothing to delete." << endl;
            return;
        }

        Node *curr = head;
        Node *prev = NULL;

        Node *target = NULL;
        Node *targetPrev = NULL;

        cout << "Starting Search..." << endl;

        do
        {
            if (curr->data == x)
            {
                target = curr;
                targetPrev = prev;
                cout << "  -> Found candidate at Address " << curr << " (Value: " << curr->data << ")" << endl;
            }

            prev = curr;
            curr = curr->next;

        } while (curr != head);

        if (target == NULL)
        {
            cout << "Result: Value " << x << " not found in list." << endl;
            return;
        }

        cout << "Target Identified: Node [" << target->data << "] at Address " << target << endl;

        if (target == head)
        {
            cout << "Action: Deleting HEAD node..." << endl;

            if (head->next == head)
            {
                delete head;
                head = NULL;
                cout << "List became empty." << endl;
            }
            else
            {
                Node *tail = head;
                while (tail->next != head)
                {
                    tail = tail->next;
                }

                head = head->next;
                tail->next = head;
                delete target;
            }
        }
        else
        {
            cout << "Action: Deleting INNER/TAIL node..." << endl;

            if (targetPrev == NULL)
            {
                Node *temp = head;
                while (temp->next != target)
                    temp = temp->next;
                targetPrev = temp;
            }

            targetPrev->next = target->next;
            delete target;
        }

        printState("Status After Delete:");
    }

    void printList()
    {
        printState("Current List:");
    }
};

int main()  
{
    CircularList list;

    list.add(10);
    list.add(20);
    list.add(10);
    list.add(30);
    list.add(10);
    list.add(50);

    list.printList();

    list.deleteLastOccurrence(10);

    list.deleteLastOccurrence(50);

    list.deleteLastOccurrence(99);

    return 0;
}