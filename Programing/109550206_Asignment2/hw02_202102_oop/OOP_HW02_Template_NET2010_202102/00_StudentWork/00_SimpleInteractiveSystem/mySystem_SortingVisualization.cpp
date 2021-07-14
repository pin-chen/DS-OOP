//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/29
//
#include "mySystem_SortingVisualization.h"
#include "myBasicTools.h"
#include <iostream>
#include <string>

using namespace std;

SORTING_VISUALIZATION::SORTING_VISUALIZATION( )
{
    mNumElements = 20;
    mMinValue = 1;
    mMaxValue = 30;
    reset();
}

/*
Generate randomly the elements between mMinValue and mMaxValue.
The total number of elements is mNumElements.
*/
void SORTING_VISUALIZATION::reset( )
{
	mCurrentIndex = 0;
	mMaxNonHandledElementIndex = mNumElements;
	mNumbers.clear();
	mNumbers.resize(mNumElements);
	for(int i = 0; i < mNumElements; i++){
		mNumbers[i] = getRandDouble(mMinValue, mMaxValue);
	}
	LastOneSwap = 0;
}

/*
Show the system title.
Ask to input the range [mMinValue, mMaxValue] of the elements.
Ask to input the number of elements.
Generate the elements.
*/
void SORTING_VISUALIZATION::askForInput( )
{
    cout << "//////////////////////////////" << endl;
    cout << "SORTING_VISUALIZATION" << endl;
	cout << "The range of elements is [1, 30]:" << endl;
	while(true){
		cout << "Input minValue and maxValue:" << endl;
		this -> mMinValue = Input();
		this -> mMaxValue = Input();
		if(mMinValue >=1 && mMaxValue <= 30 && mMinValue <= mMaxValue) break;
	}
	while(true){
		cout << "Input the number of elements [1, 50]:" << endl;
		this -> mNumElements = Input();
		if(mNumElements <= 50 && mNumElements >= 1) break;
	}
	cout << "//////////////////////////////" << endl;
    cout << "Press SPACEBAR to visualize the process..." << endl;
    cout << "//////////////////////////////" << endl;
	this -> reset();
}

/*
Two elements whose
indices are (index) and (index+1).

Swap these two elements if their order is incorrect.
*/
void SORTING_VISUALIZATION::checkAndSwapTwoElements( int index )
{

	if (mNumbers[index] > mNumbers[index + 1]){
		int temp = mNumbers[index];
		mNumbers[index] = mNumbers[index + 1];
		mNumbers[index + 1] = temp;
		LastOneSwap = index + 1;
	}
}

/*
Perform one swap step for two elements.
The first element is indicated by mCurrentIndex.
*/
void SORTING_VISUALIZATION::processOneSwapStep( )
{
	if(mMaxNonHandledElementIndex < 1) return;
	if (mCurrentIndex < mMaxNonHandledElementIndex - 2){
		checkAndSwapTwoElements( mCurrentIndex++ );
	}else{
		checkAndSwapTwoElements(mCurrentIndex);
		mMaxNonHandledElementIndex = LastOneSwap;
		LastOneSwap = 0;
		mCurrentIndex = 0;
	}
}

/*
Return the current element that will be processed.
*/
int SORTING_VISUALIZATION::getCurrentElementIndex( ) const
{
    return this -> mCurrentIndex;
}

/*
Return the index of the last non-handled element.

mMaxNonHandledElementIndex
*/
int SORTING_VISUALIZATION::getMaxNonHandledElementIndex( ) const
{
    return this -> mMaxNonHandledElementIndex;
}

/*
Return the number of elements.
*/
int SORTING_VISUALIZATION::getNumOfElements( ) const
{
    //Return the number of elements
    return this -> mNumElements;
}

/*
Return the element whose index is elementIndex.
*/
int SORTING_VISUALIZATION::getElement( int elementIndex ) const
{
	return this -> mNumbers[elementIndex];
}

//Check input is number or not
int SORTING_VISUALIZATION::Input(){
	while(1){
		string s;
		cin >> s;
		try{
			int num = stoi(s);
			return num;
			break;
		}catch(std::exception& e){
			cout << "Wrong input!!!" <<'\n'; 
		}
	}
}