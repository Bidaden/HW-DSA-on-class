#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Gift
{
    string name;
    int distance;
};

class Santa
{
public:
    vector<Gift> st;

    Gift pop()
    {
        Gift g = st.back();
        st.pop_back();
        return g;
    }

    void push(Gift g)
    {
        vector<Gift> temp;

        while (!st.empty() && st.back().distance < g.distance)
        {
            temp.push_back(st.back());
            st.pop_back();
        }

        st.push_back(g);

        while (!temp.empty())
        {
            st.push_back(temp.back());
            temp.pop_back();
        }
    }
};

int main()
{
    vector<Santa> santas(26);

    vector<Gift> gifts = {
        {"Apple", 45}, {"Ball", 12}, {"Car", 78}, {"Doll", 33}, {"Egg", 90}, {"Fan", 21}, {"Game", 55}, {"Hat", 10}, {"Ice", 66}, {"Jacket", 42}, {"Key", 5}, {"Lamp", 88}, {"Mouse", 31}, {"Notebook", 70}, {"Orange", 15}, {"Pen", 9}, {"QueenToy", 95}, {"Ring", 23}, {"Shoe", 61}, {"Toy", 18}, {"Umbrella", 50}, {"Violin", 84}, {"Watch", 27}, {"Xylophone", 92}, {"Yoyo", 14}, {"ZooToy", 39}, {"Apple2", 47}, {"Ball2", 19}, {"Car2", 80}, {"Doll2", 36}, {"Egg2", 91}, {"Fan2", 22}, {"Game2", 58}, {"Hat2", 11}, {"Ice2", 68}, {"Jacket2", 44}, {"Key2", 6}, {"Lamp2", 89}, {"Mouse2", 34}, {"Notebook2", 73}, {"Orange2", 17}, {"Pen2", 8}, {"QueenToy2", 96}, {"Ring2", 25}, {"Shoe2", 63}, {"Toy2", 20}, {"Umbrella2", 53}, {"Violin2", 86}};

    for (auto &g : gifts)
    {
        if (g.name.empty())
            continue;
        int santaIndex = g.name[0] - 'A';
        santas[santaIndex].push(g);
    }

    for (int i = 0; i < 26; i++)
    {
        cout << "\nSanta " << char('A' + i) << ":\n";
        Santa &santa = santas[i];
        while (!santa.st.empty())
        {
            Gift g = santa.pop();
            cout << "NAME: " << g.name
                 << ", DISTANCE: " << g.distance << endl;
        }
    }
}
