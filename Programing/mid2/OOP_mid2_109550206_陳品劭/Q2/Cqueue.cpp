#include "Cqueue.h"
#include<iostream>
using namespace std;

Cqueue::Cqueue(int Capacity)
{
	// TODO: Constructor
	capacity = Capacity;
	queue = new int[capacity];
	start = 0;
	end = -1;
}

void Cqueue::Enqueue(int x)
{
	if (IsFull()) {
		cout << "Queue is full, cannot add more elements." << endl;
	}
	else {
		//TODO: Add the element to the back of the queue
		if(end + 1 > capacity){
			end = 0;
		}else{
			end++;
		}
		queue[end] = x;
	}
}

void Cqueue::Dequeue()
{
	if (IsEmpty()) {
		cout << "Queue is empty" << endl;
	}
	else {
		//TODO: Remove the first element of the queue
		if(start == end) {
			start = 0;
			end = -1;
			return;
		}
		queue[start] = 0;
		if(start + 1 > capacity){
			start = 0;
		}else{
			start++;
		}
		
	}
}

bool Cqueue::IsEmpty()
{
	//TODO: Determine if queue is empty
	if(start == 0 && end == -1) return true;
	return false;
}

bool Cqueue::IsFull()
{
	//TODO: Determine if queue is full
	if(start == 0 && end == -1) return false;
	int x = end + 1;
	if(x > capacity) x = 0;
	if(start == x) return true;
	return false;
}

void Cqueue::Print()
{
	cout << "The current content of queue is: ";
	
	//TODO: Print out the elements of queue from front to back
	if(IsEmpty())return;
	if(start < end){
		for(int i = start; i <= end; i++){
			cout << queue[i] << " ";  
		}
		cout << '\n';
	}else{
		for(int i = start; i < capacity; i++){
			cout << queue[i] << " ";
		}
		for(int i = 0; i <= end; i++){
			cout << queue[i] << " ";
		}
		cout << '\n';
	}
}

void Cqueue::Reverse(){
	//TODO: Reverse the queue
	for(int i = 0; i < GetSize() / 2; i++){
		int x = start + i;
		int y = end - i;
		if(x > capacity) x = 0;
		if(y < 0) y = capacity;
		int temp = queue[x];
		queue[x] = queue[y];
		queue[y] = queue[x];
	}
}

int Cqueue::GetSize(){
	//Return the size of queue
	if(start == 0 && end == -1) return 0;
	if(end > start) return end - start + 1;
	else return capacity - start + end + 1;
}

int Cqueue::GetStart() {
	//return start;
	return start;
}

int Cqueue::GetEnd() {
	//return end;
	return end;
}
