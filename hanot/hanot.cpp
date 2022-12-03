#include<iostream>
#define MAXLENGTH 4
using namespace std;

static int step = 0;

// plate: 1, 2, 3...
// pillar: 'a', 'b', 'c'
typedef struct {
    int array[MAXLENGTH];
    int len;
}pip, *pillar;

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

    for(int i = 0; i < MAXLENGTH; i++) {
        a->array[i] = 0;
        b->array[i] = 0;
        c->array[i] = 0;
    }

    a->len = MAXLENGTH;
    b->len = c->len = 0;

    for(int i = 0; i < MAXLENGTH; i++) {
        a->array[i] = MAXLENGTH - i;
    }
}

// note that must switch(begin) first, then switch(end)
void Status::Move(char begin, char end) {
    int plate;
    switch (begin) {
        case 'a':
        // get the top plate from a pillar
            plate = a->array[a->len-1];
            a->array[a->len-1] = 0;
            a->len--;
            break;
        case 'b':
            plate = b->array[b->len-1];
            b->array[b->len-1] = 0;
            b->len--;
            break;
        case 'c':
            plate = c->array[c->len-1];
            c->array[c->len-1] = 0;
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

void Status::PrintStatus() {
    for(int i = MAXLENGTH-1; i >= 0; i--) {
        PrintRow(a->array[i], b->array[i], c->array[i]);
    }
    for(int i = 0; i < 6*MAXLENGTH+6; i++) {
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

void Status::PrintSingle(int x) {
    if(x == 0) {
        for(int i = 0; i < 2*MAXLENGTH+2; i++) {
            cout << " ";
        } 
    }
    else {
        for(int i = 0; i < MAXLENGTH-x; i++) cout << " ";
        cout << "/";
        for(int i = 0; i < 2*x; i++) cout << "-";
        cout << "\\";
        for(int i = 0; i < MAXLENGTH-x; i++) cout << " "; 
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

void Hanot(int n, char begin, char tmp, char end, Status & hanot) {
    if(n == 1) {
        Print(begin, end);
        hanot.Move(begin, end);
        hanot.PrintStatus();
    } 
    else {
        Hanot(n-1, begin, end, tmp, hanot);
        Print(begin, end);
        hanot.Move(begin, end);
        hanot.PrintStatus();
        Hanot(n-1, tmp, begin, end, hanot);
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