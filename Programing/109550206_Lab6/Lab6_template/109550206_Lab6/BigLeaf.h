
#ifndef BIGLEAF_H
#define BIGLEAF_H
#include "Student.h"

class BigLeaf : public Student {
public:
	BigLeaf(string ID, int score, int money, float background);
	void ShowSchool();
};

#endif
