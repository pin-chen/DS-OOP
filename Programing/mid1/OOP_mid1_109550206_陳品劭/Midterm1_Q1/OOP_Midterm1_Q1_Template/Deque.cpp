#include "Deque.h"
#include <iostream>

using namespace std;

Deque::Deque(int _capacity) {
	// TODO: Create a dynamic array to implement a Deque 
	this->capacity = _capacity;
	currentSize = 0;
	deque = new int[capacity];
}

Deque::~Deque() {
	// TODO: delete Deque
	delete[] deque;
}

void Deque::PushFront(int element) {
	// TODO: push the element to the front of the Deque
	if (IsFull()) 
		DoubleCapacity();

	for (int i = currentSize - 1; i >= 0; i--)
	{
		deque[i + 1] = deque[i];
	}
	
	deque[0] = element;
	currentSize++;
}

void Deque::PushBack(int element) {
	// TODO: push the element to the back of the Deque
	if (IsFull()) 
		DoubleCapacity();

	deque[currentSize] = element;
	currentSize++;
}

void Deque::PopFront() {
	// TODO: pop the front element of the Deque
	if (IsEmpty())
		return;
	
	for (int i = 0; i < currentSize - 1; i++)
	{
		deque[i] = deque[i + 1];
	}

	currentSize--;
}

void Deque::PopBack() {
	// TODO: pop the back element of the Deque
	if (IsEmpty()) 
		return;
	
	deque[currentSize - 1] = 0;
	currentSize--;
}

int  Deque::GetFront() {
	// TODO: get the value of front element in the Deque 
	if (IsEmpty())
		return 0;

	return deque[0];
}

int  Deque::GetBack() {
	// TODO: get the value of back element in the Deque
	if (IsEmpty())
		return 0;

	return deque[currentSize - 1];
}

void Deque::Reverse() {
	// TODO: reverse the Deque
	if (IsEmpty())
		return;

	for (int i = 0; i < currentSize / 2; i++) 
	{
		int temp = deque[currentSize - i - 1];
		deque[currentSize - i - 1] = deque[i];
		deque[i] = temp;
	}
}

void Deque::DoubleCapacity() {
	// TODO: double the capacity of the Deque
	capacity *= 2;
	int* new_deque = new int[capacity];
	for (int i = 0; i < currentSize; i++) {
		new_deque[i] = deque[i];
	}
	delete deque;
	deque = new_deque;
}

void Deque::Print() {
	cout << "Element: ";
	for (int i = 0; i < currentSize; i++)
	{
		cout << deque[i] << " ";
	}
	cout << "\n";
}

bool Deque::IsEmpty() {
	return currentSize == 0;
}

bool Deque::IsFull() {
	return currentSize == capacity;
}

int  Deque::GetCapacity() {
	return capacity;
}
