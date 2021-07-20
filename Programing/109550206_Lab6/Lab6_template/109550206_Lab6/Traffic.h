
#ifndef TRAFFIC_H
#define TRAFFIC_H
#include "Student.h"

class Traffic : public Student {
public:
	Traffic(string ID, int score, int money, float background);
	void ShowSchool();
};

#endif
