//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/03/01
//
#include "mySystemApp.h"

using namespace std;

#define STUDENT_INFO "Name:���~�o   ID:109550206"

void MY_SYSTEM_APP::showMyStudentInfo( ) const
{
	cout << "*******************************" << endl;
    cout << "Date:" << "2020/03/14" << endl;
	cout << "Student ID: 109550206\t" << endl;
	cout << "Student Name: ���~�o\t" << endl;
	cout << "Student Email: hardymike.cs09@nctu.edu.tw\t" << endl;
	cout << "*******************************" << endl;
}

MY_SYSTEM_APP::MY_SYSTEM_APP( )
{
	mSystemType = SYSTEM_TYPE_MONTE_CARLO_CIRCLE;
    string title = STUDENT_INFO;
        glutSetWindowTitle(title.data( ));
}

void MY_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = true;
}

void MY_SYSTEM_APP::update( )
{

}
// CODE: 2021/03/01. Do not delete this line.



