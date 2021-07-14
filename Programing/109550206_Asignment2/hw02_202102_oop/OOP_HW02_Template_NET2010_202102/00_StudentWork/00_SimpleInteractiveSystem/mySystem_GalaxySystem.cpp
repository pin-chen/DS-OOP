//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
//
#include "mySystem_GalaxySystem.h"
#include <iostream>

using namespace std;

namespace {
    double getRandDouble( double L, double U ) {
        return L + (U-L)*rand( )/(double) RAND_MAX;
    }
};

GALAXY_SYSTEM::GALAXY_SYSTEM( )
{
    mTimeStep = 0.0025; 
    mMaxV = 100.0;
    mNumOfObjs = 100;
    mNumLargeObjs = 2;
    mMinR = 0.5;            //minimum radius of objects
    mMaxR = 3.0;            //maximum radius of objects
    mSpaceSize = 300.0;
    mG = 5.0;               //gravitational constant
    generateObjects( );
}

/*
Generate randomly the positions,  
velocities and radii of the objects.

Also, if the objects are large, 
set their masses to be a large number.

The mass of an  object depends on the object's radius.

The position of an object is inside 
[-halfSpaceSize, halfSpaceSize]x[-halfSpaceSize, halfSpaceSize].

The velocity of an object is inside
[-100.0, 100]x[-100.0, 100].

Initialize the alive flag of each object.
the alive flag indicates whether the object is alive or not.
If the object is not alive, ignore it in all the calculations.

If there's only one large object,
set its position to the origin
and set its velocity to zero.

Use 
TAIL_PLANET tail(x,y);
mTails.push_back( tail ); // push a tail to mTails.
to initialize the tail of an object. 
It sets all the points of the tail to the same point, i.e., (x,y).

Each object has one tail.

*/
void GALAXY_SYSTEM::generateObjects( )
{
    mNumFrames = 0;

	mX.clear();
	mY.clear();
	mR.clear();
	mMass.clear();
	mVx.clear();
	mVy.clear();
	mFx.clear();
	mFy.clear();	
	mAlive.clear();
	mTails.clear();

	mX.resize( mNumOfObjs );
    mY.resize( mNumOfObjs );
    mR.resize( mNumOfObjs );
    mMass.resize( mNumOfObjs );
	mVx.resize( mNumOfObjs );
    mVy.resize( mNumOfObjs );
	mFx.resize( mNumOfObjs );
    mFy.resize( mNumOfObjs );
	mAlive.resize( mNumOfObjs );
	mTails.resize( mNumOfObjs );

	for(int i = mNumLargeObjs; i < mNumOfObjs; i++){
		mX[i] = getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
		mY[i] = getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
		mVx[i] = getRandDouble(-100, 100);
		mVy[i] = getRandDouble(-100, 100);
		mR[i] = getRandDouble(mMinR, mMaxR);
		mMass[i] = mR[i] * mR[i];
		mAlive[i] = true;
		TAIL_PLANET tail(mX[i], mY[i]);
		mTails[i] = tail;
	}
	for(int i = 0; i < mNumLargeObjs; i++){
		mX[i] = mNumLargeObjs == 1 ? 0.0 : getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
		mY[i] = mNumLargeObjs == 1 ? 0.0 : getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
		mVx[i] = 0.0;
		mVy[i] = 0.0;
		mR[i] = mMaxR * 2.0;
		mMass[i] = mMaxR * mMaxR * 1000;
		mAlive[i] = true;
		TAIL_PLANET tail(mX[i], mY[i]);
		mTails[i] = tail;
	}
    mFx.resize( mNumOfObjs );
    mFy.resize( mNumOfObjs );

}

/*
Handle the key events.
*/
bool GALAXY_SYSTEM::handleKeyPressedEvent( int key )
{
    bool flgHandled = false;
	switch(key){
	case '1':
		mNumLargeObjs = 1;
		flgHandled = true;
		reset();
		break;
	case '2':
		mNumLargeObjs = 2;
		flgHandled = true;
		reset();
		break;
	case '3':
		mNumLargeObjs = 3;
		flgHandled = true;
		reset();
		break;
	case 'r':
		flgHandled = true;
		reset();
		break;
	default:
		break;
	}
    return flgHandled;
}

/*
Generate the objects.
Call generateObjects( ).
*/
void GALAXY_SYSTEM::reset( )
{
    generateObjects( );
}

/*
Show the system title.
Show the key usage.
*/
void GALAXY_SYSTEM::askForInput( )
{
    cout << "GALAXY_SYSTEM::askForInput" << endl;
    cout << "Key usage:" << endl;
    cout << "1: one large object" << endl; // generate the objects. Only one large object
    cout << "2: two large object" << endl; // generate the objects. Only two large objects
    cout << "3: three large object" << endl; // generate the objects. Only three large objects
    cout << "r: reset" << endl; 		// reset the positions of the objects
}

/*
Return the number of objects
return mNumOfObjs
*/
int GALAXY_SYSTEM::getNumOfObjs( ) const
{
    return mNumOfObjs;
	//return 0;
}

/*
Get the object information based on the object index.
(x,y) = position
r = radius
Return the alive flag.
*/
bool GALAXY_SYSTEM::getObjInfo( int objIndex, double &x, double &y, double &r ) const
{
    x = mX[objIndex];
    y = mY[objIndex];
    r = mR[objIndex];
    return mAlive[objIndex];
	//return 0;
}

/*
Merge the objects if they overlap with each other.
Modify the velocities of the objects after merging
based on the conservation of momentum.
Set the alive flags of the objects accordingly.

Pseudo-code

For each pair of the objects
  if they do not overlap continue
  If they overlap
    do
      turn off the alive flag of the object with smaller radius
      compute the new velocity of the larger object
*/
void GALAXY_SYSTEM::mergeObjects( )
{
	for(int i = 0; i < mNumOfObjs; i++){
		if( !mAlive[i] )continue;
		double mi = mMass[i];
		double ri = mR[i];
		for(int j = i + 1; j < mNumOfObjs; j++){
			if( !mAlive[j] ) continue;
			double mj = mMass[j];
			double rj = mR[j];

			double dx = mX[i] - mX[j];
			double dy = mY[i] - mY[j];
			double d = sqrt(dx * dx + dy * dy);

			if(ri + rj > d) {
				mAlive[j] = false;

				mVx[i] *= mMass[i];
				mVx[i] += mVx[j] * mMass[j];

				mVy[i] *= mMass[i];
				mVy[i] += mVy[j] * mMass[j];

				mMass[i] += mMass[j];

				mVx[i] /= mMass[i];
				mVy[i] /= mMass[i];
				break;
			}
		}
	}
}

/*
Update the position of the objects
Steps:
1. compute the forces exerting on each object
2. compute the velocity of each object
3. compute the position of each object

Constraints:
The component of a velocity must be inside [-mMaxV, mMaxV].

*/
void GALAXY_SYSTEM::update( ) 
{
    int skipFrames = 10;
    /////////////////////////////////////////////////////
    mergeObjects( ); // merge objects first if they overlap with each other
	mFx.clear();
	mFy.clear();
	mFx.resize(mNumOfObjs);
	mFy.resize(mNumOfObjs);
    //
    //Fill in here
    //compute forces exerting on objects
    //compute velocities of objects
    //compute positions of objects
    //
    //add a point to the tail of each object
    //each tail has a maximum number of sample points
    //
	for(int i = 0; i < mNumOfObjs; i++){
		if( !mAlive[i] ) continue;
		double mi = mMass[i];
		double ri = mR[i];
		for(int j = i + 1; j < mNumOfObjs; j++){
			if( !mAlive[j] ) continue;

			double mj = mMass[j];
			double rj = mR[j];

			double dx = mX[i] - mX[j];
			double dy = mY[i] - mY[j];
			double d2 = dx * dx + dy * dy;
			double d = sqrt(d2);

			double nx = dx / d;
			double ny = dy / d;
			double mij = mi * mj;
			if(d2 != 0.0){
				mFx[i] -= mij * mG * nx / d2;
				mFy[i] -= mij * mG * ny / d2;

				mFx[j] += mij * mG * nx / d2;
				mFy[j] += mij * mG * ny / d2;
			}
		}
	}
	for(int i =0; i < mNumOfObjs; i++){
		if( !mAlive[i] ) continue;

		mVx[i] = mVx[i] + mFx[i] / mMass[i] * mTimeStep;
		mVy[i] = mVy[i] + mFy[i] / mMass[i] * mTimeStep;
		
		if(mVx[i] > mMaxV) mVx[i] = mMaxV;
		if(mVx[i] < -mMaxV) mVx[i] = -mMaxV;

		if(mVy[i] > mMaxV) mVy[i] = mMaxV;
		if(mVy[i] < -mMaxV) mVy[i] = -mMaxV;
	}

	double halfSpaceSize = mSpaceSize / 2.0;
	for(int i = 0; i < mNumOfObjs; i++){
		if( !mAlive[i] ) continue;
		
		mX[i] = mX[i] + mVx[i] * mTimeStep;
		mY[i] = mY[i] + mVy[i] * mTimeStep;
		
		if(skipFrames == 0 || mNumFrames % skipFrames == 0){
			mTails[i].add_to_front(mX[i], mY[i]);
		}
	}
    /////////////////////////////////////////////////////
    ++mNumFrames;
}

//
// return the number of sample points of the tail
// of an object with index planet_index
int GALAXY_SYSTEM::getTail_NumSamplePoints( int planet_index ) const 
{ 
    //mTails
	return mTails[planet_index].points.size();
	//return 0;
}

//
// return the coordinates of the sample point of an object
//
COORD_2D GALAXY_SYSTEM::getTail_SamplePointCoords( int planet_index, int sample_point_index ) const 
{ 
    //mTails
	return mTails[planet_index].points[sample_point_index];
	//return COORD_2D(0,0);
}