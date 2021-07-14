//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/04/
//
#include "mySystem_2048.h"
#include <iostream>

#define UP		0
#define DOWN	1
#define LEFT	2
#define RIGHT	3

using namespace std;

static int score10[] = {
	0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000,
};

static unsigned char specialKeys[] = {
    GLUT_KEY_UP,
    GLUT_KEY_DOWN,
    GLUT_KEY_LEFT,
    GLUT_KEY_RIGHT
};

int numSpecialKeys = sizeof(specialKeys)/sizeof(unsigned char);

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    flg_AutoPlay = false;
}

MY_2048::MY_2048( int nx, int nz )
{
    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    // Implement your own stuff
    //
	mNX = nx;
    mNZ = nz;
    reset();
	
}

void MY_2048::setDimension(int nx, int nz)
{
    mFlgFocus = true;
    
    //
    // Implement your own stuff
    //

	mNX = nx;
    mNZ = nz;
    reset();
}


void MY_2048::setFocus( bool flg )
{
    mFlgFocus = flg;
}

void MY_2048::setPosition( int x, int z )
{
    mPositionX = x;
    mPositionZ = z;
}

//copy
void MY_2048::copyT( int src[][MAX_2048_NX], int tgt[][MAX_2048_NX])
{
    for (int j = 0; j < mNZ; ++j ) {
        for (int i = 0; i < mNX; ++i ) {
            tgt[j][i] = src[j][i];
        }
    }
}

//
// Copy the m's previous board 
// to the object's mBoard.
//
void MY_2048::copyPrevious( const BASE_SYSTEM *m )
{
	for ( int j = 0; j < mNZ; ++j ) {
		for ( int i = 0; i < mNX; ++i ) {
			mBoard[j][i] = ((MY_2048*)m)->mPreviousBoard[j][i];
		}
	}
}

//
//reset the game board
//
void MY_2048::reset( )
{
	mEvent = 0;
	///////////////////////////////////////
	//
	// Implement your own stuff
	//
	for ( int j = 0; j < mNZ; ++j ) {
		for ( int i = 0; i < mNX; ++i ) {
			mBoard[ j ][ i ] = 0;
		}
	}
	for (int j = 0; j < mNZ; ++j ) {
		for (int i = 0; i < mNX; ++i ) {
			mPreviousBoard[j][i] = mBoard[j][i];
		}
	}
}

//
// show messages and ask for input (if any)
//
void MY_2048::askForInput( )
{
    //
    // Implement your own stuff
    //
	cout << "MY_2048" << endl;
    cout << "Key usage:" << endl;
    cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
    cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
    cout << "3: generate randomly the numbers for all the cells" << endl;
    cout << "r: clear all the cells" << endl;
    cout << " " << endl;
    cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;

}

//
// randomly generate a new number
//
void MY_2048::generateNumber( )
{
    //
    // Implement your own stuff
    //
	//rand to selet 2 or 4
    int r = rand()%10;
    int v = 2;
    if(r == 1) v = 4;
	//load free cells
    vector<vector<pair<int,int>>> freeArr(mNZ);
    for ( int j = 0; j < mNZ; ++j ) { 
        for ( int i = 0; i < mNX; ++i ) {
            int z = mNZ - j - 1;
            if ( mBoard[ z ][ i ] == 0 ) {
				freeArr[j].push_back(pair<int,int>(z,i));
            }
        }
    }
	//
	if(freeArr.size() == 0) return;
	//rand to selet cell
    for ( int j = 0; j < mNZ; ++j ) {
		if ( freeArr[j].size() ==0) continue;
		int index = rand()%freeArr[j].size();
		int z = freeArr[j][index].first;
		int x = freeArr[j][index].second;
		mBoard[ z ][ x ] = v;
		break;
    }
}

void MY_2048::moveDown( )
{
    //
    // Implement your own stuff
    //    
    for ( int i = 0; i < mNX; ++i ) {
        moveOneLine(i, DOWN);
    }
}

void MY_2048::moveUp( )
{
    //
    // Implement your own stuff
    //
	for ( int i = 0; i < mNX; ++i ) {
        moveOneLine(i, UP);
    }
}

void MY_2048::moveLeft( )
{
    //
    // Implement your own stuff
    //
	for ( int i = 0; i < mNZ; ++i ) {
        moveOneLine(i, LEFT);
    }
}

void MY_2048::moveRight( )
{
    //
    // Implement your own stuff
    //
	for ( int i = 0; i < mNZ; ++i ) {
        moveOneLine(i, RIGHT);
    }
}

void MY_2048::generateNumbers_All_2to4( )
{
    //
    // Implement your own stuff
    //
	generateNumbers(2);
}

void MY_2048::generateNumbers_All_2to8( )
{
    //
    // Implement your own stuff
    //
	generateNumbers(3);
}

void MY_2048::generateNumbers_All( )
{
    //
    // Implement your own stuff
    //
	generateNumbers(11);
}

void MY_2048::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 'r':
    case 'R':
        reset( );
        break;
    case '1':
        generateNumbers_All_2to4( );
        break;
    case '2':
        generateNumbers_All_2to8( );
        break;
    case '3':
        generateNumbers_All( );
        break;
	case ' ':
        flg_AutoPlay = !flg_AutoPlay;
        break;
    case 'a':
    case 'A':
        flg_AutoPlay = true;
        update( );
        flg_AutoPlay = false;
		break;
    }
}

bool MY_2048::performAction( unsigned char key ) 
{
	bool flgDone = false;

    switch( key ) {
    case GLUT_KEY_UP:
        flgDone = true;
        moveUp( );
        mEvent = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        flgDone = true;
        moveDown( );
        mEvent = GLUT_KEY_DOWN;
        break;
    case GLUT_KEY_LEFT:
        flgDone = true;
        moveLeft( );
        mEvent = GLUT_KEY_LEFT;
        break;
    case GLUT_KEY_RIGHT:
        flgDone = true;
        moveRight( );
        mEvent = GLUT_KEY_RIGHT;
        break;
    }
    if ( flgDone ) generateNumber();

	return flgDone;
}

void MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    //
    // It takes a long time to show a message!
    //
    //cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
	int initBoard[MAX_2048_NZ][MAX_2048_NX];
    copyT(mBoard, initBoard);
    if ( performAction( key ) ) {
        copyT(initBoard, mPreviousBoard);
    }
}

bool MY_2048::isAutoPlay() const
{
    return flg_AutoPlay;
}
//coomput the rate with every event
double MY_2048::EventDFS( int numSteps, unsigned char action_key, int board[][MAX_2048_NX])
{
    double LScore = 0.0;
	//compute rate by some way
	//(sum of all cells) * (num of free cells)
    if (numSteps <=0) {
		double s = 0.0;
		int numOfFree = 1;
		for ( int i = 0; i < mNZ; ++i ) {
			for ( int j = 0; j < mNX; ++j ) {
				if(mBoard[i][j] == 0) {
					numOfFree++;
					continue;
				}
				for(int k = 0; k < 11; k++){
					int v = 2;
					v = v << k;
					if(v == mBoard[i][j]){
						s += score10[k];
						continue;
					}
				}
			}
		}
		s *= numOfFree;
		if (s > LScore) {
			LScore = s;
		}
        return LScore;
    }
    copyT(board, mBoard);
    handleSpecialKeyPressedEvent( action_key );
	int initBoard[MAX_2048_NZ][MAX_2048_NX];
    copyT(mBoard, initBoard);
	//check that key will move
	bool sign = false;
	if(numSteps == 7){
		for ( int i = 0; i < mNZ; ++i ) {
			for ( int j = 0; j < mNX; ++j ) {
				if(initBoard[i][j] != board[i][j]){
					sign = true;
					break;
				}
			}
			if(sign) break;
		}
		if(sign == false) return 0.0;
	}
    //call next key
    double score = 0.0;
    for (int i = 0; i < numSpecialKeys; ++i ) {
        score = score + EventDFS( numSteps - 1, specialKeys[ i ], initBoard );
    }
    return score;
}
//
// The update( ) function is called every frame.
//
// Design an algorithm to automatically perform
// one step.
//
void MY_2048::update( )
{
    //
    // It takes a long time to show a message!
    //
    if (!flg_AutoPlay) return;
	cout << "MY_2048::update( )" << endl;
    //cout << "MY_2048::flg_AutoPlay:\t" << flg_AutoPlay << endl;
	
    //
    // Implement your own stuff
    //
	copyT(mBoard, mPreviousBoard);
	//check next 7 keys
    vector<double> score(numSpecialKeys, 0);
    for (int i = 0; i < numSpecialKeys; ++i ) {
		int initBoard[MAX_2048_NZ][MAX_2048_NX];
		copyT(mBoard, initBoard);
		double fScore = EventDFS( 7, specialKeys[i], initBoard );
		copyT(initBoard, mBoard);
		score[i] = fScore;
    }
	//take and the best next ket 
	//cout << score[0] << '\n';
    double best_score = score[0];
    int action_index = 0;
    for (int i = 1; i < numSpecialKeys; ++i ) {
        //cout << score[i] << '\n';
		if (score[i] > best_score) {
            best_score = score[i];
            action_index = i;
        }
    }
    handleSpecialKeyPressedEvent( specialKeys[action_index] );
}
//
void MY_2048::generateNumbers(int range)
{
    reset( );
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            int r = rand() % range;
            int v = 2;
            v = v << r;
            mBoard[ j ][ i ] = v;
        }
    }
}
//
void MY_2048::moveOneLine(int i, int direction)
{
	int base, start;
	switch(direction){
	case UP:
		base = mNZ - 1;
		start = mNZ - 1;
		while (1) {
			int xz0 = findItem( start, i, direction );
			if ( xz0 < 0 ) break;
			moveItem( xz0, base, i, direction );
			int xz1 = findItem( xz0 - 1, i, direction );
			if ( xz1 < 0 ) break;
			//merge
			if ( mBoard[xz1][i] == mBoard[base][i] ) {
				mBoard[base][i] *= 2;
				mBoard[xz1][i] = 0;
				start = xz1 - 1;
			}else{
				start = xz1;
			}
			--base;
		}
		break;
	case DOWN:
		base = 0;
		start = 0;
		while (1) {
			int xz0 = findItem( start, i, direction );
			if ( xz0 >= mNZ ) break; // no item found
			moveItem( xz0, base, i, direction );
			int xz1 = findItem( xz0 + 1, i, direction );
			if ( xz1 >= mNZ ) break;
			//merge
			if ( mBoard[xz1][i] == mBoard[base][i] ) {
				mBoard[base][i] *= 2;
				mBoard[xz1][i] = 0;
				start = xz1 + 1;
			}else{
				start = xz1;
			}
			++base;
		}
		break;
	case RIGHT:
		base = mNX - 1;
		start = mNX - 1;
		while (1) {
			int xz0 = findItem( start, i, direction );
			if ( xz0 < 0 ) break;
			moveItem( xz0, base, i, direction );
			int xz1 = findItem( xz0 - 1, i, direction );
			if ( xz1 < 0 ) break;
			//merge
			if ( mBoard[i][xz1] == mBoard[i][base] ) {
				mBoard[i][base] *= 2;
				mBoard[i][xz1] = 0;
				start = xz1 - 1;
			}else{
				start = xz1;
			}
			--base;
		}
		break;
	case LEFT:
		base = 0;
		start = 0;
		while (1) {
			int xz0 = findItem( start, i, direction );
			if ( xz0 >= mNX ) break; // no item found
			moveItem( xz0, base, i, direction );
			int xz1 = findItem( xz0 + 1, i, direction );
			if ( xz1 >= mNX ) break;
			//merge
			if ( mBoard[i][xz1] == mBoard[i][base] ) {
				mBoard[i][base] *= 2;
				mBoard[i][xz1] = 0;
				start = xz1 + 1;
			}else{
				start = xz1;
			}
			++base;
		}
		break;
	}
}
//
int MY_2048::findItem( int start, int i, int direction ) const 
{
	int xz = start;
	switch(direction){
	case UP:
		while ( xz >= 0 ) {
			if ( mBoard[xz][i] != 0) {
				break;
			}
			--xz;
		}
		break;
	case DOWN:
		while ( xz < mNZ ) {
			if ( mBoard[xz][i] != 0) {
				break;
			}
			++xz;
		}
		break;
	case RIGHT:
		while ( xz >= 0 ) {
			if ( mBoard[i][xz] != 0) {
				break;
			}
			--xz;
		}
		break;
	case LEFT:
		while ( xz < mNX ) {
			if ( mBoard[i][xz] != 0) {
				break;
			}
			++xz;
		}
		break;
	}
	return xz;
}
//
void MY_2048::moveItem( int now, int move, int i, int direction )
{
	if ( move == now ) return;
	switch(direction){
	case UP:
	case DOWN:
		mBoard[move][i] = mBoard[now][i];
		mBoard[now][i] = 0;
		break;
	case LEFT:
	case RIGHT:
		mBoard[i][move] = mBoard[i][now];
		mBoard[i][now] = 0;
		break;
	}
}