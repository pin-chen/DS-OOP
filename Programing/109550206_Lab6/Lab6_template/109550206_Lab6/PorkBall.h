//#pragma once
#ifndef PORKBALL_H
#define PORKBALL_H
#include "Traffic.h"

class PorkBall {
public:
	PorkBall(string name, float speed);
	bool canRide(Student* student);
private:
	string name;
	float speed;
	bool isTraffic(Student* student);
};

#endif
