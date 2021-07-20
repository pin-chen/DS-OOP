
#include "Porkball.h"

PorkBall::PorkBall(string name, float speed) {
	this -> name = name;
	this -> speed = speed;
}

bool PorkBall::canRide(Student* student) {
	// use isTraffic to check whether the student can ride the porkball.
	if (isTraffic(student) ){
		cout << student->getID() << " can ride porkball "<<this->name<<", the spped is "<<this->speed<<'\n';
		return true;
	}else{
		cout<<"error bad_cast"<<'\n';
		return false;
	}
	
}

bool PorkBall::isTraffic(Student* student) {
	// use dynamic casting to check whether the student is a Traffic student. 
	if( dynamic_cast<Traffic*>(student) ){
		return true; 
	}else{
		return false;
	}
}
