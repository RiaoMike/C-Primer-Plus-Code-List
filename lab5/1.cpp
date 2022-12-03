#include<iostream>
using namespace std;

typedef int ElemType;

typedef struct node {
    ElemType data;
    node *fch, *nsib;
}Node, *Tree;

int LeafNum(const Tree & tree) {
    if(tree == NULL) {
        return 0;
    }
    else if(tree->fch == NULL) {
        int sib = LeafNum(tree->nsib);
        return sib + 1;
    }
    else {
        int ch = LeafNum(tree->fch);
        int sib = LeafNum(tree->nsib);
        return ch + sib;
    }
}

class Treecl{
    Tree root = NULL;
public:
    Treecl(ElemType m = 0);
    const Tree & Getroot();
    void Addch(ElemType m);
    void Addsib(ElemType m);
    ~Treecl();
};

Treecl::Treecl(ElemType m) {
    root = new Node;
    root->data = m;
    root->fch = NULL;
    root->nsib = NULL;
}

void Treecl::Addsib(ElemType m) {
    root->nsib = new Node;
    Tree tmp = root->nsib;
    tmp->data = m;
    tmp->fch = NULL;
    tmp->nsib = NULL;
}

void Treecl::Addch(ElemType m) {
    Tree left = root;
    while(left->fch != NULL) {
        left = left->fch;
    } 
    left->fch = new Node;
    Tree tmp = left->fch;
    tmp->data = m;
    tmp->fch = NULL;
    tmp->nsib = NULL;
}

const Tree & Treecl::Getroot() {
    return root;
}

Treecl::~Treecl() {
}

int main() {
    Treecl tt(35);
    tt.Addch(12);
    tt.Addch(34);

    int num = LeafNum(tt.Getroot());
    cout << num << endl;

    return 0;
}