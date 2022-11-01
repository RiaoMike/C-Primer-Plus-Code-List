// strc_ref.cpp -- using structure references
#include<iostream>
#include<string>
using namespace std;
struct free_throws {
    string name;
    int made;
    int attempts;
    float percent;
};

void display(const free_throws & ft);
void set_pc(free_throws & ft);
free_throws & accumulates(free_throws & target, const free_throws & source);

int main() {
    return 0;
}

void display(const free_throws & ft) {
    cout << "Name: " << ft.name << endl;
    cout << " Made: " << ft.made << "\t";
    cout << "Attempts: " << ft.attempts << "\t";
    cout << "Percent: " << ft.percent << endl;
}

void set_pc(free_throws & ft) {
    if (ft.attempts != 0)
        ft.percent = 100.0f * ft.made / ft.attempts;
    else
        ft.percent = 0;
}