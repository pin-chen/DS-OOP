
#include "BigLeaf.h"

BigLeaf::BigLeaf(string ID, int score, int money, float background) : Student(ID,score, money, background){}

void BigLeaf::ShowSchool(){
	cout << "Student " << getID() << " is BigLeaf student." << '\n' << '\n';
}