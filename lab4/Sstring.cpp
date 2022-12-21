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
    Sstring * new_String = new Sstring;
    new_String->length = 0; 
    cout << "new string has been built" << endl;
    return new_String;
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
    // cin.get();
    char newStr[100];
    cin.get();  // to take ENTER key
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

// KMP next function with improve
int * get_next(char * smod, int len) {
    int i = 0, j = -1;
    int * next = new int[len];
    next[i] = -1;
    while(i < len) {
        if(j==-1 || smod[i]==smod[j]) {
            ++i;
            ++j;
            if(smod[i] != smod[j]) next[i] = j;
            else next[i] = next[j];
        }
        else j = next[j];
    }
    return next;
}

// KMP Algorithm
// return the index of substring (begin with pos)
// return the -1 if not found
int Search(Sstring * ss,int pos = 0) {
    cout << "Please enter the string you want to search: " ;
    char subString[255];
    cin.get();
    cin.getline(subString, 255);
    int subLen = 0;
    while(subString[subLen] != '\0') {
        subLen++;
    }
    int j = 0;  // substring begin with index 0 
    int *next = get_next(subString, subLen);
    //  cmpare while neither end
    while(pos < ss->length && j < subLen) {
        if(j==-1 || ss->ch[pos]==subString[j]) {
            ++pos;
            ++j;
        }
        else j = next[j];
    }
    int index = -1;
    if(j == subLen) {
        index = pos - subLen;
        cout << "the index of subString is: " << index << endl;
        delete[] next;
        return index;
    }
    cout << "not found!" << endl;
    delete[] next;
    return index;
}

void Length(Sstring * ss) {
    cout << "the length of the string is " << ss->length << endl;
}

int main() {
    cout << "build string: " << endl;
    Sstring* Sstr = Build();
    int choice = 0;
    showMenu();
    cin >> choice;
    while(choice != 0) {
        switch(choice) {
            case 1:
                Display(Sstr);
                break;
            case 2:
                Change(Sstr);
                break;
            case 3:
                Insert(Sstr);
                break;
            case 4:
                Delete(Sstr);
                break;
            case 5:
                Search(Sstr);
                break;
            case 6:
                Length(Sstr);
                break;        
        }
        system("sleep 3");
        system("clear");
        showMenu();
        cin >> choice;
    }
    delete Sstr;
    return 0;
}