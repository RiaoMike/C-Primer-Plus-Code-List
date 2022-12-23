#include<iostream>
using namespace std;

// 树的节点结构，包含数据域，孩子指针和兄弟指针
typedef struct node {
    int data;
    node* fch, * nsib;
}Node, * Tree;

// 给出孩子兄弟方式构造的树，计算叶子节点个数
int LeafNum(const Tree& tree) {
    if (tree == NULL) {
        return 0;   // 如果是空节点，直接返回0
    }
    else if (tree->fch == NULL) {   // 如果没有孩子，则自身为一个叶子
        int sib = LeafNum(tree->nsib);  // 递归计算右边森林的叶子个数
        return sib + 1;
    }
    else {
        int ch = LeafNum(tree->fch);    // 如果有孩子，则不是叶子，计算子树的叶子数
        int sib = LeafNum(tree->nsib);  // 右边森林的叶子个数
        return ch + sib;
    }
}

// 用孩子兄弟法构建森林
void create_Tree(Tree& tree) {
    char dd; // 节点的数据，输入‘#’表示空节点
    cin >> dd;
    if (dd != '#') {
        tree = new Node;    // 申请节点
        tree->data = dd;
        create_Tree(tree->fch); // 递归构造孩子子树和兄弟子树
        create_Tree(tree->nsib);
    }
    else tree = NULL;   // 如果为‘#’，表示没有孩子或兄弟
}

int main() {
    Tree tree;
    cout << "请用孩子兄弟法输入森林：" << endl;
    create_Tree(tree);
    cout << "森林的叶子节点个数为：";
    cout << LeafNum(tree) << endl;
    // 这里就懒得释放内存了
 
    return 0;
}
