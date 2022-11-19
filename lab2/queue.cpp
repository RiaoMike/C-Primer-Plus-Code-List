#include<iostream>
using namespace std;

#define MAXSIZE 5
#define ERROR 0
#define OVERFLOW -2

typedef int Elem; 

typedef struct{
    Elem * base;
    int front;
    int rear;
}SqQueue;

void InitQueue(SqQueue & queue) {
    queue.base = new Elem[MAXSIZE];
    if(!queue.base) {
        exit(OVERFLOW);
    }
    queue.front = 0;
    queue.rear = 0;
}

void DestroyQueue(SqQueue & queue) {
    //  queue not exists
    if(!queue.base) {
        exit(ERROR);
    }
    delete [] queue.base;
}

void ClearQueue(SqQueue & queue) {
    if(!queue.base) {
        exit(ERROR);
    }
    queue.rear = queue.front;
}

void QueueEmpty(SqQueue queue) {
    if(!queue.base) {
        exit(ERROR);
    }
    if(queue.rear == queue.front) {
        cout << "queue is empty" << endl;
    }
    else {
        cout << "queue is not empty" << endl;
    }
}

int QueueLength(SqQueue queue) {
    if(!queue.base) {
        exit(ERROR);
    }
    int length = 0;
    while(queue.front != queue.rear) {
        length++;
        queue.front = (queue.front + 1) % MAXSIZE;
    }
    return length;
}

void GetHead(SqQueue queue) {
    if(queue.front == queue.rear) {
        cout << "queue is empty" << endl;
    }
    else {
        cout << "the head of queue is: " << queue.base[queue.front] << endl;
    }
}

void DeQueue(SqQueue & queue) {
    if(queue.front == queue.rear) {
        cout << "queue is empty, can not delete" << endl;
    }
    else {
        cout << "the head of queue: " << queue.base[queue.front]; 
        cout << " has now being deleted" << endl;
        queue.front = (queue.front + 1) % MAXSIZE;
    }
}

void EnQueue(SqQueue & queue, Elem elem) {
    if((queue.rear+1)%MAXSIZE == queue.front) {
        cout << "overflow" << endl;
    } 
    else {
        queue.base[queue.rear] = elem;
        queue.rear = (queue.rear + 1) % MAXSIZE;
		cout << "elem " << elem << " is now in the queue" << endl;
    }
}

void QueueTraverse(SqQueue queue) {
    if(!queue.base) {
        exit(ERROR);
    }
    if(queue.front == queue.rear) {
        cout << "queue is empty" << endl;
    }
    else {
        for(int i = 0; i < QueueLength(queue); i++) {
            int index = (queue.front + i) % MAXSIZE;
            cout << queue.base[index] << " ";
        }
		cout << endl;
    }
}

int main() {
    SqQueue q;

    InitQueue(q);
	QueueEmpty(q);
    EnQueue(q, -1);
    EnQueue(q, 2);
    EnQueue(q, 10);
    DeQueue(q);
    cout << "the length of queue is: " << QueueLength(q) << endl;
    EnQueue(q, -3);
    EnQueue(q, 12);
    EnQueue(q, 10);
	cout << "length: " << QueueLength(q) << endl;
    QueueTraverse(q);
	QueueEmpty(q);
    DestroyQueue(q);
}
