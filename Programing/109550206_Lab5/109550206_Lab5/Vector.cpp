#include "Vector.h"

//TODO: constructor
Vector::Vector() {
	this -> x = 0.0;
	this -> y = 0.0;
	this -> z = 0.0;
}
Vector::Vector(float _x, float _y, float _z) {
	this -> x = _x;
	this -> y = _y;
	this -> z = _z;
}
 
Vector Vector::operator+(Vector v)
{
	//TODO: Overload the plus operator +.
	//Then we can use more intuitively way to add our vector (like v1 + v2).
	//Return the result of v1 + v2
	Vector ans(this -> x + v.x, this -> y + v.y, this -> z + v.z);
	return ans;
}

Vector Vector::operator-(Vector v)
{
	//TODO: Overload the subtract operator -.
	//Then we can use more intuitively way to subtract out vector (like v1 - v2).
	//Return the result of v1 - v2
	Vector ans(this -> x - v.x, this -> y - v.y, this -> z - v.z);
	return ans;
}


float Vector::operator*(Vector v)
{
	//TODO: Overload the operator * as dot product.
	//Return the dot product result of two vector
	float ans = this -> x * v.x + this -> y * v.y + this -> z * v.z;
	return ans;
}

Vector Vector::operator/(Vector v)
{
	//TODO: Overload the operator / as cross product.
	//Return the cross product result of v1 / v2
	float x, y, z;
	x = this -> y * v.z - this -> z * v.y;
	y = this -> z * v.x - this -> x * v.z;
	z = this -> x * v.y - this -> y * v.x;
	Vector ans(x, y, z);
	return ans;
}

Vector Vector::operator-()
{
	//TODO: Overload the negate operator -.
	//Then we can use more intuitively way to negate a vector -v1.
	//Return the result of -v1
	Vector ans(-x, -y, -z);
	return ans;
}

bool Vector::operator>(Vector v) {
	//TODO: Overload the ">" operator.
	//Then we can use more intuitively way to
	//compare the length from the original point(0,0,0) of two vectors (v1 > v2).
	//Return true if the length of v1 is greater than that of v2, return false otherwise. 
	float this_length, v_length;
	this_length = x*x + y*y + z*z;
	v_length = v.x*v.x + v.y*v.y + v.z*v.z;
	return this_length > v_length;
}


ifstream& operator>>(ifstream& in, Vector& v)
{
	//TODO: Overload the >> operator.
	//Read the input.txt file and store vector in v
	in >> v.x >> v.y >> v.z;
	return in;
}

ostream& operator<<(ostream& out, const Vector& v)
{
	//TODO: Overload the << operator.
	//Output the vector v
	out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}
