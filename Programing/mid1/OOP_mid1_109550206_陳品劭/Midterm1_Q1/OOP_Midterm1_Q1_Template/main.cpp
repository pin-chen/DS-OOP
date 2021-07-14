#include "Deque.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {

	fstream file;

	file.open("test1_Q1.txt");
	if (!file) {
		cout << "Failed to open!\n";
		system("pause");
		exit(0);
	}

	int executeTime, dequeCapacity;
	file >> executeTime >> dequeCapacity;
	Deque myDeque(dequeCapacity);

	while (executeTime--)
	{
		char cmd;
		file >> cmd;
		int num;

		switch (cmd)
		{
		case '1':
			// TODO: implement function of PushFront
			file >> num;
			cout << "PushFront(" << num << "): \t";
			myDeque.PushFront(num);
			cout << "Capacity: " << myDeque.GetCapacity() << ", ";
			myDeque.Print();
			break;

		case '2':
			// TODO: implement function of PushBack
			file >> num;
			cout << "PushBack(" << num << "): \t";
			myDeque.PushBack(num);
			cout << "Capacity: " << myDeque.GetCapacity() << ", ";
			myDeque.Print();
			break;

		case '3':	
			// TODO: implement function of PopFront
			cout << "PopFront(): \t";
			if (myDeque.IsEmpty())
				cout << "Deque is empty." << '\n';
			else {
				myDeque.PopFront();
				myDeque.Print();
			}
			break;

		case '4':
			// TODO: implement function of PopBack
			cout << "PopBack(): \t";
			if (myDeque.IsEmpty())
				cout << "Deque is empty." << '\n';
			else {
				myDeque.PopBack();
				myDeque.Print();
			}
			break;

		case 'F':
			// TODO: implement function of GetFront
			cout << "GetFront(): \t";
			if (myDeque.IsEmpty())
				cout << "Deque is empty." << '\n';
			else
				cout << myDeque.GetFront() << '\n';
			break;

		case 'B':
			// TODO: implement function of GetBack
			cout << "GetBack(): \t";
			if (myDeque.IsEmpty())
				cout << "Deque is empty." << '\n';
			else
				cout << myDeque.GetBack() << '\n';
			break;

		case 'R':
			// TODO: implement function of Reverse
			cout << "Reverse(): \t";
			if (myDeque.IsEmpty())
				cout << "Deque is empty." << '\n';
			else {
				myDeque.Reverse();
				myDeque.Print();
			}
			break;

		default:
			break;
		}
	}

	system("pause");
	return 0;
}