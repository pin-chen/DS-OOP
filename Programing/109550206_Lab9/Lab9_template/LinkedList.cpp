#include"LinkedList.h"

LinkedList::LinkedList()
{
	head = NULL;
}

LinkedList::~LinkedList()
{
	Clear();
}


void LinkedList::Push_back(int x)
{
	//TODO: add a new node to the back of the list with value x
	Node* new_node = new Node(x);
	if(head == NULL){
		head = new_node;
	}else{
		Node* now = head;
		while(now -> next != NULL){
			now = now -> next;
		}
		now -> next = new_node;
	}
}

void LinkedList::Push_front(int x)
{
	//TODO: add a new node to the front of the list with value x
	Node* new_node = new Node(x);
	if(head == NULL){
		head = new_node;
	}else{
		new_node -> next = head;
		head = new_node;
	}
}

void LinkedList::Insert(int index, int x)
{
	//TODO: add a new node at position "index" of the list with value x
	Node* new_node = new Node(x);
	if(index == 0){
		new_node -> next = head;
		head = new_node;
		return;
	}
	Node* now = head;
	while(--index){
		now = now -> next;
	}
	new_node -> next = now -> next;
	now -> next = new_node;
}

void LinkedList::Delete(int index)
{
	//TODO: delete the node at position "index"
	Node* now = head;
	if(index == 0){
		if(head == NULL) return;
		head = now -> next;
		delete now;
		return;
	}
	while(--index){
		now = now -> next;
	}
	Node* next_next = now -> next -> next;
	delete now -> next;
	now -> next = next_next;
}

void LinkedList::Reverse()
{
	//TODO: reverse all elements in the list
	if(head == NULL) return;
	Node* now = head;
	Node* temp = now -> next;
	this -> Push_front(now -> value);
	head -> next=NULL;
	while(temp != NULL){
		delete now;
		now = temp;
		temp = now -> next;
		this -> Push_front(now -> value);
	}
	delete now;
}

void LinkedList::Print()
{
	//TODO: print out all elements in the list
	if(head == NULL){
		cout << "This list is empty." << '\n';
	}else{
		cout << "List: ";
		Node* now = head;
		while(now -> next != NULL){
			cout << now -> value << " ";
			now = now -> next;
		}
		cout << now -> value << '\n';
	}
}

void LinkedList::Clear() 
{
	//TODO: delete all elements in the list
	if(head == NULL) return;
	Node* now = head;
	Node* temp = now -> next;
	while(temp != NULL){
		delete now;
		now = temp;
		temp = now -> next;
	}
	delete now;
	head = NULL;
}