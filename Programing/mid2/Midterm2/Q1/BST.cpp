#include"BST.h"
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <map>

using namespace std;

Node* BST::Successor(Node* node) {
    //TODO: find the successor of the given node and return it
	Node* MIN = root;
	Node* now = root;
	queue<Node*> q;
	q.push(now);
	while(q.size() != 0){
		if(q.front() -> value < MIN -> value) MIN = q.front();
		if(q.front()->leftchild != NULL){
			//MIN = min(MIN, q.front()->leftchild->value);
			q.push(q.front()->leftchild);
		}
		if(q.front()->rightchild != NULL){
			//MIN = min(MIN, q.front()->rightchild->value);
			q.push(q.front()->rightchild);
		}
		q.pop();
	}
	return MIN;
}

Node* BST::Search(int value) {
    //TODO: search the node with value
    //if the node does't exist, return NULL
    //otherwise return the node
	Node* now = root;
	while(1){
		if(now==NULL) return now;
		if(value == now->value) return now;
		if(value < now->value) now = now->leftchild;
		else	now = now->rightchild;
	}
}

void BST::InsertNode(int value) {
    //TODO: insert a node with value to the BST
	Node* new_node = new Node;
	new_node -> value = value;
	//cout << "x";
	if(root == NULL){
		root = new_node;
		root->parent = NULL;
		root->leftchild = NULL;
		root->rightchild = NULL;
		return;
	}
	//cout << "x";
	Node* now = root;
	while(1){
		//cout << "x" << now->value<<'\n';
		if(now->value >= new_node -> value){
			if(now->leftchild == NULL){
				now->leftchild = new_node;
				new_node->parent = now;
				new_node->leftchild = NULL;
				new_node->rightchild = NULL;
				return;
			}else
				now = now->leftchild;
		}else if(now -> value < new_node -> value){
			if(now->rightchild == NULL){
				now->rightchild = new_node;
				new_node->parent = now;
				new_node->leftchild = NULL;
				new_node->rightchild = NULL;
				return;
			}else
				now = now->rightchild;
		}
	}
}

void BST::DeleteNode(int value) {
    Node* delete_node = Search(value);
    if (delete_node == NULL) {
        cout << value << " not found.\n";
        return;
    }

    //Case 1:
    if (delete_node->leftchild == NULL && delete_node->rightchild == NULL) {
        cout << "Delete case 1\n";
        //TODO: delete node with case 1
		if(delete_node->parent->leftchild == delete_node){
			delete_node->parent->leftchild = NULL;
		}else{
			delete_node->parent->rightchild = NULL;
		}
		delete delete_node;
		return;
    }
    //Case 2:
    if (delete_node->leftchild != NULL && delete_node->rightchild != NULL) {
        cout << "Delete case 2\n";
        //TODO: delete node with case 2
		Node* temp = Successor(delete_node);
		delete_node->value = temp->value;
		delete_node = temp;
		if (delete_node->leftchild == NULL && delete_node->rightchild == NULL) {
			//TODO: delete node with case 1
			if(delete_node->parent->leftchild == delete_node){
				delete_node->parent->leftchild = NULL;
			}else{
				delete_node->parent->rightchild = NULL;
			}
		}else if (delete_node->leftchild != NULL) {
			//TODO: delete node with case 3 (left)
			if(delete_node == root){
				root = delete_node->leftchild;
				root -> parent = NULL;
			}else if(delete_node->parent->leftchild == delete_node){
				delete_node->parent->leftchild = delete_node->leftchild;
			}else{
				delete_node->parent->rightchild = delete_node->leftchild;
			}
		}else{
			//TODO: delete node with case 3 (right)
			if(delete_node == root){
				root = delete_node->rightchild;
				root -> parent = NULL;
			}else if(delete_node->parent->leftchild == delete_node){
				delete_node->parent->leftchild = delete_node->rightchild;
			}else{
				delete_node->parent->rightchild = delete_node->rightchild;
			}
		}
		delete delete_node;
		return;
    }
    //Case 3:
    cout << "Delete case 3\n";
    if (delete_node->leftchild != NULL) {
        //TODO: delete node with case 3 (left)
		if(delete_node == root){
			root = delete_node->leftchild;
			root -> parent = NULL;
		}else if(delete_node->parent->leftchild == delete_node){
			delete_node->parent->leftchild = delete_node->leftchild;
			delete_node->leftchild->parent = delete_node->parent;
		}else{
			delete_node->parent->rightchild = delete_node->leftchild;
			delete_node->leftchild->parent = delete_node->parent;
		}
		delete delete_node;
		return;
    }
    else {
        //TODO: delete node with case 3 (right)
		if(delete_node == root){
			root = delete_node->rightchild;
			root -> parent = NULL;
		}else if(delete_node->parent->leftchild == delete_node){
			delete_node->parent->leftchild = delete_node->rightchild;
			delete_node->rightchild->parent = delete_node->parent;
		}else{
			delete_node->parent->rightchild = delete_node->rightchild;
			delete_node->rightchild->parent = delete_node->parent;
		}
		delete delete_node;
		return;
    }
}

int BST::ComputeHeight(Node* node) {
    //TODO: compute the height of the BST
	Node* now = root;
	int Max = 1;
	queue<Node*> q;
	map<Node*, int> m;
	m[root] = 1;
	q.push(now);
	while(q.size() != 0){
		if(Max < m[q.front()]) Max = m[q.front()];
		if(q.front()->leftchild != NULL){
			m[q.front()->leftchild] = m[q.front()] + 1;
			q.push(q.front()->leftchild);
		}
		if(q.front()->rightchild != NULL){
			m[q.front()->rightchild] = m[q.front()] + 1;
			q.push(q.front()->rightchild);
		}
		q.pop();
	}
	return Max;
}

void BST::InOrderPrint(Node* node) {
    //TODO: print the BST in in-order method
	if (root == NULL) return;
	stack<Node*> s;
	Node* now = root;
	while (now || !s.empty()) {
		if(now){
			s.push(now);
			now = now->leftchild;
		}else{
			Node *node = s.top();
			s.pop();
			cout << node->value << " ";
			now = node->rightchild;
		}
	}
	cout << '\n';
}

void BST::LevelOrderPrint() {
    //TODO: print the BST in level-order method
	//Node* MIN = root;
	Node* now = root;
	queue<Node*> q;
	q.push(now);
	while(q.size() != 0){
		cout << q.front()->value << " ";
		if(q.front()->leftchild != NULL){
			//MIN = min(MIN, q.front()->leftchild->value);
			q.push(q.front()->leftchild);
		}
		if(q.front()->rightchild != NULL){
			//MIN = min(MIN, q.front()->rightchild->value);
			q.push(q.front()->rightchild);
		}
		q.pop();
	}
	cout << '\n';
	//return MIN;
}

void BST::Destroy(Node* node) {
    //TODO: delete all node in the BST
    //TODO: print node value in post-order method before delete it
	if (root == NULL) return;
	stack<Node*> s;
	s.push(root);
	while (s.size() != 0) {
		Node* node = s.top();
		if (!node->leftchild && !node->rightchild) {
			s.pop();
			cout << node->value << " ";
		}

		if (node->rightchild) {
			s.push(node->rightchild);
			node->rightchild = NULL;
		}

		if (node->leftchild) {
			s.push(node->leftchild);
			node->leftchild = NULL;
		}
	}
	cout << '\n';
	Node* now = root;
	queue<Node*> q;
	q.push(now);
	while(q.size() != 0){
		if(q.front()->leftchild != NULL){
			q.push(q.front()->leftchild);
		}
		if(q.front()->rightchild != NULL){
			q.push(q.front()->rightchild);
		}
		delete q.front();
		q.pop();
	}
}