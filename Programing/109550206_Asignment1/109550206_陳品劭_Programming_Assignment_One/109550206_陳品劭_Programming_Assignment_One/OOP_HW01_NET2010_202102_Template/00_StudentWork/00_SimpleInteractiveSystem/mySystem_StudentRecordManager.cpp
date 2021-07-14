//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#include "mySystem_StudentRecordManager.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

STUDENT_RECORD_MANAGER::STUDENT_RECORD_MANAGER( )
{
	mNumStudents = 0;
}

void STUDENT_RECORD_MANAGER::askForInput( )
{
	//Show the system title
	//Ask to input the number of students
	//Ask to input the score of each student
	//Show the average
	//Show the standard deviation
	//Show the scores in an ascending order
	//
	cout << "STUDENT_RECORD_MANAGER" << endl;
	while ( true ) {
		cout << "Input the number of students [2, 100]:" << endl;
		mNumStudents = Input();
		if ( mNumStudents >= 2 && mNumStudents <= 100 ) break;
	}

	cout << "Input the score of each student [0, 100]:" << endl;
	mScore.clear();
	for(int i = 0; i < mNumStudents; ++i){
		while( true ){
			mScore.push_back( Input() );
			if ( mScore[i] >= 0 && mScore[i] <= 100 ) break;
			cout << "Wrong number!!!" << '\n';
		}
	}

	cout << "Average: " << computeAverage( ) << '\n';
	cout << "Standard Deviation: " << computeStandardDeviation( ) << '\n';

    sortScores( );
	cout << "Sorted scores:" << '\n';
	showSortedScores( );
}

double STUDENT_RECORD_MANAGER::computeAverage( )
{
	//Compute the average
    int totalScore = 0;
    for(int i = 0; i < mNumStudents; ++i){
		totalScore += mScore[i];
	}
	mAverageScore = (double) totalScore / mNumStudents;
	return mAverageScore;
}

double STUDENT_RECORD_MANAGER::computeStandardDeviation( )
{
	//Compute the standard deviation
	double sum = 0.0;
	for(int i = 0; i < mNumStudents; ++i){
		sum += mScore[i] * mScore[i];
	}

	mStandardDeviation = sqrt( (double) sum / mNumStudents - (double) mAverageScore * mAverageScore );
	return mStandardDeviation;
}

void STUDENT_RECORD_MANAGER::sortScores( )
{
	//Sorting in an ascending order
	mSortedScore.assign(mScore.begin(), mScore.end() );
	sort(mSortedScore.begin(), mSortedScore.end() );
}

void STUDENT_RECORD_MANAGER::showSortedScores( ) const
{
	//Show the scores in an ascending order
	for(int i = 0; i < mNumStudents; ++i){
		cout << mSortedScore[i] << '\n';
	}
}

int STUDENT_RECORD_MANAGER::getNumOfStudentsInScoreInterval(int s0, int s1) const
{
	//
	//Return the number of students whose score is inside the interval [s0, s1]. 
	//s0 and s1 are included.
	// 
	int num = 0;
	for (int i = 0; i < mNumStudents; ++i){
		if (mScore[i] >= s0 && mScore[i] <= s1){
			num++;
		}
	}
    return num;
}

//Check input is number or not
double STUDENT_RECORD_MANAGER::Input(){
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