
#include "Student.h"

Student::Student(string ID, int score, int money, float background) {
	this -> ID = ID;
	this -> score = score;
	this -> money = money;
	this -> background = background;
}

void Student::ShowSchool(){}

void Student::printAllInfo(){
	cout << "ID: " << ID << '\n';
	cout << "Score: " << score << '\n';
	cout << "Money: " << money << '\n';
	cout << "Background: " << background << '\n';

}

string Student::getID(){
	return ID;
}


