
#include "Traffic.h"

Traffic::Traffic(string ID, int score, int money, float background) : Student(ID,score, money, background){}

void Traffic::ShowSchool(){
	cout << "Student " << getID() << " is Traffic student."<<'\n'<<'\n';
}
