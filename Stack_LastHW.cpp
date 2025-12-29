#include <iostream>
#include <string>
using namespace std;

class Stack
{
    char a[100];
    int t;

public:
    Stack() { t = -1; }
    bool empty() { return t == -1; }
    char top() { return a[t]; }
    void push(char x) { a[++t] = x; }
    void pop() { t--; }
};

int priority(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

int main()
{
    string infix;
    getline(cin, infix);

    Stack st;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++)
    {
        char c = infix[i];
        if (c == ' ')
            continue;

        if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        {
            postfix += c;
            cout << c << " ";
        }
        else if (c == '(')
        {
            st.push(c);
            cout << c << " ";
        }
        else if (c == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                postfix += st.top();
                cout << st.top() << " ";
                st.pop();
            }
            st.pop();
        }
        else
        {
            while (!st.empty() && priority(st.top()) >= priority(c))
            {
                postfix += st.top();
                cout << st.top() << " ";
                st.pop();
            }
            st.push(c);
            cout << c << " ";
        }
    }

    while (!st.empty())
    {
        postfix += st.top();
        cout << st.top() << " ";
        st.pop();
    }

    cout << endl;
    cout << postfix << endl;
    return 0;
}
