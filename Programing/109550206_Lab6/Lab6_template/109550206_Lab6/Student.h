
#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
	Student(string ID, int score, int money, float background);
	void printAllInfo();
	virtual void ShowSchool();
	string getID();
private:
	string ID;
	int score;
	int money;
	float background;
};

#endif
