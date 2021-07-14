//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#include "mySystem_SineCosineFunction.h"
#include <iostream>
#include <cmath>

using namespace std;

namespace {
//minimum number of sample points
#define MIN_NUM_SAMPLES 2
//maximum number of sample points
#define MAX_NUM_SAMPLES 1000
//default number of sample points
#define DFT_NUM_SAMPLES 100  
};

SINECOSINE_FUNCTION::SINECOSINE_FUNCTION( )
{
	reset();
}

void SINECOSINE_FUNCTION::increaseA(double increasedAmount)
{
    a += increasedAmount;

}

    void SINECOSINE_FUNCTION::decreaseA(double decreasedAmount)
{
	a -= decreasedAmount;
}

    void SINECOSINE_FUNCTION::increaseB(double increasedAmount)
{
    b += increasedAmount;

}

void SINECOSINE_FUNCTION::decreaseB(double decreasedAmount)
{
	b -= decreasedAmount;
}

void SINECOSINE_FUNCTION::increaseSampleNum(int increasedAmount )
{
    if ( mNumSamples > MAX_NUM_SAMPLES ) mNumSamples = MAX_NUM_SAMPLES;
	else mNumSamples += increasedAmount;
}

void SINECOSINE_FUNCTION::decreaseSampleNum(int decreasedAmount)
{
	if ( mNumSamples < MIN_NUM_SAMPLES ) mNumSamples = MIN_NUM_SAMPLES;
	else mNumSamples -= decreasedAmount;
}

//
// reset
void SINECOSINE_FUNCTION::reset()
{
    x0 = -20.0;
	x1 = 20.0;
	mNumSamples = DFT_NUM_SAMPLES;
	a = b = 1;
}

//
//Show the system name
//Ask to input a, b
//Ask to input the range of x in [-10, 10]
//Ask to input the number of sample points
//
void SINECOSINE_FUNCTION::askForInput( )
{
	cout << "SINECOSINE_FUNCTION" << endl;
	cout << "Input the coeffients, a and b: a cos(b*x)" << endl;
	a = Input();
	b = Input();
	while ( true ) {
		cout << "Input the range of x in [-20, 20]. i.e., minimum value and maximum value of x." << endl;
		x0 = Input();
		x1 = Input();
		if ( x0 >= -20 && a <= 20 && x1 >= x0 && x1 <= 20 ) break;
	}
	while ( true ) {
		cout << "Input the number of sample points in [2, 1000]" << endl;
		mNumSamples = Input();
		if ( mNumSamples >= 2 && mNumSamples <= 1000 ) break;
	}
}
//
// Get the range of x
// by-reference
//(x0, x1) formal parameters
// x0: minimum x 
// x1: maximum x
//
void SINECOSINE_FUNCTION::getRangeOfX( double &x0, double &x1 ) const
{
	//Return the range of x in x0 and x1.
	x0 = this -> x0;
	x1 = this -> x1;
}

//
//Return the number of samples
//
int SINECOSINE_FUNCTION::getNumOfSamples( ) const
{
	return mNumSamples;
}

//
// Get the function value for x
//
double SINECOSINE_FUNCTION::getValue( double x ) const
{
	// a cos(b*x)
	return a * cos( b * x);
}

//
//Check input is number or not
//
double SINECOSINE_FUNCTION::Input(){
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

