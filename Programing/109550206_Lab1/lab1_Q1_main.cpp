#include <iostream>
#include "lab1_Q1.h"
//#include "lab1_Q1.cpp"

using namespace std;

int main()
{
	int n;
	cin >> n;

	while (n--)
	{
		char command;
		cin >> command;
		
		QUADRATIC q1, q2;
		switch (command) {
			
			case '+':		
				q1.input();
				//q1.show();
				q2.input();
				//q2.show();
				q1.add(q2);
				q1.print();
				break;
				
			case 'p':		
				q1.input();
				//q1.show();
				q1.print();
				break;
				
			case 'd':		
				q1.input();
				//q1.show();
				q1.discriminant();
				break;

			default:
				cout << "wrong input!";
				break;
		}
	}

	system("pause");
}
