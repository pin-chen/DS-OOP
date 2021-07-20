
#include "TaiwanNumber1.h"

TaiwanNumber1::TaiwanNumber1(string ID, int score, int money, float background) : Student(ID,score, money, background){}

void TaiwanNumber1::ShowSchool(){
	cout << "Student" << getID() << " is TaiwanNumber1 student."<<'\n'<<'\n';
}