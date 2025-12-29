#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node
{
public:
    int id;
    Node *next;
    Node(int val) : id(val), next(NULL) {}
};

class JosephusCLL
{
private:
    Node *head;

    void printState()
    {
        if (!head)
            return;
        Node *t = head;
        cout << "   [List]: ";
        do
        {
            cout << t->id << " -> ";
            t = t->next;
        } while (t != head);
        cout << "(" << head->id << ")" << endl;
    }

public:
    JosephusCLL() { head = NULL; }

    void buildCircle(int n)
    {
        if (n <= 0)
            return;
        head = new Node(1);
        head->next = head;

        for (int i = 2; i <= n; i++)
        {
            Node *newNode = new Node(i);
            newNode->next = head->next;
            head->next = newNode;
            head = newNode;
        }
        head = head->next;
    }

    void play(int n, int k)
    {
        cout << "\n---------------------------------" << endl;
        cout << "START GAME: N=" << n << ", K=" << k << endl;

        buildCircle(n);

        if (k <= 0)
            return;

        if (k == 1)
        {
            cout << "Mode K=1: Eliminating consecutive players..." << endl;
            while (head->next != head)
            {
                printState();

                cout << "   -> Eliminating ID " << head->id << " (replaced by " << head->next->id << ")" << endl;

                Node *victim = head->next;
                head->id = victim->id;
                head->next = victim->next;
                delete victim;
            }
            cout << ">>> WINNER: " << head->id << endl;
            delete head;
            head = NULL;
            return;
        }

        while (head->next != head)
        {
            printState();

            cout << "   -> Skipping " << k - 1 << " steps..." << endl;
            for (int i = 0; i < k - 2; i++)
            {
                head = head->next;
            }

            Node *victim = head->next;
            cout << "   -> Standing at " << head->id << ". Eliminating neighbor " << victim->id << endl;

            head->next = victim->next;
            delete victim;

            head = head->next;
        }

        cout << ">>> WINNER: " << head->id << endl;
        delete head;
        head = NULL;
    }
};

int main()
{
    srand(time(0));
    JosephusCLL game;

    game.play(10, 3);

    int randomN = 5 + rand() % 6;
    int kOdd = 1 + 2 * (rand() % 3);
    int kEven = 2 + 2 * (rand() % 3);

    cout << "\n\n=== RANDOM TEST COMPARISON ===" << endl;
    game.play(randomN, kOdd);
    game.play(randomN, kEven);

    return 0;
}