//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_MonteCarlo.h"
#include "myBasicTools.h"
#include <iostream>

using namespace std;

#define MAX_SAMPLES 1000000

MONTE_CARLO_SYSTEM::MONTE_CARLO_SYSTEM( )
{
    //BEGIN DO NOT CHANGE ANYTHING HERE
    mFunctionType = FUNCTION_EXPONENTIAL_SINE;
    cout.precision(8);
    //
    mMinX = 0.0;
    mMaxX = 3.141592654*3.0;
    mMinY = -2.0;
    mMaxY = 2.0;
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
    cout << "1: FUNCTION_EXPONENTIAL_SINE" << endl;
    cout << "2: FUNCTION_SINE" << endl;
    cout << "3: FUNCTION_SINE_COSINE" << endl;
    cout << "4: FUNCTION_EXPONENTIAL" << endl;
   
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
    switch( key ) {
    case 'm':
        mNumSamples = 1000;
        flgHandled = true;
        break;
    case '/':
        mNumSamples = mMaxNumSamples;
        flgHandled = true;
        break;
    case ',':
        mNumSamples -= 1000;
        flgHandled = true;

        break;
    case '.':
        mNumSamples += 1000;
        flgHandled = true;

        break;
    case '1':
        mFunctionType = FUNCTION_EXPONENTIAL_SINE;
        flgHandled = true;
        break;
    case '2':
        mFunctionType = FUNCTION_SINE;
        flgHandled = true;
        break;
    case '3':
        mFunctionType = FUNCTION_SINE_COSINE;
        flgHandled = true;
        break;
    case '4':
        mFunctionType = FUNCTION_EXPONENTIAL;
        flgHandled = true;
        break;
    }
    if ( flgHandled ) {
        if ( mNumSamples < mMinNumSamples ) mMinNumSamples = 100;
        if ( mNumSamples > mMaxNumSamples ) mNumSamples = mMaxNumSamples;

        computeSamples( );
        computeArea( );
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
*/
void MONTE_CARLO_SYSTEM::getRangeOfX( double &minX, double &maxX ) const
{
    minX = mMinX;
    maxX = mMaxX;
}

/*
Uniformly generate all the random sample points
inside [mMinX, mMaxX] x [mMinY, mMaxY].

The number of sample points is mNumSamples.
*/
void MONTE_CARLO_SYSTEM::computeSamples( )
{
    //
    mX.clear( );
    mY.clear( );
    mX.resize( mNumSamples );
    mY.resize( mNumSamples );

    for ( int i = 0; i < mNumSamples; ++i ) {
        double x = getRandDouble( mMinX, mMaxX );
        double y = getRandDouble( mMinY, mMaxY  );
        mX[ i ] = x;
        mY[ i ] = y;
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
    int counter = 0;
    for ( int i = 0; i < mNumSamples; ++i ) {
        double x = mX[ i ];
        double y = mY[ i ];
        if ( isInsideArea( x, y ) ) {
            ++counter;
        }
    }

    double ratio = (counter/(double)mNumSamples);
    double area = ratio*(mMaxX - mMinX)*(mMaxY - mMinY);

    cout << "Area:" << area << endl;
    return area;

}

/*
Return the number of sample points.
*/
int MONTE_CARLO_SYSTEM::getNumSamples( ) const
{
    //Return the number of sample points
    return mNumSamples;
}
void MONTE_CARLO_SYSTEM::getSample(int sampleIndex, double &x, double &y ) const
{
    x = mX[ sampleIndex ];
    y = mY[ sampleIndex ];

}

/*
Based on the function type mFunctionType,
compute the function value for a given value x.
Return the function value.
*/
double MONTE_CARLO_SYSTEM::getValue(double x) const
{
    double y;
    switch( mFunctionType ) {
    case FUNCTION_EXPONENTIAL_SINE:
        y = 2.0*pow(2.718281828, -x/5.0)*sin(x);
        break;
    case FUNCTION_SINE:
        y = sin(x);
        break;
    case FUNCTION_SINE_COSINE:
        y = sin(x)*cos(x);
        break;
    case FUNCTION_EXPONENTIAL:
        y = 2.0*pow(2.718281828, -x/5.0);
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
    if ( realY > 0.0 && y > 0.0 && y <= realY ) return true;
    if ( realY < 0.0 && y < 0.0 && y >= realY ) return true;
    return false;
}