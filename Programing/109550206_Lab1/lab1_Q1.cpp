#include "lab1_Q1.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void QUADRATIC::print()
{
	if(b < 0){
		if(c < 0){
			cout << a << "x^2" << b << "x" << c << '\n';
		}else{
			cout << a << "x^2" << b << "x+" << c << '\n';
		}
	}else{
		if(c < 0){
			cout << a << "x^2+" << b << "x" << c << '\n';
		}else{
			cout << a << "x^2+" << b << "x+" << c << '\n';
		}
	}
	/*
	PRINT QUADRATIC FORMULA
	*/
}

void QUADRATIC::add(QUADRATIC q)
{
	a += q.a;
	b += q.b;
	c += q.c;
	/*
	ADD TWO QUADRATIC FORMULAS
	*/
}

void QUADRATIC::discriminant()
{
	double D = b*b-4*a*c;
	
	if(D > 0)
	{
		double ans1, ans2;
		ans1 = ( -b + sqrt(D) ) / double(2*a);
		ans2 = ( -b - sqrt(D) ) / double(2*a);
		cout << "There are two roots: " << ans1 << ", " << ans2 <<'\n';	
	}
	else if(D == 0)
	{
		double ans;
		ans = ( -b + sqrt(D) ) / double(2*a);
		cout << "There is a double root: " << ans <<'\n';	
	}
	else
	{
		double ans, complex;
		ans = -b / double(2*a);
		complex = sqrt(-D) / double(2*a);
		cout << "There are two complex roots: " 
			<< ans << " + " << complex << "i, " 
			<< ans << " - " << complex << "i\n";
	}
	/*
	FIND DISCRIMINANT OF QUADRATIC FORMULA AND ANWSERS
	*/
}

void QUADRATIC::input()
{
	//cout<<"INPUT  QUADRATIC FORMULA (a, b, c):"<<'\n';
	cin >> a >> b >> c;
	/*
	INPUT
	*/
}

void QUADRATIC::show()
{
	cout << "a: " << a << ", b: " << b << ", c: " << c << '\n';
	/*
	PRINT INPUT
	*/
}
