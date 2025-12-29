#include <iostream>
using namespace std;

// ===================== STACK (tự xây dựng) =====================
class Stack
{
private:
    char arr[1024];
    int top;

public:
    Stack() { top = -1; }

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == 1023; }

    void push(char c)
    {
        if (!isFull())
            arr[++top] = c;
    }

    char pop()
    {
        if (!isEmpty())
            return arr[top--];
        return '\0';
    }
};

// ===================== QUEUE (tự xây dựng) =====================
class Queue
{
private:
    char arr[1024];
    int front, rear;

public:
    Queue()
    {
        front = 0;
        rear = -1;
    }

    bool isEmpty() { return rear < front; }

    void enqueue(char c)
    {
        arr[++rear] = c;
    }

    char dequeue()
    {
        if (!isEmpty())
            return arr[front++];
        return '\0';
    }
};

// ===============================================================
//  CHUYỂN CHAR → BINARY (dùng stack)
// ===============================================================
void charToBinary(char c, char binaryOut[9])
{
    Stack st;
    int ascii = (int)c;
    while (ascii > 0)
    {
        st.push((ascii % 2) + '0');
        ascii /= 2;
    }
    int i = 0;
    while (!st.isEmpty())
    {
        binaryOut[i++] = st.pop();
    }
    while (i < 8)
        binaryOut[i++] = '0';
    binaryOut[8] = '\0';

    // đảo lại chuẩn 8 bit
    for (int j = 0; j < 4; j++)
    {
        char tmp = binaryOut[j];
        binaryOut[j] = binaryOut[7 - j];
        binaryOut[7 - j] = tmp;
    }
}

// ===============================================================
//  CHUYỂN BINARY (8 bit) → CHAR (dùng stack)
// ===============================================================
char binaryToChar(char binaryIn[9])
{
    Stack st;
    for (int i = 0; i < 8; i++)
        st.push(binaryIn[i]);

    int value = 0;
    int base = 1;
    while (!st.isEmpty())
    {
        char bit = st.pop();
        if (bit == '1')
            value += base;
        base *= 2;
    }
    return (char)value;
}

// ===============================================================
//  MÃ HÓA CHUỖI (text → binary)
// ===============================================================
void encodeMessage(Queue &q, char output[][9], int &count)
{
    count = 0;
    while (!q.isEmpty())
    {
        char c = q.dequeue();
        char temp[9];
        charToBinary(c, temp);
        for (int i = 0; i < 9; i++)
            output[count][i] = temp[i];
        count++;
    }
}

// ===============================================================
//  GIẢI MÃ (binary → text)
// ===============================================================
void decodeMessage(char binary[][9], int count)
{
    cout << "\n[Máy B giải mã] => ";
    for (int i = 0; i < count; i++)
    {
        char c = binaryToChar(binary[i]);
        cout << c;
    }
    cout << endl;
}

// ===============================================================
//                         MAIN
// ===============================================================
int main()
{
    Queue q;
    char msg[1024];

    cout << "Nhap chuoi can truyen: ";
    cin.getline(msg, 1024);

    // Đưa từng ký tự vào queue
    for (int i = 0; msg[i] != '\0'; i++)
        q.enqueue(msg[i]);

    // Mã hóa
    char binaryPacket[1024][9];
    int count = 0;
    encodeMessage(q, binaryPacket, count);

    cout << "\n[Máy A đóng gói & mã hóa]\nBinary gửi đi:\n";
    for (int i = 0; i < count; i++)
    {
        cout << binaryPacket[i] << " ";
    }
    cout << endl;

    // Giải mã bên máy B
    decodeMessage(binaryPacket, count);

    return 0;
}
