#include<iostream>
#define MAXLENGTH 4
using namespace std;

static int step = 0;

// plate: 1, 2, 3...
// pillar: 'a', 'b', 'c'
typedef struct {
    int array[MAXLENGTH];
    int len;
}pip, * pillar; // 柱子结构类型，int数组上的数字大小代表盘子大小（0代表没有）

// 状态类，用于画出每个状态的图形
class Status {
private:
    // three pillar
    pillar a;
    pillar b;
    pillar c;
public:
    Status();
    void Move(char begin, char end);
    void PrintStatus();
    void PrintRow(int x, int y, int z);
    void PrintSingle(int x);
    ~Status();
};

Status::Status() {
    a = new pip;
    b = new pip;
    c = new pip;

    for (int i = 0; i < MAXLENGTH; i++) {
        a->array[i] = MAXLENGTH - i;    // 刚开始每个盘子都在a柱子上
        b->array[i] = 0;
        c->array[i] = 0;
    }

    a->len = MAXLENGTH;
    b->len = c->len = 0;
}

// 移动盘子，改变此时的状态
// note that must switch(begin) first, then switch(end)
void Status::Move(char begin, char end) {
    int plate;
    switch (begin) {
    case 'a':
        // get the top plate from a pillar
        plate = a->array[a->len - 1];
        a->array[a->len - 1] = 0;
        a->len--;
        break;
    case 'b':
        plate = b->array[b->len - 1];
        b->array[b->len - 1] = 0;
        b->len--;
        break;
    case 'c':
        plate = c->array[c->len - 1];
        c->array[c->len - 1] = 0;
        c->len--;
        break;
    }

    switch (end) {
    case 'a':
        a->array[a->len] = plate;
        a->len++;
        break;
    case 'b':
        b->array[b->len] = plate;
        b->len++;
        break;
    case 'c':
        c->array[c->len] = plate;
        c->len++;
        break;
    }
}

// 打印状态，调用PrintRow函数按行打印
void Status::PrintStatus() {
    for (int i = MAXLENGTH - 1; i >= 0; i--) {
        PrintRow(a->array[i], b->array[i], c->array[i]);
    }
    for (int i = 0; i < 6 * MAXLENGTH + 6; i++) {
        cout << "=";
    }
    cout << endl;
}

void Status::PrintRow(int x, int y, int z) {
    PrintSingle(x);
    PrintSingle(y);
    PrintSingle(z);
    cout << endl;
}

//  对每一行打印盘子的状态
void Status::PrintSingle(int x) {
    if (x == 0) {
        for (int i = 0; i < 2 * MAXLENGTH + 2; i++) {
            cout << " ";
        }
    }
    else {
        for (int i = 0; i < MAXLENGTH - x; i++) cout << " ";
        cout << "/";
        for (int i = 0; i < 2 * x; i++) cout << "-";
        cout << "\\";
        for (int i = 0; i < MAXLENGTH - x; i++) cout << " ";
    }
}

Status::~Status() {
    delete a;
    delete b;
    delete c;
}

void Print(char begin, char end) {
    cout << "Step " << ++step << ": ";
    cout << begin << " >>> " << end << endl;
}

// 算法的主要部分，n为移动的盘子数，从哪个柱子借助哪个柱子移动到哪个柱子
// 传入状态类用于打印每个状态图
void Hanot(int n, char begin, char tmp, char end, Status& hanot) {
    if (n == 1) {   // 若只移动一个盘子，则直接改变状态并打印
        Print(begin, end);
        hanot.Move(begin, end);
        hanot.PrintStatus();
    }
    else {
        // 先把上面n-1个盘子移动到中介柱子上，再把begin的第n个盘子移动到end柱子
        Hanot(n - 1, begin, end, tmp, hanot);
        Print(begin, end);
        hanot.Move(begin, end);
        hanot.PrintStatus();
        // 借助begin柱子，将中介柱子上的n-1个盘子移动到end柱子上
        Hanot(n - 1, tmp, begin, end, hanot);
    }
}


int main() {
    cout << "Begin: " << MAXLENGTH << " plates on 'a'" << endl;
    cout << "Target: " << MAXLENGTH << " plates on 'c'" << endl;
    Status hanot;

    cout << "Initial status: " << endl;
    hanot.PrintStatus();

    Hanot(MAXLENGTH, 'a', 'b', 'c', hanot);
    return 0;
}
