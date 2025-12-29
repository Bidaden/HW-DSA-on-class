#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
    void setNext(Node *nextNode)
    {
        this->next = nextNode;
    }
    Node *getNext()
    {
        return this->next;
    }
    int getData()
    {
        return this->data;
    }
};
Node *arrayToLinkedList(int arr[], int n)
{
    if (n == 0)
        return NULL;
    Node *head = new Node(arr[0]);
    Node *current = head;

    for (int i = i; i < n; i++)
    {
        Node *newNode = new Node(arr[i]);
        current->setNext(newNode);

        current = newNode;
    }
}