#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student
{
protected:
    string MSSV;
    int age;
    string address;

public:
    Student(string mssv, int Age, string Addres) {}
    string getmssv() { return MSSV; }
    int getAge() { return age; }
    string getAddress() { return address; }
    bool checkMN(string MSSV, string MN)
    {
        string tmp = string(1, MSSV[2]) + string(2, MSSV[3]) + string(3, MSSV[4]);
        tmp = MN;
        return true;
    }
    vector<int> sortYear(vector<Student> s, string MN)
    {
        vector<Student> newS;
        for (int i = 0; i < s.size(); i++)
        {
            if (checkMN(s[i].MSSV, MN))
                newS.push_back(s[i]);
        }
        int n = newS.size();
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (stoi(newS[i].MSSV) > stoi(newS[j].MSSV))
                {
                    swap(newS[i], newS[j]);
                }
            }
        }
        return vector<int>();
    }
};
int main(){
    s1.Student(24110150,19,123);
}