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
    cout << "~~~~           1. display               ~~~~" << endl;
    cout << "~~~~           2. change                ~~~~" << endl;
    cout << "~~~~           3. insert                ~~~~" << endl;
    cout << "~~~~           4. delete                ~~~~" << endl;
    cout << "~~~~           5. search                ~~~~" << endl;
    cout << "~~~~           6. string length         ~~~~" << endl;
    cout << "~~~~           0. exit                  ~~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    cout << "Please enter your choice: " ;
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
    cin.get();
    cin.get(newStr, 100);
    if(p > q || q >= ss->length || p < 0) {
        cout << "position input error" << endl;
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
    cin.get();
    char newStr[100];
    cin.getline(newStr, 100);
    if(pos > ss->length) {
        pos = ss->length;
    }
    if(pos < 0) {
        cout << "position input error" << endl;
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
        cout << "insert successfully" << endl;
    }
}

void Delete(Sstring * ss) {
    cout << "please enter the pos you want to begin and last: " ;
    int p, q;
    cin >> p >> q;
    if(p > q || q >= ss->length || p < 0) {
        cout << "position input error" << endl;
    }
    else {  // backforward
        for(int i = q + 1; i < ss->length; i++) {
            ss->ch[i-q-1+p] = ss->ch[i];
        }
        ss->length = ss->length - q - 1 + p;
        cout << "delete successfully!" << endl;
    }
}

void Search(Sstring * ss) {

}

void Length(Sstring * ss) {
    cout << "the length of the string is " << ss->length << endl;
}

int main() {
    cout << "build string: " << endl;
    Sstring* ss = Build();
    int choice = 0;
    showMenu();
    cin >> choice;
    while(choice != 0) {
        switch(choice) {
            case 1:
                Display(ss);
                break;
            case 2:
                Change(ss);
                break;
            case 3:
                Insert(ss);
                break;
            case 4:
                Delete(ss);
                break;
            case 5:
                Search(ss);
                break;
            case 6:
                Length(ss);
                break;        
        }
        // cin.get();  // pause
        system("sleep 3");
        system("clear");
        showMenu();
        cin >> choice;
    }
    delete ss;
    return 0;
}