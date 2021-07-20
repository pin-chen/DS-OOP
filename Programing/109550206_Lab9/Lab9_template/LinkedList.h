#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
using namespace std;

struct Node
{
	int value;
	Node* next;

	Node() : value(0), next(NULL) {};
	Node(int x) : value(x), next(NULL) {};
};

class LinkedList
{
private:
	Node* head;
public:
	LinkedList();
	~LinkedList();
	void Push_back(int x);
	void Push_front(int x);
	void Insert(int index, int x);
	void Delete(int index);
	void Reverse();
	void Print();
	void Clear();
};

#endif