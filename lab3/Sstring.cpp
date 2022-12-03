#include<iostream>
#define MAXLEN 255
using namespace std;

struct Sstring{
    char ch[MAXLEN];
    int length;
};

void showMenu() {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "               string realise               " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~~           1. build string          ~~~~" << endl;
    cout << "~~~~           2. display               ~~~~" << endl;
    cout << "~~~~           3. change                ~~~~" << endl;
    cout << "~~~~           4. insert                ~~~~" << endl;
    cout << "~~~~           5. delete                ~~~~" << endl;
    cout << "~~~~           6. search                ~~~~" << endl;
    cout << "~~~~           7. string length         ~~~~" << endl;
    cout << "~~~~           0. exit                  ~~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
}

Sstring * Build() {
    Sstring * ss = new Sstring;
    ss->length = 0; 
    cout << "new string has been built" << endl;
    return ss;
}

void Display(Sstring * ss) {
    if(ss->length == 0) {
        cout << "string is empty" << endl;
    }
    else {
        cout << "string is: " ;
        for(int i = 0; i < ss->length; i++) {
            cout << ss->ch[i] ;
        }
    }
    cout << endl;
}

// p and q are index, which means begin with zero
void Change(Sstring * ss) {
    cout << "please enter the pos you want to begin and last: " ;
    int p, q;
    cin >> p >> q;
    cout << "please enter the new string: " ;
    char newStr[100];
    cin.getline(newStr, 100);
    if(p > q || p >= ss->length || p < 0) {
        cout << "error input" << endl;
    }
    else {
        int strlen = 0;
        while(newStr[strlen] != '\0') {
            strlen++;
        }
        if(q < p + strlen) {    // houyi
            int tmp = ss->length - 1; // backforward
            while(tmp > q) {
                ss->ch[tmp + strlen + p - q -1] = ss->ch[tmp];
                tmp--;
            }
        }
        else {  // qianyi
            int tmp = q + 1;
            while(tmp < ss->length) {
                ss->ch[tmp + strlen + p - q -1] = ss->ch[tmp];
                tmp++;
            }
        }
        //  insert
        for(int i = 0; i < strlen; i++) {
            ss->ch[p + i] = newStr[i];
        }
        ss->length += strlen + p - q -1;
        cout << "change successfully" << endl;
    }
}

void Insert(Sstring * ss) {
    cout << "please enter position you want to insert: " ;
    int pos;
    cin >> pos;
    cout << "please enter the string you want to insert: " ;
    char newStr[100];
    cin.get();
    cin.getline(newStr, 50);
    if(pos > ss->length) {
        pos = ss->length;
    }
    else {
        int strlen = 0;
        while(newStr[strlen] != '\0') {
            strlen++;
        }
        // backforward first, and then insert
        for(int i = ss->length - 1; i >= pos; i--) {
            ss->ch[i + strlen] = ss->ch[i];
        }
        for(int i = 0; i < strlen; i++) {
            ss->ch[i + pos] = newStr[i];
        }
        ss->length += strlen;
    }
    cout << "insert successfully" << endl;
}
void Strlen(Sstring * ss) {
    cout << "the length of the string is " << ss->length << endl;
}

int main() {
    showMenu();
    Sstring * ss = Build();
    Strlen(ss);
    Insert(ss);
    Strlen(ss);
    Display(ss);
    Change(ss);
    delete [] ss;
    return 0;
}