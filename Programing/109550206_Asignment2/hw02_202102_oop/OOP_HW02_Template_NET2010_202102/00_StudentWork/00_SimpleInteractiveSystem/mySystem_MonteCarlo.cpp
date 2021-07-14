//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
//
#include "mySystem_MonteCarlo.h"
#include "myBasicTools.h"
#include <iostream>
#include <cmath>

using namespace std;

#define MAX_SAMPLES 1000000

MONTE_CARLO_SYSTEM::MONTE_CARLO_SYSTEM( )
{
    //BEGIN DO NOT CHANGE ANYTHING HERE
    mFunctionType = FUNCTION_EXPONENTIAL_CONSINE;
    cout.precision(8);
    //
    mMinX = 0.0;
    mMaxX = 6;
    mMinY = -4.0;
    mMaxY = 4.0;
    mMinNumSamples = 100;
    mMaxNumSamples = MAX_SAMPLES;
    mNumSamples = 5000;
    computeSamples( );
    computeArea( );
    //END DO NOT CHANGE ANYTHING HERE
}

/*
Show the message to the user.
*/
void MONTE_CARLO_SYSTEM::askForInput( )
{
    cout << "MONTE_CARLO_SYSTEM::askForInput( )" << endl;
	cout << "Use keys to control......" << endl;
    cout << "1: FUNCTION_EXPONENTIAL_COSINE" << endl;
    cout << "2: FUNCTION_COSINE" << endl;
    cout << "3: FUNCTION_SINE_COSINE" << endl;
    cout << "4: FUNCTION_HYPERBOLIC_TANGENT" << endl;
    cout << "m: minimum number of sample points" << endl;
    cout << ",: decrease the number of sample points" << endl;
    cout << ".: increase the number of sample points" << endl;
    cout << "/: maximum number of sample points" << endl;
}

/*
Handle the key events.
*/
bool MONTE_CARLO_SYSTEM::handleKeyPressedEvent( int key )
{
    bool flgHandled = false;
	switch(key){
	case '1':
		mFunctionType = FUNCTION_EXPONENTIAL_CONSINE;
		flgHandled = true;
		reset();
		break;
	case '2':
		mFunctionType = FUNCTION_COSINE ;
		flgHandled = true;
		reset();
		break;
	case '3':
		mFunctionType = FUNCTION_SINE_COSINE;
		flgHandled = true;
		reset();
		break;
	case '4':
		mFunctionType = FUNCTION_EXPONENTIAL;
		flgHandled = true;
		break;
	case 'm':
		this -> mNumSamples = mMinNumSamples;
		flgHandled = true;
		reset();
		break;
	case ',':
		this -> mNumSamples -= 1000;
		if(this -> mNumSamples <= 0) {
			this -> mNumSamples = 0;
		}else{
			flgHandled = true;
			reset();
		}
		break;
	case '.':
		this -> mNumSamples += 1000;
		if(this -> mNumSamples >= mMaxNumSamples) this -> mNumSamples = mMaxNumSamples;
		flgHandled = true;
		reset();
		break;
	case '/':
		this -> mNumSamples = mMaxNumSamples;
		flgHandled = true;
		reset();
		break;
	default:
		break;
	}
    return flgHandled;
}

/*
Reset the system state.
Steps:
compute the samples
compute the area
*/
void MONTE_CARLO_SYSTEM::reset( )
{
    srand(0);
    computeSamples( );
    computeArea( );
}

/*
Return the range [mMinX, mMaxX] of x to [minX, maxX].

    minX = mMinX;
    maxX = mMaxX;

*/
void MONTE_CARLO_SYSTEM::getRangeOfX( double &minX, double &maxX ) const
{
	minX = this -> mMinX;
	maxX = this -> mMaxX;
}

/*
Uniformly generate all the random sample points
inside [mMinX, mMaxX] x [mMinY, mMaxY].

The number of sample points is mNumSamples.
*/
void MONTE_CARLO_SYSTEM::computeSamples( )
{
	mX.clear();
	mY.clear();
	mX.resize(this -> mNumSamples);
	mY.resize(this -> mNumSamples);
	for(int i = 0; i < this -> mNumSamples; ++i)
	{
		mX[i] = getRandDouble(mMinX, mMaxX);
		mY[i] = getRandDouble(mMinY, mMaxY);
	}
}

/*
Compute the area based on the Monte Carlo Simulation.
Steps:
1. compute the number of samples inside the area
2. compute the ratio which is equal to

number of samples inside the area 
divided 
by total number of samples

3. Based on the ratio, compute the area

Return the area value
*/
double MONTE_CARLO_SYSTEM::computeArea( ) const
{
    double area = 0.0;
	int num = 0;
	for(int i = 0; i < this -> mNumSamples; ++i)
	{
		if(this -> isInsideArea(mX[i], mY[i]) ) num++;
	}
	if(num > 0) area = (double) num / this -> mNumSamples;
	area *= (this -> mMaxX - this -> mMinX) * (this -> mMaxY - this -> mMinY);
    cout << "Area:" << area << endl;
    return area;
}

/*
Return the number of sample points.
Return mNumSamples.
*/
int MONTE_CARLO_SYSTEM::getNumSamples( ) const
{
    //Return the number of sample points
    return this -> mNumSamples;
}

/*
 x = mX[ sampleIndex ];
 y = mY[ sampleIndex ];
*/
void MONTE_CARLO_SYSTEM::getSample(int sampleIndex, double &x, double &y ) const
{
	x = this -> mX[sampleIndex];
	y = this -> mY[sampleIndex];
}

/*
Based on the function type mFunctionType,
compute the function value for a given value x.
Return the function value.
*/
double MONTE_CARLO_SYSTEM::getValue(double x) const
{
    double y;
    //y = rand( )/(float)RAND_MAX;

    switch( mFunctionType ) {
    case FUNCTION_EXPONENTIAL_CONSINE:
		y = -4 * exp(-x / 2.0) * cos(x) * sin(x);
        break;
    case FUNCTION_COSINE:
		y = - cos(x) * sin(6 * x) + x / (1 + x * x);
        break;
    case FUNCTION_SINE_COSINE:
		y = -3 * cos(x * x) + sin(3 * x) / ( fabs(x - 2) + 0.01);
        break;
    case FUNCTION_EXPONENTIAL:
		y = ( exp(x) - exp(-x) ) / ( exp(x) + exp(-x) );
        break;
    }
    return y;
}

/*
Given a point (x,y).
Check if the point lies inside the area.
Return true if it lies inside the area.
Return false otherwise.

The area is defined as the region bounded by
the x-axis and the curve of the function f(x).

Assume that (x,y) lies inside area, then
one of the following conditions must be satisfied.

- If f(x) >= 0 and y >=0, then y <= f(x).
- If f(x) <= 0 and y <=0, then y >= f(x).

Otherwise, (x,y) does not lay inside the area.
*/
bool MONTE_CARLO_SYSTEM::isInsideArea( double x, double y ) const
{
    double realY = getValue( x );
	if( realY >= 0 && y >= 0 && y <= realY){
		return true;
	}else if( realY <= 0 && y <= 0 && y>= realY){
		return true;
	}
	return false;
	//return realY >= 0 && y >= 0 && y <= realY ? true : realY <= 0 && y <= 0 && y>= realY;
}