#ifndef _LIST_H_
#define _LIST_H_

#include "Bullet.h"

typedef struct Node {
	Bullet bullet;
	struct Node* next;
}Node;

class List {
	Node* head;
	Node* tail;
public:
	List() {
		head = NULL;
		tail = NULL;
	}
	bool isEmpty();
	void insertNodeToTail(Node* node);
	Node* creatNewNode(Bullet bullet, Node* next);
	Node* removeNodeFromList(int shotNum);
	Node* getHead() {
		return head;
	}
	Node*  removeNodeFromList(Node* curr);
	void makeEmpty()
	{
		head = NULL;
		tail = NULL;
	}

};


#endif // !_LIST_H_
