//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#include "mySystem_CubicFunction.h"
#include <iostream>

using namespace std;

CUBIC_FUNCTION::CUBIC_FUNCTION( )
{
	x0 = -100.0;
	x1 = 100.0;
	mNumSamples = 1000;
    
    a = 1.0;
    b = -0.5;
	c = d = 0.5;
}

void CUBIC_FUNCTION::increase(double dv)
{
    b += dv;
}

void CUBIC_FUNCTION::decrease(double dv)
{
	b -= dv;
}


void CUBIC_FUNCTION::askForInput( )
{
	//
	//ax^3 + bx^2 + cx + d
	//Show the system name
	//Ask to input a, b, c, d
	//Ask to input the range of x in [-100, 100]
	//Ask to input the number of sample points
	//
	cout << "CUBIC_FUNCTION" << endl;
	
	cout << "Input the coeffients: ax^3 + bx^2 + cx + d" << endl;
	a = Input();
	b = Input();
	c = Input();
	d = Input();
	while ( true ) {
		cout << "Input the range of x in [-100, 100]. i.e., minimum value and maximum value of x." << endl;
		x0 = Input();
		x1 = Input();
		if ( x0 >= -100 && a <= 100 && x1 >= x0 && x1 <= 100 ) break;
	}
	while ( true ) {
		cout << "Input the number of sample points in [2, 100]" << endl;
		mNumSamples = Input();
		if ( mNumSamples >= 2 && mNumSamples <= 100 ) break;
	}
}

void CUBIC_FUNCTION::getRangeOfX( double &x0, double &x1 ) const
{
	//Return the range of x in x0 and x1.
	x0 = this -> x0;
	x1 = this -> x1;
}

int CUBIC_FUNCTION::getNumOfSamples( ) const
{
	//Return the number of samples
	return mNumSamples;
}

double CUBIC_FUNCTION::getValue( double x ) const
{
	//Compute ax^3 + bx^2 + cx + d
	return ( ( a * x + b ) * x + c ) * x + d;
}

//Check input is number or not
double CUBIC_FUNCTION::Input(){
	while(1){
		string s;
		cin >> s;
		try{
			double num = stod(s);
			return num;
			break;
		}catch(std::exception& e){
			cout << "Wrong input!!!" <<'\n'; 
		}
	}
}
// CODE: 2021/03/01. Do not delete this line.