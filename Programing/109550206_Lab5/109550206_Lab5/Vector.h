#ifndef VECTOR_H
#define VECTOR_H 

#include <iostream>
#include <fstream>

using namespace std;

class Vector
{
private:
	float x;
	float y;
	float z;

public:
	//constructor
	Vector();
	Vector(float _x, float _y, float _z);

	//overload 
	Vector operator +(Vector v);
	Vector operator -(Vector v);
	float  operator *(Vector v); // dot product
	Vector operator /(Vector v); // cross product
	Vector operator -();		 // negate
	bool   operator >(Vector v);

	//input output overload
	friend ifstream& operator >> (ifstream& in, Vector& v);
	friend ostream& operator << (ostream& out, const Vector& v);
};

#endif